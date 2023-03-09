// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Items/BaseItem.h"
#include "Utils/MMORPGEnums.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|Items|Widgets")
	TMap<EWidgetEnum, TSoftClassPtr<UUserWidget>> WidgetToShow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|Items|Popups")
	TMap<EPopUpEnum, TSoftClassPtr<UUserWidget>> PopupToShow;
};