// Fill out your copyright notice in the Description page of Project Settings.


#include "SAbilitySystemComponent.h"
#include "GameplayAbilitySystem/Characters/SCharacterBase.h"

void USAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();

	ASCharacterBase* Character = Cast<ASCharacterBase>(GetOwner());  // TODO: better remove this dependencies 

	if (!Character) return;

	bool bAbilitiesChanged = false;

	// Check if count or abilities changed
	if (LastActivatableAbilities.Num() != ActivatableAbilities.Items.Num())
	{
		bAbilitiesChanged = true;
	}
	else
	{
		for (int i = 0; i < LastActivatableAbilities.Num(); i++)
		{
			if (LastActivatableAbilities[i].Ability != ActivatableAbilities.Items[i].Ability)
			{
				bAbilitiesChanged = true;
				break;
			}
		}
	}


	// 
	if (bAbilitiesChanged)
	{
		Character->SendAbilitiesChangedEvent();
		LastActivatableAbilities = ActivatableAbilities.Items;
	}
}
