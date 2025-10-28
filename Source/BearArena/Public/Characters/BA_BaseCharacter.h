// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "BA_BaseCharacter.generated.h"

struct FOnAttributeChangeData;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FASCInitialized, UAbilitySystemComponent*, ASC, UAttributeSet*, AS);

UCLASS(Abstract)
class BEARARENA_API ABA_BaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABA_BaseCharacter();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const { return nullptr; }

	UPROPERTY(BlueprintAssignable)
	FASCInitialized OnASCInitialized;

	UFUNCTION(BlueprintCallable, Category = "BearArena|Death")
	virtual void HandleRespawn();

	UFUNCTION(BlueprintCallable, Category = "BearArena|Attributes")
	void ResetAttributes();

protected:
	void GiveStartupAbilities();
	void InitializeAttributes() const;
	void OnHealthChanged(const FOnAttributeChangeData& AttributeChangeData);

	virtual void HandleDeath();

private:
	UPROPERTY(EditDefaultsOnly, Category = "BearArena|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "BearArena|Effects")
	TSubclassOf<UGameplayEffect> InitializeAttributesEffect;

	UPROPERTY(EditDefaultsOnly, Category = "BearArena|Effects")
	TSubclassOf<UGameplayEffect> ResetAttributesEffect;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Replicated)
	bool bAlive { true };

public:
	bool IsAlive() const { return bAlive; }
	void SetAlive(bool InAlive) { bAlive = InAlive; }
};
