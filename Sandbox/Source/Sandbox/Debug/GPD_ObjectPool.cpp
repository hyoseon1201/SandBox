#include "Debug/GPD_ObjectPool.h"

#if WITH_GAMEPLAY_DEBUGGER
#include "Subsystem/ObjectPoolSubsystem.h"

FGameplayDebuggerCategory_ObjectPool::FGameplayDebuggerCategory_ObjectPool()
{
    bShowOnlyWithDebugActor = false;
}

void FGameplayDebuggerCategory_ObjectPool::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
    if (UWorld* World = OwnerPC->GetWorld())
    {
        if (UObjectPoolSubsystem* PoolSub = World->GetSubsystem<UObjectPoolSubsystem>())
        {
            DataPack.Pools.Empty();

            // 서브시스템의 통계 함수 호출
            auto Stats = PoolSub->GetPoolStatistics();
            for (const auto& S : Stats)
            {
                DataPack.Pools.Add({ S.ClassName, S.ActiveCount, S.InactiveCount });
            }
        }
    }
}

void FGameplayDebuggerCategory_ObjectPool::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
    CanvasContext.Printf(FColor::Cyan, TEXT("[Sandbox Object Pool System]"));
    CanvasContext.Printf(FColor::Yellow, TEXT("%-20s | %7s | %8s"), TEXT("Class"), TEXT("Active"), TEXT("Inactive"));
    CanvasContext.Printf(FColor::Yellow, TEXT("--------------------------------------------------"));

    if (DataPack.Pools.Num() == 0)
    {
        CanvasContext.Printf(FColor::Red, TEXT("No active pools found."));
    }

    for (const auto& P : DataPack.Pools)
    {
        CanvasContext.Printf(FColor::White, TEXT("%-20s | %7d | %8d"), *P.Name, P.Active, P.Inactive);
    }
}

TSharedRef<FGameplayDebuggerCategory> FGameplayDebuggerCategory_ObjectPool::MakeInstance()
{
    return MakeShareable(new FGameplayDebuggerCategory_ObjectPool());
}
#endif