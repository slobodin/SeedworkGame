// Copyright (c) Mistfly Games. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "SystemUtilityLibrary.generated.h"

UCLASS()
class SEEDWORKGAME_API USystemUtilityLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure)
    static bool IsWithEditor();

    UFUNCTION(BlueprintPure)
    static bool IsShippingBuild();

    UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
    static bool IsGameWorld(const UObject* worldContextObject);

    UFUNCTION(BlueprintPure)
    static FString GetGameVersionString();
};
