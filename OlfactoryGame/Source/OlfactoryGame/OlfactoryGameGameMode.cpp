// Copyright Epic Games, Inc. All Rights Reserved.

#include "OlfactoryGameGameMode.h"
#include "FPCharacter.h"

AOlfactoryGameGameMode::AOlfactoryGameGameMode()
	: Super()
{
	DefaultPawnClass = AFPCharacter::StaticClass();

}
