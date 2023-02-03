// Fill out your copyright notice in the Description page of Project Settings.


#include "SLoadingLayout.h"
#include "Engine/UserInterfaceSettings.h"
#include "UnrealEngine.h"
#include "Engine/GameEngine.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Images/SThrobber.h"
#include "Widgets/Layout/SSpacer.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SSafeZone.h"
#include "Widgets/Layout/SDPIScaler.h"
#include "Engine/UserInterfaceSettings.h"
#include "Slate/DeferredCleanupSlateBrush.h"

#define LOCTEXT_NAMESPACE "SLoadingLayout"

void SLoadingLayout::Construct(const FArguments& InArgs)
{
	const ULoadingScreenSettings* LoadingScreenSettings = GetDefault<ULoadingScreenSettings>();
	const FSlateFontInfo& TipFontInfo = LoadingScreenSettings->TipFontInfo;
	const FSlateFontInfo& LoadingFontInfo = LoadingScreenSettings->LoadingFontInfo;
	const FLoadingScreenSettingsStruct& LoadingScreenSettingsStruct = LoadingScreenSettings->LoadingScreenSetting;

	TSharedRef<SOverlay> Root = SNew(SOverlay);

	// If there's an image defined;
	if (LoadingScreenSettingsStruct.Images.Num() > 0)
	{
		const int32 ImageIndex = FMath::RandRange(0, LoadingScreenSettingsStruct.Images.Num() - 1);
		const FStringAssetReference& ImageAsset = LoadingScreenSettingsStruct.Images[ImageIndex];
		UObject* ImageObject = ImageAsset.TryLoad();
		if (UTexture2D* LoadingImage = Cast<UTexture2D>(ImageObject))
		{
			LoadingScreenBrush = FDeferredCleanupSlateBrush::CreateBrush(LoadingImage);

			Root->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SBorder)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.BorderBackgroundColor(LoadingScreenSettingsStruct.BackgroundColor)
				.BorderImage(FCoreStyle::Get().GetBrush("WhiteBrush"))
				[
					SNew(SScaleBox)
					.Stretch(LoadingScreenSettingsStruct.ImageStretch)
					[
						SNew(SImage)
						.Image(LoadingScreenBrush.IsValid() ? LoadingScreenBrush->GetSlateBrush() : nullptr)
					]
				]
			];
		}
	}

	TSharedRef<SWidget> TipWidget = SNullWidget::NullWidget;
	if (LoadingScreenSettings->Tips.Num() > 0)
	{
		const int32 TipIndex = FMath::RandRange(0, LoadingScreenSettings->Tips.Num() - 1);

		TipWidget = SNew(STextBlock)
		.WrapTextAt(LoadingScreenSettings->TipWrapAt)
		.Font(TipFontInfo)
		.Text(LoadingScreenSettings->Tips[TipIndex]);
	}
	else
	{
		// Need to use a spacer when rendered on another thread, incrementing the SNullWidget will
		// Lead to Shared ptr crashes.
		TipWidget = SNew(SSpacer);
	}

	Root->AddSlot()
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Bottom)
	[
		SNew(SBorder)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Bottom)
		.BorderBackgroundColor(LoadingScreenSettingsStruct.TipBackgroundColor)
		.BorderImage(FCoreStyle::Get().GetBrush("WhiteBrush"))
		[
			SNew(SSafeZone)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Bottom)
			.IsTitleSafe(true)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.Padding(FMargin(25.0f, 0.0f, 0.0f, 0.0f))
				.VAlign(VAlign_Center)
				.AutoWidth()
				[
					SNew(SCircularThrobber)
					.Radius(PointSizeToSlateUnits(LoadingFontInfo.Size) / 2.0f)
				]

				+ SHorizontalBox::Slot()
				.Padding(FMargin(40.0f, 0.0f, 0, 0))
				.AutoWidth()
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.Text(LoadingScreenSettingsStruct.LoadingText)
				.Font(LoadingFontInfo)
				]

				+ SHorizontalBox::Slot()
				.FillWidth(1)
				.HAlign(HAlign_Fill)
				[
					SNew(SSpacer)
					.Size(FVector2D(1.0f, 1.0f))
				]

				+ SHorizontalBox::Slot()
				.AutoWidth()
				.HAlign(HAlign_Right)
				.VAlign(VAlign_Center)
				.Padding(FMargin(10.0f))
				[
					TipWidget
				]
			]
		]
	];

	ChildSlot
	[
		Root
	];
}

void SLoadingLayout::AddReferencedObjects(FReferenceCollector& Collector)
{
}

FString SLoadingLayout::GetReferencerName() const
{
	return TEXT("SLoadingLayout");
}

float SLoadingLayout::PointSizeToSlateUnits(float InPointSize)
{
	const float SlateFreeTypeHorizontalResolutionDPI = 96.0f;
	const float FreeTypeNativeDPI = 72.0f;
	const float PixelSize = InPointSize * (SlateFreeTypeHorizontalResolutionDPI / FreeTypeNativeDPI);
	return PixelSize;
}

float SLoadingLayout::GetDPIScale() const
{
	const FVector2D DrawSize = GetTickSpaceGeometry().ToPaintGeometry().GetLocalSize();
	const FIntPoint Size((int32)DrawSize.X, (int32)DrawSize.Y);
	return GetDefault<UUserInterfaceSettings>()->GetDPIScaleBasedOnSize(Size);
}

#undef LOCTEXT_NAMESPACE