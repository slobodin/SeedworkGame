// Copyright (c) Mistfly Games. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Templates/SubclassOf.h"
#include "ActorUtilityLibrary.generated.h"

class AActor;
class UObject;
class UInterface;

UCLASS()
class SEEDWORKGAME_API UActorUtilityLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /** Find and returns actor that MUST be unique (e.g. only 1 instance of this actor class exists in the current world. */
    UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "ActorClass"))
    static AActor* FindUniqueActor(const UObject* worldContextObject, TSubclassOf<AActor> actorClass);

    UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "ActorClass"))
    static AActor* FindUniqueActorWithTag(const UObject* worldContextObject, TSubclassOf<AActor> actorClass, FName tag);

    UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
    static AActor* FindUniqueActorWithInterface(const UObject* worldContextObject, TSubclassOf<UInterface> interface);

    UFUNCTION(BlueprintCallable)
    static void DestroyActorOnNextTick(AActor* theActor);

    UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
    static void DestroyAllActorsOfClass(const UObject* worldContextObject, TSubclassOf<AActor> actorClass);
};
