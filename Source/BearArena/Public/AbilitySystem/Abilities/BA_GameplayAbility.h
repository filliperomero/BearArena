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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BearArena|Debug")
	bool bDrawDebugs { false };
};
