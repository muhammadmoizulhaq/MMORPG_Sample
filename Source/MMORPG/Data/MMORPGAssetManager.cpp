// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/MMORPGAssetManager.h"
#include "AbilitySystemGlobals.h"
#include "BaseItem.h"

const FPrimaryAssetType UMMORPGAssetManager::WidgetItemType = TEXT("Widget");

UMMORPGAssetManager& UMMORPGAssetManager::Get()
{
	UMMORPGAssetManager* This = Cast<UMMORPGAssetManager>(GEngine->AssetManager);
	if (This)
	{
		return *This;
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("Invalid AssetManager in DefaultEngine.ini, must be MMORPGAssetManager!"));
		return *NewObject<UMMORPGAssetManager>();// never calls this
	}
}

void UMMORPGAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	UAbilitySystemGlobals::Get().InitGlobalData();
	UE_LOG(LogTemp, Warning, TEXT("Ability System Globals init!"));
}

UBaseItem* UMMORPGAssetManager::ForceLoadItem(const FPrimaryAssetId& InPrimaryAssetId, bool bLogWarning)
{
	FSoftObjectPath MyItemPath = GetPrimaryAssetPath(InPrimaryAssetId);
	FStreamableManager& MyStreamableManager = UMMORPGAssetManager::Get().GetStreamableManager();
	TSharedPtr<FStreamableHandle> MyStreamableHandle = MyStreamableManager.RequestAsyncLoad(MyItemPath, []() {
		UE_LOG(LogTemp, Warning, TEXT("Asset Loaded!"));
		},MyStreamableManager.AsyncLoadHighPriority);
	UBaseItem* MyLoadedItem = Cast<UBaseItem>(MyItemPath.ResolveObject());
	if (bLogWarning && MyLoadedItem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load item for identifier %s!"), *InPrimaryAssetId.ToString());
	}
	return MyLoadedItem;
}