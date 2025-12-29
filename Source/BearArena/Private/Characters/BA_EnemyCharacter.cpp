// Copyright Fillipe Romero. All Rights Reserved.

#include "Characters/BA_EnemyCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/BA_AbilitySystemComponent.h"
#include "AbilitySystem/BA_AttributeSet.h"
#include "GameplayTags/BA_Tags.h"
#include "Net/UnrealNetwork.h"
#include "Runtime/AIModule/Classes/AIController.h"

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

void ABA_EnemyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, bIsBeingLaunched);
}

void ABA_EnemyCharacter::StopMovementUntilLanded()
{
	bIsBeingLaunched = true;
	
	AAIController* AIController = GetController<AAIController>();
	
	if (!IsValid(AIController)) return;
	
	AIController->StopMovement();
	
	if (!LandedDelegate.IsAlreadyBound(this, &ThisClass::EnableMovementOnLanded))
	{
		LandedDelegate.AddDynamic(this, &ThisClass::EnableMovementOnLanded);
	}
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

void ABA_EnemyCharacter::HandleDeath()
{
	Super::HandleDeath();
	
	AAIController* AIController = GetController<AAIController>();
	
	if (!IsValid(AIController)) return;
	
	AIController->StopMovement();
}

void ABA_EnemyCharacter::EnableMovementOnLanded(const FHitResult& HitResult)
{
	bIsBeingLaunched = false;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, BATags::Events::Enemy::EndAttack, FGameplayEventData());
	LandedDelegate.RemoveAll(this);
}

