// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MMORPGGameInstance.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(MMORPGGameInstance, Log, All);

UCLASS()
class MMORPG_API UMMORPGGameInstance : public UGameInstance
{
	GENERATED_BODY()
private:
	FDelegateHandle TickDelegateHandle;
protected:
	virtual void Init() override;
	virtual void Shutdown() override;
	bool Tick(float InDeltaTime);
};