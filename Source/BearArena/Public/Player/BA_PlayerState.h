// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "BA_PlayerState.generated.h"

class UAbilitySystemComponent;

UCLASS()
class BEARARENA_API ABA_PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABA_PlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	UPROPERTY(VisibleAnywhere, Category = "BearArena|Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
};
