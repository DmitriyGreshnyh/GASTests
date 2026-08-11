// Fill out your copyright notice in the Description page of Project Settings.


#include "SCombatAttributeSet.h"
#include "../../Engine/Public/Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"

USCombatAttributeSet::USCombatAttributeSet()
{
	Armor = 0.f;
	MaxArmor = 100.f;
	Strenght = 0.f;
	MaxStrenght = 100.f;
}

void USCombatAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(USCombatAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCombatAttributeSet, MaxArmor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCombatAttributeSet, Strenght, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCombatAttributeSet, MaxStrenght, COND_None, REPNOTIFY_Always);
}

void USCombatAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetArmorAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxArmor());
	}
	else if (Attribute == GetStrenghtAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxStrenght());
	}
}

void USCombatAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetArmorAttribute())
	{
		SetArmor(GetArmor()); // it will call PreAttributeChange that will clamp Attribute values for us
	}
	else if (Data.EvaluatedData.Attribute == GetStrenghtAttribute())
	{
		SetStrenght(GetStrenght());
	}
}
