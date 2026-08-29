// Copyright (c) Mistfly Games. All Rights Reserved.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "SeedGameMode.generated.h"

/**
 */
UCLASS(Abstract)
class SEEDWORKGAME_API ASeedGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    /**
     * Post login event, triggered when a player or bot joins the game. This is called after the player has finished initialization.
     */
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameModePlayerInitialized, AGameModeBase*, GameMode, AController*, NewPlayer);

    UPROPERTY(BlueprintAssignable)
    FOnGameModePlayerInitialized OnGameModePlayerInitialized;

protected:
    virtual bool AllowCheats(APlayerController* pc) override;

    virtual void GenericPlayerInitialization(AController* newPlayer) override;

    UFUNCTION(BlueprintImplementableEvent)
    void ReceiveGenericPlayerInitialization(AController* newPlayer);
};
