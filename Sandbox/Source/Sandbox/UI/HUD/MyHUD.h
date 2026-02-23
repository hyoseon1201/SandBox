// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

class UDebugMenuWidgetController;
class UOverlayUserWidget;
class UOverlayUserWidgetController;

/**
 * 
 */
UCLASS()
class SANDBOX_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void InitOverlay();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UOverlayUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayUserWidget> OverlayWidget;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UOverlayUserWidgetController> OverlayControllerClass;

	UPROPERTY()
	TObjectPtr<UOverlayUserWidgetController> OverlayController;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UDebugMenuWidgetController> DebugControllerClass;

	UPROPERTY()
	TObjectPtr<UDebugMenuWidgetController> DebugController;
};
