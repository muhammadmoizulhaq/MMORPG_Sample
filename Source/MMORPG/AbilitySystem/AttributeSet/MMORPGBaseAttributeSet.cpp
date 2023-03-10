// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/AttributeSet/MMORPGBaseAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UMMORPGBaseAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMMORPGBaseAttributeSet, Health, OldHealth);
}

void UMMORPGBaseAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMMORPGBaseAttributeSet, MaxHealth, OldMaxHealth);
}

void UMMORPGBaseAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMMORPGBaseAttributeSet, Mana, OldMana);
}

void UMMORPGBaseAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMMORPGBaseAttributeSet, MaxMana, OldMaxMana);
}

void UMMORPGBaseAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UMMORPGBaseAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMMORPGBaseAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMMORPGBaseAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMMORPGBaseAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}