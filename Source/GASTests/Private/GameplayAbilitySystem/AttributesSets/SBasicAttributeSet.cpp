// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/AttributesSets/SBasicAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"

USBasicAttributeSet::USBasicAttributeSet()
{
	Health = 100.f;
	MaxHealth = 100.f;
	Stamina = 100.f;
	MaxStamina = 100.f;
	Damage = 0.0f;
	Shield = 0.0f;
	MaxShield = 100.0f;
}

void USBasicAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(USBasicAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USBasicAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USBasicAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USBasicAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
}

void USBasicAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) // Clamp of attribute values changed
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxHealth());
	}
	else if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxStamina());
	}
	else if (Attribute == GetShieldAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxShield());
	}


}

void USBasicAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) // Clamp of attributes changed by EffectExecution
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		float TotalDamage = GetDamage();
		SetDamage(0.f);

		float CurrentShield = GetShield();
		if (CurrentShield > 0.0f)
		{
			SetShield(GetShield() - TotalDamage);
			float RemainingDamage = TotalDamage - CurrentShield;

			if (RemainingDamage > 0.0f)
			{
				SetHealth(RemainingDamage);
			}
		}
		else
		{
			SetHealth(GetHealth() - TotalDamage);
		}
				

		if (Data.EffectSpec.Def->GetAssetTags().HasTag(FGameplayTag::RequestGameplayTag("Effects.HitReaction")) && Data.EvaluatedData.Magnitude != 0.f) // If GameplayEffect has tag we notifying about damage
		{
			FGameplayTagContainer HitReactionTagContainer;
			HitReactionTagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("GameplayAbility.HitReaction")));
			GetOwningAbilitySystemComponent()->TryActivateAbilitiesByTag(HitReactionTagContainer);
		}
	}



	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(GetHealth()); // it will call PreAttributeChange that will clamp Attribute values for us
	}
	else if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(GetStamina());
	}
}

void USBasicAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetHealthAttribute() && NewValue <= 0.f)
	{
		FGameplayTagContainer DeathAbilityTagContainer;
		DeathAbilityTagContainer.AddTag(FGameplayTag::RequestGameplayTag("GameplayAbility.Death"));
		GetOwningAbilitySystemComponent()->TryActivateAbilitiesByTag(DeathAbilityTagContainer);
	}

}
