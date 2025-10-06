// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "BA_BaseCharacter.generated.h"

class UGameplayEffect;
class UGameplayAbility;

UCLASS(Abstract)
class BEARARENA_API ABA_BaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABA_BaseCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	void GiveStartupAbilities();
	void InitializeAttributes() const;

private:
	UPROPERTY(EditDefaultsOnly, Category = "BearArena|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "BearArena|Effects")
	TSubclassOf<UGameplayEffect> InitializeAttributesEffect;
};
