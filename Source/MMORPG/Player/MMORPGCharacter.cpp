// Fill out your copyright notice in the Description page of Project Settings.

#include "MMORPGCharacter.h"
#include "MMORPGPlayerController.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystem/MMORPGAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/BaseGameplayAbility.h"
#include "AbilitySystem/AttributeSet/MMORPGBaseAttributeSet.h"
#include "EnhancedInputComponent.h"

// Sets default values
AMMORPGCharacter::AMMORPGCharacter(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Overlap);
	bAlwaysRelevant = true;

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
	EffectRemoveOnDeathTag = FGameplayTag::RequestGameplayTag(FName("State.RemoveOnDeath"));
}

// Called when the game starts or when spawned
void AMMORPGCharacter::BeginPlay()
{
	Super::BeginPlay();
	// Setting up a mapping context for EnhancedInput
	
	if (APlayerController* MyPlayercontroller = Cast<APlayerController>(GetController()))
	{
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(MyPlayercontroller->GetLocalPlayer())->AddMappingContext(IMC_MyCharacter, 0);
	}
}

void AMMORPGCharacter::Move(const FInputActionValue& Value)
{
	//if (ActionState != EActionState::EAS_Unoccupied)return;
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

void AMMORPGCharacter::AddCharacterAttributies()
{
}

void AMMORPGCharacter::InitializeAttributes()
{
}

void AMMORPGCharacter::AddStartupEffects()
{
}

void AMMORPGCharacter::SetHealth(float InHealth)
{
}

void AMMORPGCharacter::SetMana(float InMana)
{
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

UAbilitySystemComponent* AMMORPGCharacter::GetAbilitySystemComponent() const
{
	return MMORPGAbilitySystemComponent.Get();
}

bool AMMORPGCharacter::IsAlive() const
{
	return GetHealth() > 0.0f;
}

int32 AMMORPGCharacter::GetAbilityLevel(EMMORPGAbilityID AbilityID) const
{
	return int32();
}

void AMMORPGCharacter::RemoveCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !MMORPGAbilitySystemComponent.IsValid() || !MMORPGAbilitySystemComponent->bIsCharacterAbilitiesGiven)
	{
		return;
	}
	TArray<FGameplayAbilitySpecHandle> GameplayAbilitySpecHandleToRemove;
	for (const FGameplayAbilitySpec& Spec : MMORPGAbilitySystemComponent->GetActivatableAbilities())
	{
		if ((Spec.SourceObject == this) && (BaseGameplayAbility.Contains(Spec.Ability->GetClass())))
		{
			GameplayAbilitySpecHandleToRemove.Add(Spec.Handle);
		}
	}
	for (int32 i = 0; i < GameplayAbilitySpecHandleToRemove.Num(); i++)
	{
		MMORPGAbilitySystemComponent->ClearAbility(GameplayAbilitySpecHandleToRemove[i]);
	}
	MMORPGAbilitySystemComponent->bIsCharacterAbilitiesGiven = false;
}

void AMMORPGCharacter::Die()
{
	RemoveCharacterAbilities();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	/*GetCharacterMovement()->GravityScale = 0;
	GetCharacterMovement()->Velocity = FVector(0);*/

	CharacterDiedDelegate.Broadcast(this);
	
	if (MMORPGAbilitySystemComponent.IsValid())
	{
		MMORPGAbilitySystemComponent->CancelAbilities();
		FGameplayTagContainer MyGameplayTagContainer;
		MyGameplayTagContainer.AddTag(EffectRemoveOnDeathTag);
		int32 NumEffectRemoved = MMORPGAbilitySystemComponent->RemoveActiveEffectsWithTags(MyGameplayTagContainer);
		MMORPGAbilitySystemComponent->AddLooseGameplayTag(DeadTag);
	}
	if (DeathMontage)
	{
		PlayAnimMontage(DeathMontage);
	}
	else
	{
		FinishDying();
	}
}

void AMMORPGCharacter::FinishDying()
{
	Destroy();
}

float AMMORPGCharacter::GetHealth() const
{
	if (MMORPGBaseAttributeSet.IsValid()) 
		return MMORPGBaseAttributeSet->GetHealth();

	return 0.0f;
}

float AMMORPGCharacter::GetMaxHealth() const
{
	if (MMORPGBaseAttributeSet.IsValid())
		return MMORPGBaseAttributeSet->GetMaxHealth();

	return 0.0f;
}

float AMMORPGCharacter::GetMana() const
{
	if (MMORPGBaseAttributeSet.IsValid())
		return MMORPGBaseAttributeSet->GetMana();

	return 0.0f;
}

float AMMORPGCharacter::GetMaxMana() const
{
	if (MMORPGBaseAttributeSet.IsValid())
		return MMORPGBaseAttributeSet->GetMaxMana();

	return 0.0f;
}
