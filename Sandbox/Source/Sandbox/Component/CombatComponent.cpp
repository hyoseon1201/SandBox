// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/CombatComponent.h"

#include "Actor/BaseProjectile.h" 
#include "Data/ProjectileData.h"
#include "Subsystem/ObjectPoolSubsystem.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UCombatComponent::SetUseObjectPooling(bool useValue)
{
	bUseObjectPooling = useValue;
}

bool UCombatComponent::GetUseObjectPooling()
{
	return bUseObjectPooling;
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UCombatComponent::EquipWeaponData(TSubclassOf<ABaseProjectile> NewClass, UProjectileData* NewData)
{
	ProjectileClass = NewClass;
	CurrentProjectileData = NewData;
}

void UCombatComponent::Fire(FVector SpawnLocation, FRotator SpawnRotation)
{
	if (!ProjectileClass || !CurrentProjectileData) return;

	if (bUseObjectPooling)
	{
		UObjectPoolSubsystem* PoolManager = GetWorld()->GetSubsystem<UObjectPoolSubsystem>();

		if (PoolManager)
		{
			ABaseProjectile* PooledProjectile = PoolManager->GetProjectile(ProjectileClass);

			if (PooledProjectile)
			{
				PooledProjectile->SetActorLocationAndRotation(SpawnLocation, SpawnRotation);
				PooledProjectile->InitializeProjectile(CurrentProjectileData, true);
			}
		}
	}
	else
	{
		ABaseProjectile* NewProjectile = GetWorld()->SpawnActor<ABaseProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
		if (NewProjectile)
		{
			NewProjectile->InitializeProjectile(CurrentProjectileData, false);
		}
	}
}

