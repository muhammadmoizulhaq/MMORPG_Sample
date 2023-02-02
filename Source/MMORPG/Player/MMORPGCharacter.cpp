// Fill out your copyright notice in the Description page of Project Settings.

#include "MMORPGCharacter.h"
#include "MMORPGPlayerController.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
AMMORPGCharacter::AMMORPGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMMORPGCharacter::BeginPlay()
{
	Super::BeginPlay();
	// Setting up a mapping context for EnhancedInput
	/*if (APlayerController* MyPlayercontroller = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* MySubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(MyPlayercontroller->GetLocalPlayer()))
		{
			MySubsystem->AddMappingContext(IMC_MyCharacter, 0);
		}
	}*/
	if (APlayerController* MyPlayercontroller = Cast<APlayerController>(GetController()))
	{
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(MyPlayercontroller->GetLocalPlayer())->AddMappingContext(IMC_MyCharacter, 0);
	}
}

void AMMORPGCharacter::Move(const FInputActionValue& Value)
{
	//if (ActionState != EActionState::EAS_Unoccupied)return;
	/*const FVector2D MyDirectionValue = Value.Get<FVector2D>();
	if (GetController() && (MyDirectionValue != FVector2D(0.0f, 0.0f)))
	{
		const FRotator MyRotation = GetController()->GetControlRotation();
		const FRotator MyYawRotation(0.0f, MyRotation.Yaw, 0.0f);

		const FVector MyForwardDirection = FRotationMatrix(MyYawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(MyForwardDirection, MyDirectionValue.Y);
		const FVector MyRightDirection = FRotationMatrix(MyYawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(MyRightDirection, MyDirectionValue.X);
	}*/
	const FVector2D MyDirectionValue = Value.Get<FVector2D>();
	if (MyDirectionValue != FVector2D(0.0f, 0.0f))
	{
		if (AController* MyController = GetController())
		{
			const FRotator MyRotation = MyController->GetControlRotation();
			const FVector MyForwardDirection = MyRotation.RotateVector(FVector::ForwardVector);
			AddMovementInput(MyForwardDirection, MyDirectionValue.Y);
			const FVector MyRightDirection = MyRotation.RotateVector(FVector::RightVector);
			AddMovementInput(MyRightDirection, MyDirectionValue.X);
		}
	}
}

void AMMORPGCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D MyLookValue = Value.Get<FVector2D>();
	if (GetController() && (MyLookValue != FVector2D(0.0f, 0.0f)))
	{
		AddControllerYawInput(MyLookValue.X);
		AddControllerPitchInput(MyLookValue.Y);
	}
}

// Called every frame
void AMMORPGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Calculate FPS
	UE_LOG(LogTemp, Warning, TEXT("FPS: %f"), (1.0f / DeltaTime));
}

// Called to bind functionality to input
void AMMORPGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// EnhancedInput Component
	if (UEnhancedInputComponent* MyEnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		MyEnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMMORPGCharacter::Move);
		MyEnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AMMORPGCharacter::Look);
	}
}