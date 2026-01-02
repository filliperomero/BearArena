// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Blueprint/UserWidget.h"
#include "BA_AttributeWidget.generated.h"

class UBA_AttributeSet;

UCLASS()
class BEARARENA_API UBA_AttributeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BearArena|Attributes")
	FGameplayAttribute Attribute;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BearArena|Attributes")
	FGameplayAttribute MaxAttribute;

	void OnAttributeChange(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair, UBA_AttributeSet* AttributeSet, float OldValue);
	bool MatchesAttributes(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const;

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="On Attribute Change"))
	void BP_OnAttributeChange(float NewValue, float NewMaxValue, float OldValue);
	
	UPROPERTY(BlueprintReadOnly, Category = "BearArena|Attributes")
	TWeakObjectPtr<AActor> AvatarActor;
};
