// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SandBoxUserWidget.h"

void USandBoxUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;

	WidgetControllerSet();
}
