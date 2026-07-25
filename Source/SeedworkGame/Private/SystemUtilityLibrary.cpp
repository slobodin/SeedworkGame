// Copyright (c) Mistfly Games. All Rights Reserved.

#include "SystemUtilityLibrary.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Misc/App.h"

bool USystemUtilityLibrary::IsWithEditor()
{
#if WITH_EDITOR
    return true;
#else
    return false;
#endif
}

bool USystemUtilityLibrary::IsShippingBuild()
{
#if UE_BUILD_SHIPPING
    return true;
#else
    return false;
#endif
}

bool USystemUtilityLibrary::IsGameWorld(const UObject* worldContextObject)
{
    if (auto world = GEngine->GetWorldFromContextObject(worldContextObject, EGetWorldErrorMode::ReturnNull))
    {
        return world->IsGameWorld();
    }

    return false;
}

FString USystemUtilityLibrary::GetGameVersionString()
{
    FString rhi = FApp::GetGraphicsRHI();

#if PLATFORM_IOS
    FString projVer = FPlatformMisc::GetProjectVersion();
    FString buildNo = FPlatformMisc::GetBuildNumber();

    return FString::Printf(TEXT("ver. %s (%s) %s"), *projVer, *buildNo, *rhi);
#elif PLATFORM_ANDROID
    FString projVer = FPlatformMisc::GetProjectVersion();

    return FString::Printf(TEXT("ver. %s %s"), *projVer, *rhi);
#elif PLATFORM_WINDOWS || PLATFORM_MAC
    return FString::Printf(TEXT("Desktop %s"), *rhi);
#else
#error "implement"
#endif
}
