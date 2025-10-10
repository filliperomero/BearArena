// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Components/WidgetComponent.h"
#include "BA_WidgetComponent.generated.h"

class UBA_AttributeSet;
class UAttributeSet;
class UAbilitySystemComponent;
class UBA_AbilitySystemComponent;
class ABA_BaseCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BEARARENA_API UBA_WidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TMap<FGameplayAttribute, FGameplayAttribute> AttributeMap;

private:
	TWeakObjectPtr<ABA_BaseCharacter> Character;
	TWeakObjectPtr<UBA_AbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<UBA_AttributeSet> AttributeSet;

	void InitAbilitySystemData();
	bool IsASCInitialized() const;
	void InitializeAttributeDelegate();
	void BindWidgetToAttributeChanges(UWidget* WidgetObject, const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const;

	UFUNCTION()
	void OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS);

	UFUNCTION()
	void BindToAttributeChanges();
};
