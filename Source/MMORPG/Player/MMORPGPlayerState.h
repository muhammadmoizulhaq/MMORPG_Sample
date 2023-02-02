// Fill out your copyright notice in the Description page of Project Settings.
/**
* The class APlayerState is the most important class for a specific Player. 
* It is meant to hold current information about the Player. Each Player has their own PlayerState.
* The PlayerState is also replicated to everyone and can be used to retrieve and display data on other Clients.
* An easy way to access all PlayerStates, that are currently in the Game, is the PlayerArray inside of the GameState Class.
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MMORPGPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MMORPG_API AMMORPGPlayerState : public APlayerState
{
	GENERATED_BODY()
};