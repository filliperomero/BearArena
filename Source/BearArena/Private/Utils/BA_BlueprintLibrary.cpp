// Copyright Fillipe Romero. All Rights Reserved.

#include "Utils/BA_BlueprintLibrary.h"

EHitDirection UBA_BlueprintLibrary::GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator)
{
	const float DotProduct = FVector::DotProduct(TargetForward, ToInstigator);

	if (DotProduct < -0.5f) return EHitDirection::Back;

	// Either Left or Right
	if (DotProduct < 0.5f)
	{
		const FVector CrossProduct = FVector::CrossProduct(TargetForward, ToInstigator);
		if (CrossProduct.Z < 0.f) return EHitDirection::Left;

		return EHitDirection::Right;
	}

	return EHitDirection::Front;
}

FName UBA_BlueprintLibrary::GetHitDirectionName(const EHitDirection& HitDirection)
{
	switch (HitDirection)
	{
		case EHitDirection::Left: return FName("Left");
		case EHitDirection::Right: return FName("Right");
		case EHitDirection::Front: return FName("Front");
		case EHitDirection::Back: return FName("Back");
		default: return FName("None");
	}
}
