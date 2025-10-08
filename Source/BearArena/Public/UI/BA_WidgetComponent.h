// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "BA_WidgetComponent.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class UBA_AttributeSet;
class UBA_AbilitySystemComponent;
class ABA_BaseCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BEARARENA_API UBA_WidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:

protected:
	virtual void BeginPlay() override;

private:
	TWeakObjectPtr<ABA_BaseCharacter> Character;
	TWeakObjectPtr<UBA_AbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<UBA_AttributeSet> AttributeSet;

	void InitAbilitySystemData();
	bool IsASCInitialized() const;

	UFUNCTION()
	void OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS);
};
