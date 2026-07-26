// Copyright (c) Mistfly Games. All Rights Reserved.

#include "ActorUtilityLibrary.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

AActor* UActorUtilityLibrary::FindUniqueActor(const UObject* worldContextObject, TSubclassOf<AActor> actorClass)
{
    if (!actorClass)
    {
        return nullptr;
    }

    if (auto world = GEngine->GetWorldFromContextObject(worldContextObject, EGetWorldErrorMode::LogAndReturnNull))
    {
        if (!world->IsGameWorld())
        {
            return nullptr;
        }

        AActor* foundActor = nullptr;
        int32 count = 0;

        for (TActorIterator<AActor> it(world, actorClass); it; ++it)
        {
            if (count == 0)
            {
                foundActor = *it;
            }
            count++;

            // Early out if we found more than one
            if (count > 1)
            {
                break;
            }
        }

        if (ensureMsgf(count == 1, TEXT("FindUniqueActor: passed actor class is not unique or actor does not exists!")))
        {
            return foundActor;
        }
    }

    return nullptr;
}

AActor* UActorUtilityLibrary::FindUniqueActorWithTag(const UObject* worldContextObject, TSubclassOf<AActor> actorClass, FName tag)
{
    unimplemented();
    return nullptr;
}

AActor* UActorUtilityLibrary::FindUniqueActorWithInterface(const UObject* worldContextObject, TSubclassOf<UInterface> interface)
{
    unimplemented();
    return nullptr;
}

void UActorUtilityLibrary::DestroyActorOnNextTick(AActor* theActor)
{
    if (ensure(IsValid(theActor)))
    {
        TWeakObjectPtr<AActor> weakActor = theActor;

        theActor->GetWorld()->GetTimerManager().SetTimerForNextTick([weakActor]()
        {
            if (weakActor.IsValid())
            {
                weakActor->Destroy();
            }
        });
    }
}

void UActorUtilityLibrary::DestroyAllActorsOfClass(const UObject* worldContextObject, TSubclassOf<AActor> actorClass)
{
    if (auto world = GEngine->GetWorldFromContextObject(worldContextObject, EGetWorldErrorMode::LogAndReturnNull))
    {
        if (!world->IsGameWorld())
        {
            return;
        }

        TArray<AActor*> actorsToDestroy;
        UGameplayStatics::GetAllActorsOfClass(worldContextObject, actorClass, actorsToDestroy);

        for (AActor* actor : actorsToDestroy)
        {
            actor->Destroy();
        }
    }
}
