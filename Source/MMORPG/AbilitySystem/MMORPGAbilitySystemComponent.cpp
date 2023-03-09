// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/MMORPGAbilitySystemComponent.h"

UMMORPGAbilitySystemComponent::UMMORPGAbilitySystemComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	FMemory::Memset(ActivationGroupCount, 0, sizeof(ActivationGroupCount));
}