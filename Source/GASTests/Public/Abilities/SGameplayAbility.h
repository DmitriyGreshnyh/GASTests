// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	None UMETA(DisplayName = "None"),
	PrimaryAbility UMETA(DisplayName= "PrimaryAbility"),
	SecondaryAbility UMETA(DisplayName = "SecondaryAbility"),
	DefensiveAbility UMETA(DisplayName = "DefenciveAbility"),
	MovementAbility UMETA(DisplayName = "MovementAbility"),
};

/**
 Basic class for all Abilities in game 
 */
UCLASS()
class GASTESTS_API USGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()


public:

	USGameplayAbility();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	bool ShouldShowInAbilitiesBar = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Activation")
	bool AutoActivateOnGranted = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	EAbilityInputID AbilityInputID = EAbilityInputID::None;

	UFUNCTION(BlueprintCallable)
	bool IsControlledByPlayer() const;
};
