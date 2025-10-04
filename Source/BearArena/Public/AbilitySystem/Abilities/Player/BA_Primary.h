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
	void HitBoxOverlapTest();

private:
	UPROPERTY(EditDefaultsOnly, Category = "BearArena|Abilities")
	float HitBoxRadius { 100.f };

	UPROPERTY(EditDefaultsOnly, Category = "BearArena|Abilities")
	float HitBoxForwardOffset { 200.f };

	UPROPERTY(EditDefaultsOnly, Category = "BearArena|Abilities")
	float HitBoxElevationOffset { 20.f };
};
