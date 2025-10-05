// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BA_BlueprintLibrary.generated.h"

UENUM(BlueprintType)
enum class EHitDirection : uint8
{
	Left,
	Right,
	Forward,
	Back
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
};
