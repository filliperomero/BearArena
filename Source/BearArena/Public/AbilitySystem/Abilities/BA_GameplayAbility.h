// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BA_GameplayAbility.generated.h"

UCLASS()
class BEARARENA_API UBA_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BearArena|Debug")
	bool bDrawDebugs { false };
};
