// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BA_BaseCharacter.h"
#include "BA_EnemyCharacter.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class BEARARENA_API ABA_EnemyCharacter : public ABA_BaseCharacter
{
	GENERATED_BODY()

public:
	ABA_EnemyCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BearArena|AI")
	float AcceptanceRadius { 500.f };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BearArena|AI")
	float MinAttackDelay { 0.1f };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BearArena|AI")
	float MaxAttackDelay { 0.5f };
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BearArena", Replicated)
	bool bIsBeingLaunched { false };
	
	UFUNCTION(BlueprintImplementableEvent)
	float GetTimelineLength();
	
	void StopMovementUntilLanded();

protected:
	virtual void BeginPlay() override;
	virtual void HandleDeath() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
	UFUNCTION()
	void EnableMovementOnLanded(const FHitResult& HitResult);
};
