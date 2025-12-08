// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BA_Projectile.generated.h"

class UGameplayEffect;
class UProjectileMovementComponent;

UCLASS()
class BEARARENA_API ABA_Projectile : public AActor
{
	GENERATED_BODY()

public:
	ABA_Projectile();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BearArena|Damage", meta = (ExposeOnSpawn, ClampMin = "0.0"))
	float Damage { 5.f };
	
	UFUNCTION(BlueprintImplementableEvent, Category = "BearArena|Projectile")
	void SpawnImpactEffects();
	
private:
	UPROPERTY(VisibleAnywhere, Category = "BearArena|Projectile")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
	
	UPROPERTY(EditDefaultsOnly, Category = "BearArena|Damage")
	TSubclassOf<UGameplayEffect> DamageEffect;
};
