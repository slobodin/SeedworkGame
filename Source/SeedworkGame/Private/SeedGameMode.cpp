// Copyright (c) Mistfly Games. All Rights Reserved.

#include "SeedGameMode.h"

bool ASeedGameMode::AllowCheats(APlayerController* pc)
{
    // Always block CheatManager spawning in shipping builds.
#if UE_BUILD_SHIPPING
    return false;
#else
    return true;
#endif
}

void ASeedGameMode::GenericPlayerInitialization(AController* newPlayer)
{
    Super::GenericPlayerInitialization(newPlayer);

    OnGameModePlayerInitialized.Broadcast(this, newPlayer);
}
