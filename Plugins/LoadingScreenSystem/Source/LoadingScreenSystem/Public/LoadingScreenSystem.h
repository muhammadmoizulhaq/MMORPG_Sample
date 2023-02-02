// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FLoadingScreenSystemModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	virtual bool IsGameModule() const override;
	static inline FLoadingScreenSystemModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FLoadingScreenSystemModule>("LoadingScreenSystem");
	}
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("LoadingScreenSystem");
	}
private:
	void PreLoadingScreenSetup();
	void LoadingScreenSetup();
};
