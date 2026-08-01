// Fill out your copyright notice in the Description page of Project Settings.


#include "SAbilitySystemComponent.h"
#include "GameplayAbilitySystem/Characters/SCharacterBase.h"

void USAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();

	ASCharacterBase* Character = Cast<ASCharacterBase>(GetOwner());  // TODO: better remove this dependencies 

	if (!Character) return;

	Character->SendAbilitiesChangedEvent();
}
