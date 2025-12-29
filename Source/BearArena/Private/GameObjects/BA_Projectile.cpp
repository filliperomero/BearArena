// Copyright Fillipe Romero. All Rights Reserved.

#include "GameObjects/BA_Projectile.h"

#include "AbilitySystemComponent.h"
#include "Characters/BA_PlayerCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameplayTags/BA_Tags.h"
#include "Utils/BA_BlueprintLibrary.h"

ABA_Projectile::ABA_Projectile()
{
	PrimaryActorTick.bCanEverTick = false;
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	
	bReplicates = true;
}

void ABA_Projectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	ABA_PlayerCharacter* PlayerCharacter = Cast<ABA_PlayerCharacter>(OtherActor);
	if (!IsValid(PlayerCharacter) || !PlayerCharacter->IsAlive()) return;
	
	if (!HasAuthority()) return;
	
	FGameplayEventData Payload;
	Payload.Instigator = GetOwner();
	Payload.Target = PlayerCharacter;
	
	UBA_BlueprintLibrary::SendDamageEventToPlayer(PlayerCharacter, DamageEffect, Payload, BATags::SetByCaller::Projectile, Damage, BATags::None);
	
	SpawnImpactEffects();
	Destroy();
}
