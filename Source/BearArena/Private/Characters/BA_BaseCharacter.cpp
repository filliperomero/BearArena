// Copyright Fillipe Romero. All Rights Reserved.

#include "BearArena/Public/Characters/BA_BaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"

ABA_BaseCharacter::ABA_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// Tick and Refresh Bone transforms whether rendered or not - for bone updates on a dedicated server
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

UAbilitySystemComponent* ABA_BaseCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}

void ABA_BaseCharacter::GiveStartupAbilities()
{
	check(IsValid(GetAbilitySystemComponent()));
	
	for (const auto& Ability : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability);

		GetAbilitySystemComponent()->GiveAbility(AbilitySpec);
	}
}
