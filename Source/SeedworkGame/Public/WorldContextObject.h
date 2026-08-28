// Copyright (c) Mistfly Games. All Rights Reserved.

#pragma once

#include "UObject/Object.h"
#include "WorldContextObject.generated.h"

UCLASS(Blueprintable)
class SEEDWORKGAME_API UWorldContextObject : public UObject
{
    GENERATED_BODY()

public:
    virtual UWorld* GetWorld() const override;
};
