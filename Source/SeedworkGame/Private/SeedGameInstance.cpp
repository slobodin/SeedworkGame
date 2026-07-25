// Copyright (c) Mistfly Games. All Rights Reserved.

#include "SeedGameInstance.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/StreamableManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetInternationalizationLibrary.h"
#include "SeedGameUserSettings.h"
#include "TimerManager.h"

namespace
{
#if !UE_BUILD_SHIPPING
    ANSICHAR StackTraceData[1 << 17] = { 0 };

    bool EnsureHandler(const TWeakObjectPtr<UObject> worldCtx, const FEnsureHandlerArgs& args)
    {
        if (worldCtx.IsValid())
        {
            const SIZE_T size = UE_ARRAY_COUNT(StackTraceData);

            memset(StackTraceData, 0, sizeof(StackTraceData));

            FPlatformStackWalk::StackWalkAndDumpEx(StackTraceData, size, PLATFORM_RETURN_ADDRESS(),
                FGenericPlatformStackWalk::EStackWalkFlags::FlagsUsedWhenHandlingEnsure);

            UKismetSystemLibrary::PrintString(worldCtx.Get(), "*** ENSURE FAILED: " + FString(args.Expression) + " " + FString(args.Message) + " *** \n Stack: \n" + FString::ConstructFromPtrSize(StackTraceData, size) + "\n", true, true, FColor::Red, 10.0f);
        }

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

    TimerManagerEx = MakeShareable(new FTimerManager());

    Super::Init();

    CoreTickerHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateWeakLambda(this, [this](float deltaSeconds)
    {
        TimerManagerEx->Tick(deltaSeconds);

        return true;
    }));

#if !UE_BUILD_SHIPPING
    TWeakObjectPtr<USeedGameInstance> weakThis = this;

    SetEnsureHandler([weakThis](const FEnsureHandlerArgs& args) { return EnsureHandler(weakThis.Get(), args); });
#endif
}

void USeedGameInstance::Shutdown()
{
    FTSTicker::GetCoreTicker().RemoveTicker(CoreTickerHandle);

    Super::Shutdown();
}

USeedGameInstance* USeedGameInstance::Get(const UObject* worldContextObject)
{
    return CastChecked<USeedGameInstance>(UGameplayStatics::GetGameInstance(worldContextObject));
}
