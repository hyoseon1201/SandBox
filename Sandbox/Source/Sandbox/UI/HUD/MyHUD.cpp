// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/MyHUD.h"

#include "UI/Widget/SandBoxUserWidget.h"
#include "UI/WidgetController/DebugMenuWidgetController.h"
#include "Blueprint/UserWidget.h"

void AMyHUD::InitDebugMenu()
{
    DebugWidget = CreateWidget<USandBoxUserWidget>(GetWorld(), DebugWidgetClass);

    DebugController = NewObject<UDebugMenuWidgetController>(this, DebugControllerClass);

    DebugController->PlayerController = GetOwningPlayerController();
    DebugWidget->SetWidgetController(DebugController);
    DebugWidget->AddToViewport();
}
