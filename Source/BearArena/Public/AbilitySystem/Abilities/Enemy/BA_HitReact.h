// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/BA_GameplayAbility.h"
#include "BA_HitReact.generated.h"

UCLASS()
class BEARARENA_API UBA_HitReact : public UBA_GameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "BearArena|Abilities")
	void CacheHitDirectionVectors(AActor* Instigator);
	
	UPROPERTY(BlueprintReadOnly, Category = "BearArena|Abilities")
	FVector AvatarForward;

	UPROPERTY(BlueprintReadOnly, Category = "BearArena|Abilities")
	FVector ToInstigator;
};
