// Fill out your copyright notice in the Description page of Project Settings.


#include "SLoadingLayout.h"
#include "Engine/UserInterfaceSettings.h"
#include "UnrealEngine.h"
#include "Engine/GameEngine.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Images/SThrobber.h"
#include "Widgets/Layout/SSpacer.h"
#include "Widgets/Images/SImage.h"

#define LOCTEXT_NAMESPACE "SLoadingLayout"

void SLoadingLayout::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SOverlay)
		.Clipping(EWidgetClipping::ClipToBoundsAlways)
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(0)
		[
			SNew(SImage)
			.ColorAndOpacity(FColor::Black)
			.Visibility(EVisibility::SelfHitTestInvisible)
		]
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Bottom)
		.Padding(FMargin(0.0f, 0.0f, 0.0f, 50.0f))
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Fill)
			[
				SNew(STextBlock)
				.Text(FText::FromString("Loading"))
				.Visibility(EVisibility::SelfHitTestInvisible)
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SThrobber)
				.NumPieces(5)
				.Animate(SThrobber::EAnimation::Vertical)
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SSpacer)
				.Size(FVector2D(40.0f, 0.0f))
			]
		]
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