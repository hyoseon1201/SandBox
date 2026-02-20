// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor/TestActor.h"
#include "TestActor.h"

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("TestActor: Construct"));
}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("TestActor: Begin"));

	Super::BeginPlay();
}

void ATestActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(LogTemp, Warning, TEXT("TestActor: End"));

	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestActor::Interact_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("TestActor: TestInterface::Interact Called"));
}

