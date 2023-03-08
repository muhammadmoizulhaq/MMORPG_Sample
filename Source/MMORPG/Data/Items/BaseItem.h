// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Data/MMORPGAssetManager.h"
#include "BaseItem.generated.h"

UCLASS(Abstract, BlueprintType)
class MMORPG_API UBaseItem : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UBaseItem() {  }
	/** Type of this item, set in native parent class */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data|Item")
	FPrimaryAssetType ItemType;
	/** Returns the logical name, equivalent to the primary asset id */
	UFUNCTION(BlueprintCallable, Category = Item)
	FString GetIdentifierString() const;
	/** Overridden to use saved type */
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};