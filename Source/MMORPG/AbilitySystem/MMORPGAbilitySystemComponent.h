// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "NativeGameplayTags.h"
#include "Utils/MMORPGEnums.h"
#include "Utils/MMORPGDelegates.h"
#include "MMORPGAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FReceivedDamageDelegate, UMMORPGAbilitySystemComponent*, InSource, float, InUnmitigatedDamage, float, InMitigatedDamage);

UCLASS()
class MMORPG_API UMMORPGAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	UMMORPGAbilitySystemComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	bool bIsCharacterAbilitiesGiven = false;
	bool bIsStartupEffectsApplied = false;

	FReceivedDamageDelegate ReceivedDamageDelegate;

	virtual void ReceiveDamage(UMMORPGAbilitySystemComponent* InSource, float InUnmitigatedDamage, float InMitigatedDamage);
protected:
	int32 ActivationGroupCount[(uint8)EMMORPGAbilityActivationGroup::MAX];
};