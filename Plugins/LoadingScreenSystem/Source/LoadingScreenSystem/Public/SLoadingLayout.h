// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/SCompoundWidget.h"
#include "UObject/GCObject.h"

#include "Animation/CurveHandle.h"
#include "Animation/CurveSequence.h"
#include "Slate/DeferredCleanupSlateBrush.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "LoadingScreenSettings.h"

class UFont;
class UMaterialInstance;
class UTexture;
class FDeferredCleanupSlateBrush;

class LOADINGSCREENSYSTEM_API SLoadingLayout : public SCompoundWidget, public FGCObject
{
public:
	SLATE_BEGIN_ARGS(SLoadingLayout) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	//~ Begin FGCObject interface
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual FString GetReferencerName() const override;
	//~ End FGCObject interface
	static float PointSizeToSlateUnits(float InPointSize);
private:
	float GetDPIScale() const;
private:
	TSharedPtr<FDeferredCleanupSlateBrush> LoadingScreenBrush;
};