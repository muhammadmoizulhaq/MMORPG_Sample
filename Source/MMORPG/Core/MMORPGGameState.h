// Fill out your copyright notice in the Description page of Project Settings.
/**
* The class AGameState is probably the most important class for shared information between Server and Clients.
* The GameState is used to keep track of the current State of the Game. This includes, for Multiplayer important, a List of connected Players (APlayerState).
* The GameState is replicated to all Clients. So everyone can access it. This makes the GameState to one of the most centered classes for Multiplayer Games.
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MMORPGGameState.generated.h"

/**
 * 
 */
UCLASS()
class MMORPG_API AMMORPGGameState : public AGameState
{
	GENERATED_BODY()
};