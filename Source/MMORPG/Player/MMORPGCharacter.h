// Fill out your copyright notice in the Description page of Project Settings.
/**
* The class APawn is the 'Actor' that the Player actually controls.
* Most of the time it's a human character, but it could also be a cat, plane, ship, block, etc.
* The Player can only possess one Pawn at a time, but can easily switch between Pawns by unpossessing and re-possessing them.
* The Pawn is mostly replicated to all Clients.
* The Pawn's child class ACharacter is often used, because it comes with an already networked MovementComponent, which handles replicating the Position, Rotation, etc. of a Players Character.
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Utils/MMORPGEnums.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemInterface.h"
#include "MMORPGCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDiedDelegate, AMMORPGCharacter*, Character);

class UInputMappingContext;
class UInputAction;
class UMMORPGAbilitySystemComponent;
class UMMORPGBaseAttributeSet;
class UGameplayEffect;
class UBaseGameplayAbility;

UCLASS()
class MMORPG_API AMMORPGCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AMMORPGCharacter(const class FObjectInitializer& ObjectInitializer);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UPROPERTY(BlueprintAssignable, Category = "MMORPG|Character")
	FCharacterDiedDelegate CharacterDiedDelegate;
	UFUNCTION(BlueprintCallable, Category = "MMORPG|Character")
	virtual bool IsAlive() const;
	UFUNCTION(BlueprintCallable, Category = "MMORPG|Character")
	virtual int32 GetAbilityLevel(EMMORPGAbilityID AbilityID) const;
	virtual void RemoveCharacterAbilities();
	virtual void Die();
	UFUNCTION(BlueprintCallable, Category = "MMORPG|Character")
	virtual void FinishDying();
	UFUNCTION(BlueprintCallable, Category = "MMORPG|Character|Attributes")
	float GetHealth() const;
	UFUNCTION(BlueprintCallable, Category = "MMORPG|Character|Attributes")
	float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable, Category = "MMORPG|Character|Attributes")
	float GetMana() const;
	UFUNCTION(BlueprintCallable, Category = "MMORPG|Character|Attributes")
	float GetMaxMana() const;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* IMC_MyCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_Move;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_Look;
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void Look(const FInputActionValue& Value);
	TWeakObjectPtr<UMMORPGAbilitySystemComponent> MMORPGAbilitySystemComponent;
	TWeakObjectPtr<UMMORPGBaseAttributeSet> MMORPGBaseAttributeSet;
	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MMORPG|Character")
	FText CharacterName;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MMORPG|Character")
	UAnimMontage* DeathMontage;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MMORPG|Character")
	TSubclassOf<UGameplayEffect> DefaultAttributes;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MMORPG|Character")
	TArray<TSubclassOf<UGameplayEffect>> StartupEffects;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MMORPG|Character")
	TArray<TSubclassOf<UBaseGameplayAbility>> BaseGameplayAbility;
	virtual void AddCharacterAttributies();
	virtual void InitializeAttributes();
	virtual void AddStartupEffects();
	virtual void SetHealth(float InHealth);
	virtual void SetMana(float InMana);
};