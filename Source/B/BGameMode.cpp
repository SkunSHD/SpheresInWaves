// Copyright Epic Games, Inc. All Rights Reserved.

#include "BGameMode.h"
#include "BHUD.h"
#include "BCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABGameMode::ABGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ABHUD::StaticClass();
}
