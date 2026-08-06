// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SGameplayAbility.h"

USGameplayAbility::USGameplayAbility()
{
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("GameplayAbility.Active")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag("State.Death"));
}
