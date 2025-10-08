// Copyright Fillipe Romero. All Rights Reserved.

#include "UI/BA_WidgetComponent.h"

#include "AbilitySystem/BA_AbilitySystemComponent.h"
#include "AbilitySystem/BA_AttributeSet.h"
#include "Characters/BA_BaseCharacter.h"

void UBA_WidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	InitAbilitySystemData();

	if (!IsASCInitialized())
	{
		Character = Cast<ABA_BaseCharacter>(GetOwner());
		Character->OnASCInitialized.AddDynamic(this, &ThisClass::OnASCInitialized);
	}
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

void UBA_WidgetComponent::OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	AttributeSet = Cast<UBA_AttributeSet>(AS);
	AbilitySystemComponent = Cast<UBA_AbilitySystemComponent>(ASC);
}

