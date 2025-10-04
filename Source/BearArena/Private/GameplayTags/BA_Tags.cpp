// Copyright Fillipe Romero. All Rights Reserved.

#include "GameplayTags/BA_Tags.h"

namespace BATags
{
	namespace Abilities
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven, "BATags.Abilities.ActivateOnGiven", "Tag for Abilities that should Activate immediately once given");
		
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "BATags.Abilities.Primary", "Tag for the Primary Ability");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary, "BATags.Abilities.Secondary", "Tag for the Secondary Ability");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tertiary, "BATags.Abilities.Tertiary", "Tag for the Tertiary Ability");

		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "BATags.Abilities.Enemy.HitReact", "Tag for the Enemy Hit React Ability");
		}
	}

	namespace Events
	{
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "BATags.Events.Enemy.HitReact", "Tag for the Enemy Hit React Event");
		}
	}
}