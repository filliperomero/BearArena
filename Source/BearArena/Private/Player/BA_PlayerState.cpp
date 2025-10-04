// Copyright Fillipe Romero. All Rights Reserved.

#include "Player/BA_PlayerState.h"
#include "AbilitySystem/BA_AbilitySystemComponent.h"

ABA_PlayerState::ABA_PlayerState()
{
	SetNetUpdateFrequency(100.f);

	AbilitySystemComponent = CreateDefaultSubobject<UBA_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* ABA_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
