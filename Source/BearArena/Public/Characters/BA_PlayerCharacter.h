// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BA_BaseCharacter.h"
#include "BA_PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class BEARARENA_API ABA_PlayerCharacter : public ABA_BaseCharacter
{
	GENERATED_BODY()

public:
	ABA_PlayerCharacter();

private:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<UCameraComponent> FollowCamera;
};
