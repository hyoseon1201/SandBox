// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ObjectPoolSubsystem.generated.h"

class ABaseProjectile;

USTRUCT()
struct FProjectilePoolArray
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<ABaseProjectile*> Pool;
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

private:
	UPROPERTY()
	TMap<UClass*, FProjectilePoolArray> ObjectPools;

	ABaseProjectile* AllocateNewProjectile(TSubclassOf<ABaseProjectile> ProjectileClass);
};
