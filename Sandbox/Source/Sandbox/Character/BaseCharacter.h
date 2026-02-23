// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UStaticMeshComponent;
class UCombatComponent;
class ABaseProjectile;
class UProjectileData;

UCLASS()
class SANDBOX_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	UCombatComponent* GetCombatComponent();

	void PlayAttackMontage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCombatComponent* CombatComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<ABaseProjectile> DefaultProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UProjectileData* DefaultProjectileData;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UAnimMontage> AttackMontage;

	bool bIsAttacking = false;
public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void FireWeapon();
};
