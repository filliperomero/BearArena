// Copyright Fillipe Romero. All Rights Reserved.

#include "AbilitySystem/AbilityTasks/BA_WaitGameplayEvent.h"

UBA_WaitGameplayEvent* UBA_WaitGameplayEvent::WaitGameplayEventToActorProxy(AActor* TargetActor, FGameplayTag EventTag, bool OnlyTriggerOnce, bool OnlyMatchExact)
{
	UBA_WaitGameplayEvent* MyObj = NewObject<UBA_WaitGameplayEvent>();
	MyObj->SetAbilityActor(TargetActor);
	MyObj->Tag = EventTag;
	MyObj->OnlyTriggerOnce = OnlyTriggerOnce;
	MyObj->OnlyMatchExact = OnlyMatchExact;
	return MyObj;
}

void UBA_WaitGameplayEvent::StartActivation()
{
	Activate();
}
