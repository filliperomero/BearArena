// Copyright Fillipe Romero. All Rights Reserved.

#include "Player/BA_PlayerState.h"

#include "AbilitySystemComponent.h"

ABA_PlayerState::ABA_PlayerState()
{
	SetNetUpdateFrequency(100.f);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* ABA_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
