// Fill out your copyright notice in the Description page of Project Settings.

#include "MMORPGHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

DEFINE_LOG_CATEGORY(MMORPGHUD);

void AMMORPGHUD::BeginPlay()
{
	Super::BeginPlay();
}

void AMMORPGHUD::SetWidgets(TArray<TSoftClassPtr<UObject>> InWidgets)
{
	MyWidgets = InWidgets;
	MyWidgetMap.Reserve(InWidgets.Num());
	for (int32 i = 0; i < InWidgets.Num(); i++)
	{
		MyWidgetMap.Add((EWidgetEnum)i, InWidgets[i]);
		UE_LOG(MMORPGHUD, Warning, TEXT("%s added to Map"), *InWidgets[i].GetAssetName());
	}
}

void AMMORPGHUD::SetPopUps(TArray<TSoftClassPtr<UObject>> InPopUps)
{
	MyPopUps = InPopUps;
	MyWidgetMap.Reserve(InPopUps.Num());
	for (int32 i = 0; i < InPopUps.Num(); i++)
	{
		MyPopUpMap.Add((EPopUpEnum)i, InPopUps[i]);
	}
}

TArray<TSoftClassPtr<UObject>> AMMORPGHUD::GetWidgets()
{
	TSoftClassPtr<UObject>* WidgetClass;
	for (int i = 0; i <= MyWidgetMap.Num(); i++)
	{
		WidgetClass = MyWidgetMap.Find((EWidgetEnum)i);
		MyWidgets.Add(*WidgetClass);
	}
	return MyWidgets;
}

TArray<TSoftClassPtr<UObject>> AMMORPGHUD::GetPopUps()
{
	TSoftClassPtr<UObject>* PopUpClass;
	for (int i = 0; i <= MyPopUpMap.Num(); i++)
	{
		PopUpClass = MyPopUpMap.Find((EPopUpEnum)i);
		MyPopUps.Add(*PopUpClass);
	}
	return MyPopUps;
}

void AMMORPGHUD::SetCurrentWidgetEnum(EWidgetEnum InWidget)
{
	MyCurrentWidgetEnum = InWidget;
}

void AMMORPGHUD::SetCurrentPopUpEnum(EPopUpEnum InPopUp)
{
	MyCurrentPopUpEnum = InPopUp;
}

EWidgetEnum AMMORPGHUD::GetCurrentWidgetEnum()
{
	return MyCurrentWidgetEnum;
}

EPopUpEnum AMMORPGHUD::GetCurrentPopUpEnum()
{
	return MyCurrentPopUpEnum;
}

void AMMORPGHUD::SetCurrentWidget(UUserWidget* InWidget)
{
	MyCurrentWidget = InWidget;
}

void AMMORPGHUD::SetCurrentPopUp(UUserWidget* InPopUp)
{
	MyCurrentPopUp = InPopUp;
}

UUserWidget* AMMORPGHUD::GetCurrentWidget()
{
	return MyCurrentWidget;
}

UUserWidget* AMMORPGHUD::GetCurrentPopUp()
{
	return MyCurrentPopUp;
}

