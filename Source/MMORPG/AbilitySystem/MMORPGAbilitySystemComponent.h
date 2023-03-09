// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "NativeGameplayTags.h"
#include "Utils/MMORPGEnums.h"
#include "MMORPGAbilitySystemComponent.generated.h"

UCLASS()
class MMORPG_API UMMORPGAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	UMMORPGAbilitySystemComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
protected:
	int32 ActivationGroupCount[(uint8)EMMORPGAbilityActivationGroup::MAX];
};