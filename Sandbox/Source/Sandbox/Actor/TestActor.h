// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/TestInterface.h"
#include "TestActor.generated.h"

UCLASS()
class SANDBOX_API ATestActor : public AActor, public ITestInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// * Begin TestInterface * //
public:
	virtual void Interact_Implementation() override;
	// * End TestInterface * //
};
