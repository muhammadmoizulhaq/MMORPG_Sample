// Fill out your copyright notice in the Description page of Project Settings.
/**
* The class AGameMode is used to define the RULES of your game. This includes the used classes, like Apawn, PlayerController, APlayerState and more.
* It is only available on the Server. Clients don't have an object of the GameMode and will only get a nullptr when trying to retrieve it.
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MMORPGGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MMORPG_API AMMORPGGameMode : public AGameMode
{
	GENERATED_BODY()
};