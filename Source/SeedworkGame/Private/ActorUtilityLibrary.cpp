// Copyright (c) Mistfly Games. All Rights Reserved.

#include "ActorUtilityLibrary.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

AActor* UActorUtilityLibrary::FindUniqueActor(const UObject* worldContextObject, TSubclassOf<AActor> ActorClass)
{
    if (!ActorClass)
    {
        return nullptr;
    }

    if (auto world = GEngine->GetWorldFromContextObject(worldContextObject, EGetWorldErrorMode::LogAndReturnNull))
    {
        if (!world->IsGameWorld())
        {
            return nullptr;
        }

        TArray<AActor*> outActors;
        UGameplayStatics::GetAllActorsOfClass(world, ActorClass, outActors);

        if (ensureAlwaysMsgf(outActors.Num() == 1, TEXT("FindUniqueActor: passed actor class is not unique or actor does not exists!")))
        {
            if (!outActors[0]->IsPendingKillPending())
            {
                return outActors[0];
            }
        }
    }

    return nullptr;
}

AActor* UActorUtilityLibrary::FindUniqueActorWithTag(const UObject* worldContextObject, TSubclassOf<AActor> ActorClass, FName tag)
{
    unimplemented();
    return nullptr;
}

AActor* UActorUtilityLibrary::FindUniqueActorWithInterface(const UObject* worldContextObject, TSubclassOf<UInterface> Interface)
{
    unimplemented();
    return nullptr;
}

void UActorUtilityLibrary::DestroyActorOnNextTick(const UObject* worldContextObject, AActor* theActor)
{
    if (auto world = GEngine->GetWorldFromContextObject(worldContextObject, EGetWorldErrorMode::LogAndReturnNull))
    {
        TWeakObjectPtr<AActor> weakActor = theActor;

        world->GetTimerManager().SetTimerForNextTick([weakActor]() {
            if (weakActor.IsValid())
            {
                weakActor->Destroy();
            }
        });
    }
}

void UActorUtilityLibrary::DestroyAllActorsOfClass(const UObject* worldContextObject, TSubclassOf<AActor> actorClass)
{
    if (actorClass)
    {
        if (auto world = GEngine->GetWorldFromContextObject(worldContextObject, EGetWorldErrorMode::LogAndReturnNull))
        {
            if (world->IsGameWorld())
            {
                for (TActorIterator<AActor> it(world, actorClass); it; ++it)
                {
                    if (IsValid(*it))
                    {
                        (*it)->Destroy();
                    }
                }
            }
        }
    }
}
