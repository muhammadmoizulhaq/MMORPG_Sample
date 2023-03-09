// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/Items/BaseItem.h"

FString UBaseItem::GetIdentifierString() const
{
	return GetPrimaryAssetId().ToString();
}

FPrimaryAssetId UBaseItem::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(ItemType, GetFName()/*FName(*GetFName().ToString().Append("_C"))*/);
}