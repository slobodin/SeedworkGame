// Copyright (c) Mistfly Games. All Rights Reserved.

#include "SeedGameInstance.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/StreamableManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetInternationalizationLibrary.h"
#include "TimerManager.h"

namespace
{
#if !UE_BUILD_SHIPPING
    ANSICHAR StackTraceData[1 << 17] = { 0 };

    bool EnsureHandler(const UObject* worldCtx, const FEnsureHandlerArgs& args)
    {
        static bool bInHandler = false;

        if (bInHandler)
        {
            return false;
        }

        bInHandler = true;

        const SIZE_T size = UE_ARRAY_COUNT(StackTraceData);

        FMemory::Memzero(StackTraceData, size);

        FPlatformStackWalk::StackWalkAndDumpEx(StackTraceData, size, PLATFORM_RETURN_ADDRESS(),
            FGenericPlatformStackWalk::EStackWalkFlags::FlagsUsedWhenHandlingEnsure);

        UKismetSystemLibrary::PrintString(worldCtx,
            "*** ENSURE FAILED: " + FString(args.Expression) + " " + FString(args.Message) +
            " *** \n Stack: \n" + FString(StackTraceData) + "\n", true, true, FColor::Red, 10.0f);

        bInHandler = false;
        return false;
    }
#endif
}

void USeedGameInstance::Init()
{
#if WITH_EDITOR
    // The asset registry is populated asynchronously at startup, so there's no guarantee it has finished.
    // This simple approach just runs a synchronous scan on the entire content directory.
    // Need this only for the editor builds (I'm sure on 95%), because in non-editor executable,
    // asset registry loads the data from serialized AssetRegistry.bin, created upon cooking.
    // More info in `ShouldSearchAllAssetsAtStart` inside AssetRegistry.cpp
    FAssetRegistryModule::GetRegistry().SearchAllAssets(true);
#endif

    TimerManagerEx = MakeShared<FTimerManager>(this);

    Super::Init();

    CoreTickerHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateWeakLambda(this, [this](float deltaSeconds)
    {
        TimerManagerEx->Tick(deltaSeconds);

        return true;
    }));

#if !UE_BUILD_SHIPPING
    TWeakObjectPtr<USeedGameInstance> weakThis = this;
    PreviousEnsureHandler = SetEnsureHandler([weakThis](const FEnsureHandlerArgs& args) { return EnsureHandler(weakThis.Get(), args); });
#endif

    FSlateApplication::Get().ToggleGlobalInvalidation(true);
}

void USeedGameInstance::Shutdown()
{
    FTSTicker::GetCoreTicker().RemoveTicker(CoreTickerHandle);
    TimerManagerEx.Reset();

#if !UE_BUILD_SHIPPING
    SetEnsureHandler(PreviousEnsureHandler);
#endif

    Super::Shutdown();
}

USeedGameInstance* USeedGameInstance::Get(const UObject* worldContextObject)
{
    return CastChecked<USeedGameInstance>(UGameplayStatics::GetGameInstance(worldContextObject));
}
