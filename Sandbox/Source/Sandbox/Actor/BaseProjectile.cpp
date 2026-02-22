// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/BaseProjectile.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Data/ProjectileData.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(30.f);
	RootComponent = CollisionComponent;

	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComponent"));
	ParticleComponent->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->UpdatedComponent = CollisionComponent;

	ProjectileMovementComponent->InitialSpeed = 1000.f;
	ProjectileMovementComponent->MaxSpeed = 1000.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseProjectile::InitializeProjectile(UProjectileData* Data, bool bIsPooled)
{
	if (Data == nullptr) return;

	ProjectileDataAsset = Data;

	SetActorHiddenInGame(false);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	if (Data->ProjectileEffect)
	{
		ParticleComponent->SetTemplate(Data->ProjectileEffect);
		ParticleComponent->ActivateSystem();
	}
	else
	{
		ParticleComponent->DeactivateSystem();
	}

	ProjectileMovementComponent->InitialSpeed = Data->InitialSpeed;
	ProjectileMovementComponent->MaxSpeed = Data->MaxSpeed;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	ProjectileMovementComponent->Velocity = GetActorForwardVector() * Data->InitialSpeed;
	ProjectileMovementComponent->Activate();

	if (bIsPooled)
	{
		// 풀링 모드
		GetWorld()->GetTimerManager().SetTimer(LifeSpanTimer, this, &ABaseProjectile::DeactivateProjectile, Data->LifeSpan, false);
	}
	else
	{
		// 기본 모드
		SetLifeSpan(Data->LifeSpan);
	}
}

void ABaseProjectile::DeactivateProjectile()
{
	SetActorHiddenInGame(true);
	ParticleComponent->DeactivateSystem();

	ProjectileMovementComponent->StopMovementImmediately();
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

