// Fill out your copyright notice in the Description page of Project Settings.


#include "SCombatAttributeSet.h"
#include "../../Engine/Public/Net/UnrealNetwork.h"

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
