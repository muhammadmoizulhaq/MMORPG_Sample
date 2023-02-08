// Fill out your copyright notice in the Description page of Project Settings.
/**
* The class AHUD is a Class that is only available on each Client and can be accessed through the PlayerController. It will be automatically spawned.
* Before UMG (Unreal Motion Graphics) has been released, the HUD Class has been used to draw text, textures and more in the viewport of the Client.
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MMORPGStructs.h"
#include "MMORPGEnums.h"
#include "MMORPGHUD.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(MMORPGHUD, Log, All);

class UUserWidget;

UCLASS()
class MMORPG_API AMMORPGHUD : public AHUD
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY()
	TArray<TSoftClassPtr<UObject>> MyWidgets;
	UPROPERTY()
	TArray<TSoftClassPtr<UObject>> MyPopUps;
	UPROPERTY()
	EWidgetEnum MyCurrentWidgetEnum;
	UPROPERTY()
	EPopUpEnum MyCurrentPopUpEnum;
	UPROPERTY()
	UUserWidget* MyCurrentWidget;
	UPROPERTY()
	UUserWidget* MyCurrentPopUp;
	UPROPERTY()
	TMap<EWidgetEnum, TSoftClassPtr<UObject>> MyWidgetMap;
	UPROPERTY()
	TMap<EPopUpEnum, TSoftClassPtr<UObject>> MyPopUpMap;
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetWidgets(TArray<TSoftClassPtr<UObject>> InWidgets);
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetPopUps(TArray<TSoftClassPtr<UObject>> InPopUps);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UI")
	TArray<TSoftClassPtr<UObject>> GetWidgets();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UI")
	TArray<TSoftClassPtr<UObject>> GetPopUps();
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetCurrentWidgetEnum(EWidgetEnum InWidget);
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetCurrentPopUpEnum(EPopUpEnum InPopUp);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UI")
	EWidgetEnum GetCurrentWidgetEnum();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UI")
	EPopUpEnum GetCurrentPopUpEnum();
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetCurrentWidget(UUserWidget* InWidget);
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetCurrentPopUp(UUserWidget* InPopUp);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UI")
	UUserWidget* GetCurrentWidget();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UI")
	UUserWidget* GetCurrentPopUp();
	UFUNCTION(BlueprintCallable, Category = "UI")
	UUserWidget* ShowWidgets(EWidgetEnum InWidgets = EWidgetEnum::NONE, EPopUpEnum InPopUps = EPopUpEnum::NONE, bool bShowMouseCursor = false, bool bDisableInput = false);
	UFUNCTION(BlueprintCallable, Category = "UI")
	void HideWidgets(EWidgetEnum InWidgets = EWidgetEnum::NONE, bool bShowMouseCursor = false);
	UFUNCTION(BlueprintCallable, Category = "UI")
	void HideCurrentWidget();
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetWidgetsToLoad(EWidgetEnum InWidget, EPopUpEnum InPopUp, TSubclassOf<UUserWidget>& OutWidget, TSubclassOf<UUserWidget>& OutPopUp);
};