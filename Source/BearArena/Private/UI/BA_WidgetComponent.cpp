// Copyright Fillipe Romero. All Rights Reserved.

#include "UI/BA_WidgetComponent.h"

#include "AbilitySystem/BA_AbilitySystemComponent.h"
#include "AbilitySystem/BA_AttributeSet.h"
#include "Blueprint/WidgetTree.h"
#include "Characters/BA_BaseCharacter.h"
#include "UI/Widgets/BA_AttributeWidget.h"

void UBA_WidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	InitAbilitySystemData();

	if (!IsASCInitialized())
	{
		Character->OnASCInitialized.AddDynamic(this, &ThisClass::OnASCInitialized);
		return;
	}

	InitializeAttributeDelegate();
}

void UBA_WidgetComponent::InitAbilitySystemData()
{
	Character = Cast<ABA_BaseCharacter>(GetOwner());
	AttributeSet = Cast<UBA_AttributeSet>(Character->GetAttributeSet());
	AbilitySystemComponent = Cast<UBA_AbilitySystemComponent>(Character->GetAbilitySystemComponent());
}

bool UBA_WidgetComponent::IsASCInitialized() const
{
	return AbilitySystemComponent.IsValid() && AttributeSet.IsValid();
}

void UBA_WidgetComponent::InitializeAttributeDelegate()
{
	if (!AttributeSet->bAttributesInitialized)
	{
		AttributeSet->OnAttributesInitialized.AddDynamic(this, &ThisClass::BindToAttributeChanges);
	}
	else
	{
		BindToAttributeChanges();
	}
}

void UBA_WidgetComponent::OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	AttributeSet = Cast<UBA_AttributeSet>(AS);
	AbilitySystemComponent = Cast<UBA_AbilitySystemComponent>(ASC);

	if (!IsASCInitialized()) return;
	
	InitializeAttributeDelegate();
}

void UBA_WidgetComponent::BindToAttributeChanges()
{
	for (const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair : AttributeMap)
	{
		BindWidgetToAttributeChanges(GetUserWidgetObject(), Pair); // For checking the Owned Widget Object

		GetUserWidgetObject()->WidgetTree->ForEachWidget([this, &Pair](UWidget* ChildWidget)
		{
			BindWidgetToAttributeChanges(ChildWidget, Pair);
		});
	}
}

void UBA_WidgetComponent::BindWidgetToAttributeChanges(UWidget* WidgetObject, const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const
{
	UBA_AttributeWidget* AttributeWidget = Cast<UBA_AttributeWidget>(WidgetObject);
	if (!IsValid(AttributeWidget)) return; // We only care about BA_AttributeWidgets
	if (!AttributeWidget->MatchesAttributes(Pair)) return; // Only subscribe for matching attributes

	AttributeWidget->AvatarActor = Character;
	AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get(), 0.f); // For initial values

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Key).AddLambda([this, AttributeWidget, &Pair](const FOnAttributeChangeData& AttributeChangeData)
	{
		AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get(), AttributeChangeData.OldValue); // For changes during the game
	});
}

