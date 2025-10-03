// Copyright Fillipe Romero. All Rights Reserved.

#include "Characters/BA_EnemyCharacter.h"

#include "AbilitySystemComponent.h"

ABA_EnemyCharacter::ABA_EnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

UAbilitySystemComponent* ABA_EnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABA_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(GetAbilitySystemComponent())) return;

	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);

	if (!HasAuthority()) return;

	GiveStartupAbilities();
}

