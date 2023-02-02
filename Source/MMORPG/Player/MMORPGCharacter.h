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
#include "MMORPGCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class MMORPG_API AMMORPGCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AMMORPGCharacter();
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
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};