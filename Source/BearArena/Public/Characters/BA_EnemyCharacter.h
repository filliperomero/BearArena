// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BA_BaseCharacter.h"
#include "BA_EnemyCharacter.generated.h"

class UAbilitySystemComponent;

UCLASS()
class BEARARENA_API ABA_EnemyCharacter : public ABA_BaseCharacter
{
	GENERATED_BODY()

public:
	ABA_EnemyCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
};
