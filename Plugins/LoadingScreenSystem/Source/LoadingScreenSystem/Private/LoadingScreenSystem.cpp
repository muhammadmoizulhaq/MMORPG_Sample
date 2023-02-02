// Copyright Epic Games, Inc. All Rights Reserved.

#include "LoadingScreenSystem.h"
#include "MoviePlayer.h"
#include "SLoadingLayout.h"
#include "Framework/Application/SlateApplication.h"

#define LOCTEXT_NAMESPACE "FLoadingScreenSystemModule"

void FLoadingScreenSystemModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	if (!IsRunningDedicatedServer() && FSlateApplication::IsInitialized())
	{
		UE_LOG(LogTemp, Warning, TEXT("Loading Screen Starting Up"));
		if (IsMoviePlayerEnabled())
		{
			GetMoviePlayer()->OnPrepareLoadingScreen().AddRaw(this, &FLoadingScreenSystemModule::PreLoadingScreenSetup);
		}
		LoadingScreenSetup();
	}
}

void FLoadingScreenSystemModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	if (!IsRunningDedicatedServer())
	{
		UE_LOG(LogTemp, Warning, TEXT("Loading Screen Shutting Down"));
		GetMoviePlayer()->OnPrepareLoadingScreen().RemoveAll(this);
	}
}

bool FLoadingScreenSystemModule::IsGameModule() const
{
	return true;
}

void FLoadingScreenSystemModule::PreLoadingScreenSetup()
{
	LoadingScreenSetup();
}

void FLoadingScreenSystemModule::LoadingScreenSetup()
{
	FLoadingScreenAttributes LoadingScreen;
	LoadingScreen.WidgetLoadingScreen = SNew(SLoadingLayout);
	GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLoadingScreenSystemModule, LoadingScreenSystem)