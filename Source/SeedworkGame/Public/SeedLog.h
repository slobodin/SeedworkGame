// Copyright (c) Mistfly Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(TheGame, Log, All);

#if NO_LOGGING

#define GAME_LOG(Cat, Format, ...) ((void) 0)
#define GAME_WARNING(Format, ...) ((void) 0)
#define GAME_ERROR(Format, ...) ((void) 0)

#else

void SEEDWORKGAME_API DoTraceGameLog(const FLogCategoryBase* category, const FString& text);
void SEEDWORKGAME_API DoTraceWarning(const FString& text);
void SEEDWORKGAME_API DoTraceError(const FString& text);

#define GAME_LOG(Cat, Format, ...) DoTraceGameLog(&Cat, FString::Printf(TEXT(Format), ##__VA_ARGS__))
#define GAME_WARNING(Format, ...) DoTraceWarning(FString::Printf(TEXT(Format), ##__VA_ARGS__))
#define GAME_ERROR(Format, ...) DoTraceError(FString::Printf(TEXT(Format), ##__VA_ARGS__))

#endif