UUserWidget* AMMORPGHUD::ShowWidgets(EWidgetEnum InWidgets, EPopUpEnum InPopUps, bool bShowMouseCursor, bool bDisableInput)
{
	UE_LOG(MMORPGHUD, Log, TEXT("Show Widget"));
	if (InWidgets == GetCurrentWidgetEnum())
	{
		return GetCurrentWidget();
	}
	TSubclassOf<UUserWidget> MyWidget;
	TSubclassOf<UUserWidget> MyPopUp;
	GetWidgetsToLoad(InWidgets, InPopUps, MyWidget, MyPopUp);
	if (MyWidgetMap.Contains(InWidgets))
	{
		SetCurrentWidget(Cast<UUserWidget>(MyWidget));
		GetCurrentWidget()->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		GetCurrentWidget()->Initialize();
	}
	else
	{
		SetCurrentWidget(CreateWidget<UUserWidget>(UGameplayStatics::GetGameInstance(GetWorld()), MyWidget));
		//MyWidgetMap.Add(InWidgets, *GetCurrentWidget());
		GetCurrentWidget()->AddToViewport();
		GetCurrentWidget()->Initialize();
	}
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(bShowMouseCursor);
	if (bDisableInput)
	{
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(UGameplayStatics::GetPlayerController(GetWorld(), 0), Cast<UWidget>(GetCurrentWidget()), EMouseLockMode::DoNotLock);
		SetCurrentWidgetEnum(InWidgets);
		return GetCurrentWidget();
	}
	else
	{
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(UGameplayStatics::GetPlayerController(GetWorld(), 0), nullptr, EMouseLockMode::DoNotLock, false);
		SetCurrentWidgetEnum(InWidgets);
		return GetCurrentWidget();
	}
	HideWidgets(EWidgetEnum::NONE, false);
	if (MyPopUpMap.Find(InPopUps) != nullptr)
	{
		SetCurrentPopUp(Cast<UUserWidget>(MyPopUp));
		GetCurrentPopUp()->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		GetCurrentPopUp()->Initialize();
		return GetCurrentPopUp();
	}
	switch (InPopUps)
	{
	case EPopUpEnum::NONE:
		return GetCurrentPopUp();
		break;
	case EPopUpEnum::LOADING:
		SetCurrentPopUp(CreateWidget<UUserWidget>(UGameplayStatics::GetGameInstance(GetWorld()), MyPopUp));
		break;
	default:
		break;
	}
	GetCurrentPopUp()->AddToViewport(10);
	//MyPopUpMap.Add(InPopUps, GetCurrentPopUp());
	GetCurrentPopUp()->Initialize();
	return GetCurrentPopUp();
}

void AMMORPGHUD::HideWidgets(EWidgetEnum InWidgets, bool bShowMouseCursor)
{
	UE_LOG(MMORPGHUD, Log, TEXT("Hide Widget"));
	if (MyWidgetMap.Contains(InWidgets))
	{
		//UUserWidget* Temp = Cast<UUserWidget>(MyWidgetMap.Find(InWidgets));
		if (GetCurrentWidget()->GetVisibility() == ESlateVisibility::SelfHitTestInvisible)
		{
			GetCurrentWidget()->SetVisibility(ESlateVisibility::Collapsed);
			GetCurrentWidget()->Destruct();
			SetCurrentWidgetEnum(EWidgetEnum::NONE);
			SetCurrentWidget(nullptr);
		}
	}
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(bShowMouseCursor);
	if (IsValid(GetCurrentPopUp()))
	{
		UE_LOG(MMORPGHUD, Warning, TEXT("Hide %s PopUp"), *GetCurrentPopUp()->GetName());
		if (GetCurrentPopUp()->GetVisibility() == ESlateVisibility::SelfHitTestInvisible)
		{
			GetCurrentPopUp()->SetVisibility(ESlateVisibility::Collapsed);
			GetCurrentPopUp()->Destruct();
		}
		SetCurrentPopUp(nullptr);
	}
}

void AMMORPGHUD::HideCurrentWidget()
{
	if (!GetCurrentWidget()) { return; }
	GetCurrentWidget()->SetVisibility(ESlateVisibility::Collapsed);
	SetCurrentWidgetEnum(EWidgetEnum::NONE);
	SetCurrentWidget(nullptr);
}

bool AMMORPGHUD::GetWidgetsToLoad(EWidgetEnum InWidget, EPopUpEnum InPopUp, TSubclassOf<UUserWidget>& OutWidget, TSubclassOf<UUserWidget>& OutPopUp)
{
	if (InWidget != EWidgetEnum::NONE)
	{
		MyWidgets[(uint8)InWidget - 1].LoadSynchronous();
		OutWidget = MyWidgets[(uint8)InWidget - 1].Get();
		return true;
	}
	if (InPopUp != EPopUpEnum::NONE)
	{
		MyPopUps[(uint8)InPopUp - 1].LoadSynchronous();
		OutPopUp = MyPopUps[(uint8)InPopUp - 1].Get();
		return true;
	}
	return false;
}