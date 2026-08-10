// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "SCombatAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class GASTESTS_API USCombatAttributeSet : public UAttributeSet
{
	GENERATED_BODY()


public:

	USCombatAttributeSet();

	// Armor Attribute
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing=OnRep_Armor)
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS_BASIC(USCombatAttributeSet, Armor); // This Macro give as getters and setters for Attributes

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing=OnRep_MaxArmor)
	FGameplayAttributeData MaxArmor;
	ATTRIBUTE_ACCESSORS_BASIC(USCombatAttributeSet, MaxArmor);

	// Strenght Attribute
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing=OnRep_Strenght)
	FGameplayAttributeData Strenght;
	ATTRIBUTE_ACCESSORS_BASIC(USCombatAttributeSet, Strenght);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing=OnRep_MaxStrenght)
	FGameplayAttributeData MaxStrenght;
	ATTRIBUTE_ACCESSORS_BASIC(USCombatAttributeSet, MaxStrenght);

protected:

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(USCombatAttributeSet, Armor, OldValue);
	}

	UFUNCTION()
	void OnRep_MaxArmor(const FGameplayAttributeData OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(USCombatAttributeSet, MaxArmor, OldValue);
	}
	
	UFUNCTION()
	void OnRep_Strenght(const FGameplayAttributeData OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(USCombatAttributeSet, Strenght, OldValue);
	}
	
	UFUNCTION()
	void OnRep_MaxStrenght(const FGameplayAttributeData OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(USCombatAttributeSet, MaxStrenght, OldValue);
	}

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
};
