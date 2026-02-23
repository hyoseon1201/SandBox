// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DebugMenuWidgetController.generated.h"

UENUM(BlueprintType)
enum class EDebugOptionType : uint8
{
	ObjectPooling UMETA(DisplayName = "Object Pooling")
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class SANDBOX_API UDebugMenuWidgetController : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Debug|References")
	TObjectPtr<class APlayerController> PlayerController;
	
	UFUNCTION(BlueprintCallable, Category = "Debug|Actions")
	void ToggleDebugOption(EDebugOptionType OptionType, bool bEnable);
};
