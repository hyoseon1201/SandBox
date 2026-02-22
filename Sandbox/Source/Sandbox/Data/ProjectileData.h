// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProjectileData.generated.h"

class UParticleSystem;

/**
 * 
 */
UCLASS()
class SANDBOX_API UProjectileData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UParticleSystem* ProjectileEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UParticleSystem* HitEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float InitialSpeed = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxSpeed = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float LifeSpan = 3.f;
};
