// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/MMORPGGameInstance.h"

DEFINE_LOG_CATEGORY(MMORPGGameInstance);

void UMMORPGGameInstance::Init()
{
	// Register delegate for ticker callback
	TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UMMORPGGameInstance::Tick));
	// Parent
	Super::Init();
}

void UMMORPGGameInstance::Shutdown()
{
	// Unregister ticker delegate
	FTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);
	// Parent
	Super::Shutdown();
}

bool UMMORPGGameInstance::Tick(float InDeltaTime)
{
	UE_LOG(MMORPGGameInstance, Log, TEXT("FrameRate: %f"), 1.0 / InDeltaTime);
	return true;
}