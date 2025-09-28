// Copyright Fillipe Romero. All Rights Reserved.

#include "BearArena/Public/Characters/BA_BaseCharacter.h"

ABA_BaseCharacter::ABA_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// Tick and Refresh Bone transforms whether rendered or not - for bone updates on a dedicated server
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}
