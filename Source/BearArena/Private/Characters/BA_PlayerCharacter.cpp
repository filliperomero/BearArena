// Copyright Fillipe Romero. All Rights Reserved.

#include "BearArena/Public/Characters/BA_PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/BA_AttributeSet.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/BA_PlayerState.h"

ABA_PlayerCharacter::ABA_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	Tags.Add(BearArenaTags::Player);
}

UAbilitySystemComponent* ABA_PlayerCharacter::GetAbilitySystemComponent() const
{
	const ABA_PlayerState* BA_PlayerState = GetPlayerState<ABA_PlayerState>();

	if (!IsValid(BA_PlayerState)) return nullptr;

	return BA_PlayerState->GetAbilitySystemComponent();
}

UAttributeSet* ABA_PlayerCharacter::GetAttributeSet() const
{
	const ABA_PlayerState* BA_PlayerState = GetPlayerState<ABA_PlayerState>();

	if (!IsValid(BA_PlayerState)) return nullptr;

	return BA_PlayerState->GetAttributeSet();
}

void ABA_PlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init Ability Actor Info for the Server
	if (!IsValid(GetAbilitySystemComponent()) || !HasAuthority()) return;

	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());
	GiveStartupAbilities();
	InitializeAttributes();

	if (UBA_AttributeSet* BA_AttributeSet = Cast<UBA_AttributeSet>(GetAttributeSet()))
	{
		GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(BA_AttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
	}
}

void ABA_PlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init Ability Actor Info for the Client
	if (!IsValid(GetAbilitySystemComponent())) return;

	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());

	if (UBA_AttributeSet* BA_AttributeSet = Cast<UBA_AttributeSet>(GetAttributeSet()))
	{
		GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(BA_AttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
	}
}
