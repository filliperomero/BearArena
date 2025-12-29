// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BA_BlueprintLibrary.generated.h"

struct FGameplayTag;
struct FGameplayEventData;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EHitDirection : uint8
{
	Left,
	Right,
	Front,
	Back
};

USTRUCT(BlueprintType)
struct FClosestActorWithTagResult
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<AActor> Actor;

	UPROPERTY(BlueprintReadWrite)
	float Distance { 0.f };
};

UCLASS()
class BEARARENA_API UBA_BlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "BearArena")
	static EHitDirection GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator);

	UFUNCTION(BlueprintPure, Category = "BearArena")
	static FName GetHitDirectionName(const EHitDirection& HitDirection);

	UFUNCTION(BlueprintCallable, Category = "BearArena")
	static FClosestActorWithTagResult FindClosestActorWithTag(const UObject* WorldContextObject, const FVector& Origin, const FName& Tag);
	
	UFUNCTION(BlueprintCallable, Category = "BearArena")
	static void SendDamageEventToPlayer(AActor* Target, const TSubclassOf<UGameplayEffect>& DamageEffect, UPARAM(ref) FGameplayEventData& Payload, const FGameplayTag& DataTag, float Damage, UObject* OptionalParticleSystem = nullptr);
	
	UFUNCTION(BlueprintCallable, Category = "BearArena|Abilities")
	static TArray<AActor*> HitBoxOverlapTest(AActor* AvatarActor, float HitBoxRadius, float HitBoxForwardOffset = 0.f, float HitBoxElevationOffset = 0.f, bool bDrawDebugs = false);
	
	static void DrawHitBoxOverlapDebugs(const UObject* WorldContextObject, const TArray<FOverlapResult>& OverlapResults, const FVector& HitBoxLocation, float HitBoxRadius);
};
