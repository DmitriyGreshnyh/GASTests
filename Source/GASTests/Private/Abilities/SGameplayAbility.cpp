// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SGameplayAbility.h"

USGameplayAbility::USGameplayAbility()
{
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("GameplayAbility.Active")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag("State.Death"));
}

bool USGameplayAbility::IsControlledByPlayer() const
{
	const APawn* PawnObject = Cast<APawn>(GetAvatarActorFromActorInfo());

	if (!PawnObject) return false;

	return PawnObject->IsPlayerControlled();
}

void USGameplayAbility::SetAbilityLevel(int32 NewLevel)
{
	if(FGameplayAbilitySpec* AbilitySpec = GetCurrentAbilitySpec())
	{
		AbilitySpec->Level = NewLevel;
	}
}
