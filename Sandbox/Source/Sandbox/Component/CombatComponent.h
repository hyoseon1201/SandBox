// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

class ABaseProjectile;
class UProjectileData;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SANDBOX_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent();

	void SetUseObjectPooling(bool useValue);
	bool GetUseObjectPooling();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat|ProjectilePool")
	TSubclassOf<ABaseProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat|ProjectilePool")
	UProjectileData* CurrentProjectileData;

	UPROPERTY(EditAnywhere, Category = "Combat|ProjectilePool")
	bool bUseObjectPooling = true;

public:	
	void EquipWeaponData(TSubclassOf<ABaseProjectile> NewClass, UProjectileData* NewData);

	void Fire(FVector SpawnLocation, FRotator SpawnRotation);
};
