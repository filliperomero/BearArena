// Copyright Fillipe Romero. All Rights Reserved.

#include "AbilitySystem/Abilities/Player/BA_Primary.h"

#include "AbilitySystemBlueprintLibrary.h"

void UBA_Primary::SendEventToActors(const TArray<AActor*>& Actors, const FGameplayTag EventTag)
{
	for (AActor* HitActor : Actors)
	{
		FGameplayEventData Payload;
		Payload.Instigator = GetAvatarActorFromActorInfo();
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor, EventTag, Payload);
	}
}
