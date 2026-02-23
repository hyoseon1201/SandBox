// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

class USandBoxUserWidget;
class UDebugMenuWidgetController;

/**
 * 
 */
UCLASS()
class SANDBOX_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void InitDebugMenu();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<USandBoxUserWidget> DebugWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UDebugMenuWidgetController> DebugControllerClass;

private:
	UPROPERTY()
	TObjectPtr<USandBoxUserWidget> DebugWidget;

	UPROPERTY()
	TObjectPtr<UDebugMenuWidgetController> DebugController;
};
