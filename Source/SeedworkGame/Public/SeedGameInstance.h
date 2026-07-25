// Copyright (c) Mistfly Games. All Rights Reserved.

#pragma once

#include "Containers/Ticker.h"
#include "Kismet/BlueprintPlatformLibrary.h"
#include "SeedGameInstance.generated.h"

UCLASS(Abstract)
class SEEDWORKGAME_API USeedGameInstance : public UPlatformGameInstance
{
    GENERATED_BODY()

public:
    virtual void Init() override;
    virtual void Shutdown() override;

    // Returns a timer manager that does not get paused when game is on pause.
    FTimerManager& GetTimerManagerEx() const { return *TimerManagerEx; }

    static USeedGameInstance* Get(const UObject* worldContextObject);

private:
    // Timer manager that does not get paused when game is paused
    TSharedPtr<FTimerManager> TimerManagerEx;

    FTSTicker::FDelegateHandle CoreTickerHandle;
};
