// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class GASTESTS_API USAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

protected:

	TArray<FGameplayAbilitySpec> LastActivatableAbilities;
	
protected:

	virtual void OnRep_ActivateAbilities() override;
};
