// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Items/BaseItem.h"
#include "WidgetItem.generated.h"

UCLASS()
class MMORPG_API UWidgetItem : public UBaseItem
{
	GENERATED_BODY()
public:
	UWidgetItem()
	{
		ItemType = UMMORPGAssetManager::WidgetItemType;
	}
};