// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/BA_GameplayAbility.h"
#include "BA_Primary.generated.h"

UCLASS()
class BEARARENA_API UBA_Primary : public UBA_GameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "BearArena|Abilities")
	TArray<AActor*> HitBoxOverlapTest();

	UFUNCTION(BlueprintCallable, Category = "BearArena|Abilities")
	void SendEventToActors(const TArray<AActor*>& Actors, const FGameplayTag EventTag);

private:
	void DrawHitBoxOverlapDebugs(const TArray<FOverlapResult>& OverlapResults, const FVector& HitBoxLocation) const;
	
	UPROPERTY(EditDefaultsOnly, Category = "BearArena|Abilities")
	float HitBoxRadius { 100.f };

	UPROPERTY(EditDefaultsOnly, Category = "BearArena|Abilities")
	float HitBoxForwardOffset { 200.f };

	UPROPERTY(EditDefaultsOnly, Category = "BearArena|Abilities")
	float HitBoxElevationOffset { 20.f };
};
