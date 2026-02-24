#pragma once

#include "CoreMinimal.h"

#if WITH_GAMEPLAY_DEBUGGER
#include "GameplayDebuggerCategory.h"

class FGameplayDebuggerCategory_ObjectPool : public FGameplayDebuggerCategory
{
public:
    FGameplayDebuggerCategory_ObjectPool();

    virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;
    virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;

    static TSharedRef<FGameplayDebuggerCategory> MakeInstance();

protected:
    // 디버거 화면에 그리기 위해 복사해둘 데이터 구조체
    struct FRepData
    {
        struct FPoolEntry {
            FString Name;
            int32 Active;
            int32 Inactive;
        };
        TArray<FPoolEntry> Pools;
    };

    FRepData DataPack;
};
#endif