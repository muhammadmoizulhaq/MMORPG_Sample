// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "MMORPGAssetManager.generated.h"

class UBaseItem;

UCLASS()
class MMORPG_API UMMORPGAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	// Constructor and overrides
	UMMORPGAssetManager() {  }
	virtual void StartInitialLoading() override;
	/** Static types for items */
	static const FPrimaryAssetType WidgetItemType;
	/** Returns the current AssetManager object */
	static UMMORPGAssetManager& Get();
	/**
	 * Synchronously loads an MMORPGItem subclass, this can hitch but is useful when you cannot wait for an async load
	 * This does not maintain a reference to the item so it will garbage collect if not loaded some other way
	 *
	 * @param PrimaryAssetId The asset identifier to load
	 * @param bDisplayWarning If true, this will log a warning if the item failed to load
	 */
	UBaseItem* ForceLoadItem(const FPrimaryAssetId& InPrimaryAssetId, bool bLogWarning = true);
};