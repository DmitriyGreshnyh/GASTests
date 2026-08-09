// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GASTESTS_API USGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()


public:

	USGameplayAbility();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	bool ShouldShowInAbilitiesBar = false;

	UFUNCTION(BlueprintCallable)
	bool IsControlledByPlayer() const;
};
