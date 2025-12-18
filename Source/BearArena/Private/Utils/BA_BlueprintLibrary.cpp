// Copyright Fillipe Romero. All Rights Reserved.

#include "Utils/BA_BlueprintLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/BA_AttributeSet.h"
#include "Characters/BA_BaseCharacter.h"
#include "GameplayTags/BA_Tags.h"
#include "Kismet/GameplayStatics.h"

EHitDirection UBA_BlueprintLibrary::GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator)
{
	const float DotProduct = FVector::DotProduct(TargetForward, ToInstigator);

	if (DotProduct < -0.5f) return EHitDirection::Back;

	// Either Left or Right
	if (DotProduct < 0.5f)
	{
		const FVector CrossProduct = FVector::CrossProduct(TargetForward, ToInstigator);
		if (CrossProduct.Z < 0.f) return EHitDirection::Left;

		return EHitDirection::Right;
	}

	return EHitDirection::Front;
}

FName UBA_BlueprintLibrary::GetHitDirectionName(const EHitDirection& HitDirection)
{
	switch (HitDirection)
	{
		case EHitDirection::Left: return FName("Left");
		case EHitDirection::Right: return FName("Right");
		case EHitDirection::Front: return FName("Front");
		case EHitDirection::Back: return FName("Back");
		default: return FName("None");
	}
}

FClosestActorWithTagResult UBA_BlueprintLibrary::FindClosestActorWithTag(const UObject* WorldContextObject, const FVector& Origin, const FName& Tag)
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsWithTag(WorldContextObject, Tag, OutActors);

	float ClosestDistance = TNumericLimits<float>::Max();
	AActor* ClosestActor = nullptr;

	for (AActor* Actor : OutActors)
	{
		if (!IsValid(Actor)) continue;

		ABA_BaseCharacter* BaseCharacter = Cast<ABA_BaseCharacter>(Actor);
		if (!IsValid(BaseCharacter) || !BaseCharacter->IsAlive()) continue;

		const float Distance = FVector::Dist(Origin, BaseCharacter->GetActorLocation());

		if (Distance < ClosestDistance)
		{
			ClosestDistance = Distance; 
			ClosestActor = Actor;
		}
	}

	FClosestActorWithTagResult Result;
	Result.Actor = ClosestActor;
	Result.Distance = ClosestDistance;
	
	return Result;
}

void UBA_BlueprintLibrary::SendDamageEventToPlayer(AActor* Target, const TSubclassOf<UGameplayEffect>& DamageEffect, FGameplayEventData& Payload, const FGameplayTag& DataTag, float Damage, UObject* OptionalParticleSystem)
{
	ABA_BaseCharacter* PlayerCharacter = Cast<ABA_BaseCharacter>(Target);
	if (!IsValid(PlayerCharacter) || !PlayerCharacter->IsAlive()) return;
	
	UBA_AttributeSet* AttributeSet = Cast<UBA_AttributeSet>(PlayerCharacter->GetAttributeSet());
	if (!IsValid(AttributeSet)) return;
	
	const bool bIsLethal = AttributeSet->GetHealth() - Damage <= 0.f;
	const FGameplayTag EventTag = bIsLethal ? BATags::Events::Player::Death : BATags::Events::Player::HitReact;
	
	Payload.OptionalObject = OptionalParticleSystem;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(PlayerCharacter, EventTag, Payload);
	
	UAbilitySystemComponent* TargetASC = PlayerCharacter->GetAbilitySystemComponent();
	if (!IsValid(TargetASC)) return;
	
	FGameplayEffectContextHandle ContextHandle = TargetASC->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = TargetASC->MakeOutgoingSpec(DamageEffect, 1.f, ContextHandle);
	
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DataTag, -Damage);
	TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}
