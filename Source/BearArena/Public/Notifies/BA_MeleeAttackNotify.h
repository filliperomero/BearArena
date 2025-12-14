// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "BA_MeleeAttackNotify.generated.h"

UCLASS()
class BEARARENA_API UBA_MeleeAttackNotify : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	
private:
	UPROPERTY(EditAnywhere, Category = "BearArena|Debugs")
	bool bDrawDebugs { true };
	
	UPROPERTY(EditAnywhere, Category = "BearArena|Socket")
	FName SocketName { "FX_Trail_01_R" };
	
	UPROPERTY(EditAnywhere, Category = "BearArena|Socket")
	float SocketExtensionOffset { 40.f };
	
	UPROPERTY(EditAnywhere, Category = "BearArena|Socket")
	float SphereTraceRadius { 60.f };
	
	TArray<FHitResult> PerformSphereTrace(USkeletalMeshComponent* MeshComp) const;
	void SendEventsToActors(USkeletalMeshComponent* MeshComp, const TArray<FHitResult>& Hits) const;
};
