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
	if (ProjectileClass == nullptr)
	{
		return nullptr;
	}

	FProjectilePoolArray* PoolData = ObjectPools.Find(ProjectileClass);

	if (PoolData)
	{
		for (ABaseProjectile* Proj : PoolData->Pool)
		{
			if (Proj->IsHidden() && Proj)
			{
				return Proj;
			}
		}
	}

	return AllocateNewProjectile(ProjectileClass);
}

ABaseProjectile* UObjectPoolSubsystem::AllocateNewProjectile(TSubclassOf<ABaseProjectile> ProjectileClass)
{
	if (ProjectileClass == nullptr)
	{
		return nullptr;
	}

	ABaseProjectile* NewProj = GetWorld()->SpawnActor<ABaseProjectile>(ProjectileClass, FVector::ZeroVector, FRotator::ZeroRotator);

	if (NewProj)
	{
		NewProj->SetActorHiddenInGame(true);

		FProjectilePoolArray& PoolData = ObjectPools.FindOrAdd(ProjectileClass);
		PoolData.Pool.Add(NewProj);
	}

	return NewProj;
}
