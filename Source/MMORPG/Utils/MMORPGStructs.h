// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "MMORPGStructs.generated.h"

USTRUCT(BlueprintType, Category = "UI")
struct FSettingsStruct
{
	GENERATED_BODY()

	UPROPERTY()
	float Volume;
};