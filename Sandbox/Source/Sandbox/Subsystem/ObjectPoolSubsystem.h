// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ObjectPoolSubsystem.generated.h"

class ABaseProjectile;

USTRUCT()
struct FPoolStatInfo
{
	GENERATED_BODY()

	UPROPERTY()
	FString ClassName;

	UPROPERTY()
	int32 ActiveCount = 0;

	UPROPERTY()
	int32 InactiveCount = 0;
};

USTRUCT()
struct FProjectilePoolArray
{
	GENERATED_BODY()

	// 1. 전체 관리용 (Deinitialize 시 메모리 해제용)
	UPROPERTY()
	TArray<ABaseProjectile*> AllProjectiles;

	// 2. 비활성 객체 보관용 (O(1) 접근용 스택)
	UPROPERTY()
	TArray<ABaseProjectile*> InactivePool;
};

/**
 * 
 */
UCLASS()
class SANDBOX_API UObjectPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	ABaseProjectile* GetProjectile(TSubclassOf<ABaseProjectile> ProjectileClass);

	void ReturnToPool(ABaseProjectile* Projectile);

	TArray<FPoolStatInfo> GetPoolStatistics() const;

private:
	UPROPERTY()
	TMap<UClass*, FProjectilePoolArray> ObjectPools;

	ABaseProjectile* AllocateNewProjectile(TSubclassOf<ABaseProjectile> ProjectileClass);
};
