// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/ObjectPoolSubsystem.h"

#include "Actor/BaseProjectile.h"

void UObjectPoolSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
}

void UObjectPoolSubsystem::Deinitialize()
{
	ObjectPools.Empty();
}

ABaseProjectile* UObjectPoolSubsystem::GetProjectile(TSubclassOf<ABaseProjectile> ProjectileClass)
{
    if (!ProjectileClass) return nullptr;

    FProjectilePoolArray& PoolData = ObjectPools.FindOrAdd(ProjectileClass);

    // 루프 없이 바로 마지막 요소를 꺼내옴 (O(1))
    if (PoolData.InactivePool.Num() > 0)
    {
        ABaseProjectile* Proj = PoolData.InactivePool.Pop();

        // 꺼내온 즉시 활성화 처리 (발사 준비)
        if (Proj)
        {
            Proj->SetActorHiddenInGame(false);
            Proj->SetActorEnableCollision(true);
            return Proj;
        }
    }

    // 비활성 객체가 없다면 새로 생성 (O(1))
    return AllocateNewProjectile(ProjectileClass);
}

void UObjectPoolSubsystem::ReturnToPool(ABaseProjectile* Projectile)
{
    if (!Projectile) return;

    FProjectilePoolArray& PoolData = ObjectPools.FindOrAdd(Projectile->GetClass());
    PoolData.InactivePool.AddUnique(Projectile);
}

TArray<FPoolStatInfo> UObjectPoolSubsystem::GetPoolStatistics() const
{
    TArray<FPoolStatInfo> Stats;

    for (const auto& Pair : ObjectPools)
    {
        if (Pair.Key == nullptr) continue;

        FPoolStatInfo Info;
        Info.ClassName = Pair.Key->GetName();
        Info.InactiveCount = Pair.Value.InactivePool.Num();
        Info.ActiveCount = Pair.Value.AllProjectiles.Num() - Info.InactiveCount;

        Stats.Add(Info);
    }

    return Stats;
}

ABaseProjectile* UObjectPoolSubsystem::AllocateNewProjectile(TSubclassOf<ABaseProjectile> ProjectileClass)
{
    ABaseProjectile* NewProj = GetWorld()->SpawnActor<ABaseProjectile>(ProjectileClass);

    if (NewProj)
    {
        FProjectilePoolArray& PoolData = ObjectPools.FindOrAdd(ProjectileClass);
        PoolData.AllProjectiles.Add(NewProj);
        UE_LOG(LogTemp, Warning, TEXT("Allocate!"));
    }

    return NewProj;
}
