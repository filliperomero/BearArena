// Copyright Fillipe Romero. All Rights Reserved.

#include "GameplayTags/BA_Tags.h"

namespace BATags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(None, "BATags.None", "None");
	
	namespace Abilities
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven, "BATags.Abilities.ActivateOnGiven", "Tag for Abilities that should Activate immediately once given");
		
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "BATags.Abilities.Primary", "Tag for the Primary Ability");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary, "BATags.Abilities.Secondary", "Tag for the Secondary Ability");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tertiary, "BATags.Abilities.Tertiary", "Tag for the Tertiary Ability");

		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Death, "BATags.Abilities.Death", "Tag for the Death Ability");
		
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(BlockHitReact, "BATags.Abilities.BlockHitReact", "Tag blocking Hit react");

		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "BATags.Abilities.Enemy.HitReact", "Tag for the Enemy Hit React Ability");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attack, "BATags.Abilities.Enemy.Attack", "Tag for the Enemy Attack Ability");
		}
	}

	namespace Events
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(KillScored, "BATags.Events.KillScored", "Tag for the Skill Scored Event");
		
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "BATags.Events.Enemy.HitReact", "Tag for the Enemy Hit React Event");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(EndAttack, "BATags.Events.Enemy.EndAttack", "Tag for the Enemy End Attack Event");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(MeleeTraceHit, "BATags.Events.Enemy.MeleeTraceHit", "Tag for the Enemy Melee Trace Hit Event");
		}

		namespace Player
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "BATags.Events.Player.HitReact", "Tag for the Player Hit React Event");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Death, "BATags.Events.Player.Death", "Tag for the Player Death Event");
		}
	}

	namespace Status
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Dead, "BATags.Status.Dead", "Tag for when the character is dead");
	}
	
	namespace SetByCaller
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Projectile, "BATags.SetByCaller.Projectile", "Tag for Set by Caller Magnitude for Projectiles");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Melee, "BATags.SetByCaller.Melee", "Tag for Set by Caller Magnitude for Melee Attack");
		
		namespace Player
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary, "BATags.SetByCaller.Player.Secondary", "Tag for Set by Caller Magnitude for Player Secondary Ability");
		}
	}
}