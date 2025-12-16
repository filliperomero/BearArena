// Copyright Fillipe Romero. All Rights Reserved.

#include "Notifies/BA_MeleeAttackNotify.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "KismetTraceUtils.h"
#include "Characters/BA_PlayerCharacter.h"
#include "GameplayTags/BA_Tags.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void UBA_MeleeAttackNotify::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	
	if (!IsValid(MeshComp) || !IsValid(MeshComp->GetOwner())) return;
	
	TArray<FHitResult> Hits = PerformSphereTrace(MeshComp);
	SendEventsToActors(MeshComp, Hits);
}

TArray<FHitResult> UBA_MeleeAttackNotify::PerformSphereTrace(USkeletalMeshComponent* MeshComp) const
{
	TArray<FHitResult> OutHits;
	
	const FTransform SocketTransform = MeshComp->GetSocketTransform(SocketName);
	const FVector Start = SocketTransform.GetLocation();
	const FVector ExtendedSocketDirection = UKismetMathLibrary::GetForwardVector(SocketTransform.GetRotation().Rotator()) * SocketExtensionOffset;
	const FVector End = Start - ExtendedSocketDirection;
	
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(MeshComp->GetOwner());
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActors(ActorsToIgnore);
	
	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECC_Pawn, ECR_Block);
	
	UWorld* World = GEngine->GetWorldFromContextObject(MeshComp, EGetWorldErrorMode::LogAndReturnNull);
	if (!IsValid(World)) return OutHits;
	
	const bool bHit = World->SweepMultiByChannel(OutHits, Start, End, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(SphereTraceRadius), Params, ResponseParams);
	
	if (bDrawDebugs)
	{
		DrawDebugSphereTraceMulti(World, Start, End, SphereTraceRadius, EDrawDebugTrace::ForDuration, bHit, OutHits, FColor::Red, FColor::Green, 5.f);
	}
	
	return OutHits;
}

void UBA_MeleeAttackNotify::SendEventsToActors(USkeletalMeshComponent* MeshComp, const TArray<FHitResult>& Hits) const
{
	for (const FHitResult& Hit : Hits)
	{
		ABA_PlayerCharacter* PlayerCharacter = Cast<ABA_PlayerCharacter>(Hit.GetActor());
		if (!IsValid(PlayerCharacter) || !PlayerCharacter->IsAlive()) continue;
		
		UAbilitySystemComponent* ASC = PlayerCharacter->GetAbilitySystemComponent();
		if (!IsValid(ASC)) continue;
		
		FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
		ContextHandle.AddHitResult(Hit);
		
		FGameplayEventData Payload;
		Payload.Target = PlayerCharacter;
		Payload.ContextHandle = ContextHandle;
		Payload.Instigator = MeshComp->GetOwner();
		
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), BATags::Events::Enemy::MeleeTraceHit, Payload);
	}
}
