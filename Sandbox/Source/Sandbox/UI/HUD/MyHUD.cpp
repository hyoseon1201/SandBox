// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/MyHUD.h"

#include "UI/Widget/OverlayUserWidget.h"
#include "UI/WidgetController/DebugMenuWidgetController.h"
#include "Blueprint/UserWidget.h"
#include "UI/WidgetController/OverlayUserWidgetController.h"

void AMyHUD::InitOverlay()
{
    if (!OverlayWidgetClass)
    {
        UE_LOG(LogTemp, Error, TEXT("OverlayWidgetClass is NULL! Check BP_MyHUD."));
        return;
    }

    // 1. 오버레이 위젯 생성 및 출력
    OverlayWidget = CreateWidget<UOverlayUserWidget>(GetWorld(), OverlayWidgetClass);

    if (OverlayWidget)
    {
        OverlayWidget->AddToViewport();

        // 2. 오버레이 컨트롤러 생성 및 주입 (중앙 관리자)
        OverlayController = NewObject<UOverlayUserWidgetController>(this, OverlayControllerClass);
        OverlayController->PlayerController = GetOwningPlayerController();

        // 오버레이 본체에 오버레이 전용 매니저 주입
        OverlayWidget->SetWidgetController(OverlayController);

        // 3. 디버그 컨트롤러 생성 및 자식 위젯에 직접 주입 (특수 관리자)
        DebugController = NewObject<UDebugMenuWidgetController>(this, DebugControllerClass);
        DebugController->PlayerController = GetOwningPlayerController();

        if (OverlayWidget->WBP_DebugMenu)
        {
            OverlayWidget->WBP_DebugMenu->SetWidgetController(DebugController);
        }
    }
}

void AMyHUD::BeginPlay()
{
    Super::BeginPlay();

    InitOverlay();
}
