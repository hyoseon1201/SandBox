// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/SandBoxUserWidget.h"
#include "OverlayUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOX_API UOverlayUserWidget : public USandBoxUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	TObjectPtr<USandBoxUserWidget> WBP_DebugMenu;
};
