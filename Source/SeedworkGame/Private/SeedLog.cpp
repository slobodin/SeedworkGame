// Copyright (c) Mistfly Games. All Rights Reserved.

#include "SeedLog.h"
#include "Engine/Engine.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Logging/MessageLog.h"

DEFINE_LOG_CATEGORY(TheGame)

#if !NO_LOGGING

void DoTraceGameLog(const FLogCategoryBase* category, const FString& text)
{
    const FString categoryName = category->GetCategoryName().ToString();

    const FString finalString = FString::Printf(TEXT("    [%s]: %s"), *categoryName, *text);

    UE_LOG(TheGame, Display, TEXT("%s"), *finalString);
}

void DoTraceWarning(const FString& text)
{
    const FString warnText = FString::Printf(TEXT("[warning]: %s"), *text);

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Magenta, warnText);
    }

    UE_LOG(TheGame, Warning, TEXT("%s"), *warnText);
}

void DoTraceError(const FString& text)
{
    //UKismetSystemLibrary::RaiseScriptError(text);
    const FString errText = FString::Printf(TEXT("[error]: %s"), *text);

#if !UE_BUILD_SHIPPING
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 12.0f, FColor::Red, errText);
    }

    FMessageLog("PIE").Warning(FText::FromString(text));
#endif

    UE_LOG(TheGame, Error, TEXT("%s"), *errText);
}

#endif
