// Copyright (c) Mistfly Games. All Rights Reserved.

#include "WorldContextObject.h"
#include "Engine/World.h"

UWorld* UWorldContextObject::GetWorld() const
{
    if (HasAnyFlags(RF_ArchetypeObject | RF_ClassDefaultObject))
    {
        return nullptr;
    }

    if (auto outer = GetOuter(); IsValid(outer))
    {
        if (UWorld* w = outer->GetWorld(); IsValid(w))
        {
            return w;
        }
    }

    return nullptr;
}
