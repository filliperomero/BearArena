// Copyright Fillipe Romero. All Rights Reserved.

#include "UI/Widgets/BA_AttributeWidget.h"

#include "AbilitySystem/BA_AttributeSet.h"

void UBA_AttributeWidget::OnAttributeChange(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair, UBA_AttributeSet* AttributeSet)
{
	if (!IsValid(AttributeSet)) return;

	const float AttributeValue = Pair.Key.GetNumericValue(AttributeSet);
	const float MaxAttributeValue = Pair.Value.GetNumericValue(AttributeSet);

	BP_OnAttributeChange(AttributeValue, MaxAttributeValue);
}

bool UBA_AttributeWidget::MatchesAttributes(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const
{
	return Attribute == Pair.Key && MaxAttribute == Pair.Value;
}
