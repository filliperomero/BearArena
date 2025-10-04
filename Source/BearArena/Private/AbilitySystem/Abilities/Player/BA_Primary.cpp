// Copyright Fillipe Romero. All Rights Reserved.

#include "AbilitySystem/Abilities/Player/BA_Primary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Engine/OverlapResult.h"

TArray<AActor*> UBA_Primary::HitBoxOverlapTest()
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActorFromActorInfo());

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActors(ActorsToIgnore);

	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECC_Pawn, ECR_Block);

	TArray<FOverlapResult> OverlapResults;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(HitBoxRadius);

	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector() * HitBoxForwardOffset;
	const FVector HitBoxLocation = GetAvatarActorFromActorInfo()->GetActorLocation() + Forward + FVector(0.f, 0.f, HitBoxElevationOffset);

	GetWorld()->OverlapMultiByChannel(OverlapResults, HitBoxLocation, FQuat::Identity, ECC_Visibility, Sphere, QueryParams, ResponseParams);

	TArray<AActor*> ActorsHit;

	for (const FOverlapResult& OverlapResult : OverlapResults)
	{
		if (!IsValid(OverlapResult.GetActor())) continue;

		ActorsHit.AddUnique(OverlapResult.GetActor());
	}

	if (bDrawDebugs)
	{
		DrawHitBoxOverlapDebugs(OverlapResults, HitBoxLocation);
	}

	return ActorsHit;
}

void UBA_Primary::SendEventToActors(const TArray<AActor*>& Actors, const FGameplayTag EventTag)
{
	for (AActor* HitActor : Actors)
	{
		FGameplayEventData Payload;
		Payload.Instigator = GetAvatarActorFromActorInfo();
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor, EventTag, Payload);
	}
}

void UBA_Primary::DrawHitBoxOverlapDebugs(const TArray<FOverlapResult>& OverlapResults, const FVector& HitBoxLocation) const
{
	DrawDebugSphere(GetWorld(), HitBoxLocation, HitBoxRadius, 16, FColor::Red, false, 3.f);

	for (const FOverlapResult& OverlapResult : OverlapResults)
	{
		if (IsValid(OverlapResult.GetActor()))
		{
			FVector DebugLocation = OverlapResult.GetActor()->GetActorLocation();
			DebugLocation.Z += 100.f;
			DrawDebugSphere(GetWorld(), DebugLocation, 30.f, 10, FColor::Green, false, 3.f);
		}
	}
}
