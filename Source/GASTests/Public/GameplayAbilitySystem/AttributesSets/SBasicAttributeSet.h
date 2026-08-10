// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "SBasicAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class GASTESTS_API USBasicAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	USBasicAttributeSet();

	// Health Attribute
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS_BASIC(USBasicAttributeSet, Health); // This Macro give as getters and setters for Attributes

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS_BASIC(USBasicAttributeSet, MaxHealth); 

	// Stamina Attribute
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing=OnRep_Stamina)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS_BASIC(USBasicAttributeSet, Stamina); 

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing=OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS_BASIC(USBasicAttributeSet, MaxStamina); 

	// Damage
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Damage; // temporary damage what will spread between attributes 
	ATTRIBUTE_ACCESSORS_BASIC(USBasicAttributeSet, Damage);

	// Shield Attribute
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing=OnRep_Shield)
	FGameplayAttributeData Shield;
	ATTRIBUTE_ACCESSORS_BASIC(USBasicAttributeSet, Shield); // This Macro give as getters and setters for Attributes

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing=OnRep_MaxShield)
	FGameplayAttributeData MaxShield;
	ATTRIBUTE_ACCESSORS_BASIC(USBasicAttributeSet, MaxShield);

protected:

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(USBasicAttributeSet, Health, OldValue);
	}

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(USBasicAttributeSet, MaxHealth, OldValue);
	}
	
	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(USBasicAttributeSet, Stamina, OldValue);
	}
	
	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(USBasicAttributeSet, MaxStamina, OldValue);
	}

	UFUNCTION()
	void OnRep_Shield(const FGameplayAttributeData OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(USBasicAttributeSet, Shield, OldValue);
	}

	UFUNCTION()
	void OnRep_MaxShield(const FGameplayAttributeData OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(USBasicAttributeSet, MaxShield, OldValue);
	}
	

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	
};
