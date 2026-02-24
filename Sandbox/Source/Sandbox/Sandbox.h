// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Modules/ModuleManager.h"

class FSandboxModule : public FDefaultGameModuleImpl
{
public:
	// 프로젝트가 시작될 때 호출됨
	virtual void StartupModule() override;

	// 프로젝트가 종료될 때 호출됨
	virtual void ShutdownModule() override;
};