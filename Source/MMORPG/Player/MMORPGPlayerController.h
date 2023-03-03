// Fill out your copyright notice in the Description page of Project Settings.
/**
* The class APlayerController might be the most interesting and complicated Class that we come across.
* It's also the center for a lot of Client stuff, since this is the first Class that the Client actually 'owns'.
* The PlayerController can be seen as the 'Input' of the Player. It is the link of the Player with the Server. This means, every Client has one PlayerController.
* A Client's PlayerController only exists on himself AND the Server, but other Clients don't know about other PlayerController. Every Client only knows about his own!
* The result of that is, that the Server has a reference of all Client PlayerControllers!
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MMORPGPlayerController.generated.h"

class AMMORPGHUD;

UCLASS()
class MMORPG_API AMMORPGPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	AMMORPGPlayerController();
private:
	TSoftClassPtr<AMMORPGHUD> MyHUDClassPtr;
};