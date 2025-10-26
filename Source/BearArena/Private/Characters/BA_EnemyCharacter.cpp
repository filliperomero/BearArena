// Copyright Fillipe Romero. All Rights Reserved.

#include "Characters/BA_EnemyCharacter.h"
#include "AbilitySystem/BA_AbilitySystemComponent.h"
#include "AbilitySystem/BA_AttributeSet.h"

ABA_EnemyCharacter::ABA_EnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UBA_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UBA_AttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ABA_EnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ABA_EnemyCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

void ABA_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(GetAbilitySystemComponent())) return;

	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());

	if (!HasAuthority()) return;

	GiveStartupAbilities();
	InitializeAttributes();

	if (UBA_AttributeSet* BA_AttributeSet = Cast<UBA_AttributeSet>(GetAttributeSet()))
	{
		GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(BA_AttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
	}
}

