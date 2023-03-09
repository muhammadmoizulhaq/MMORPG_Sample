// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "MMORPGEnums.generated.h"

UENUM(BlueprintType, Category = "Platforms")
enum class EPlatformEnum : uint8
{
	NONE = 0 UMETA(DisplayName = "None"),
	WINDOW = 1 UMETA(DisplayName = "Window"),
};

UENUM(BlueprintType, Category = "UI")
enum class EWidgetEnum : uint8
{
	NONE = 0 UMETA(DisplayName = "None"),
	MAINMENU = 1 UMETA(DisplayName = "Main Menu"),
};

UENUM(BlueprintType, Category = "UI")
enum class EPopUpEnum : uint8
{
	NONE = 0 UMETA(DisplayName = "None"),
	LOADING = 1 UMETA(DisplayName = "Loading"),
};

/**
 * EMMORPGbilityActivationGroup
 *
 *	Defines how an ability activates in relation to other abilities.
 */
UENUM(BlueprintType)
enum class EMMORPGAbilityActivationGroup : uint8
{
	// Ability runs independently of all other abilities.
	Independent,

	// Ability is canceled and replaced by other exclusive abilities.
	Exclusive_Replaceable,

	// Ability blocks all other exclusive abilities from activating.
	Exclusive_Blocking,

	MAX	UMETA(Hidden)
};