// Copyright Epic Games, Inc. All Rights Reserved.

#include "Sandbox.h"
#include "Modules/ModuleManager.h"

// 1. 디버거 관련 헤더 포함
#if WITH_GAMEPLAY_DEBUGGER
#include "GameplayDebugger.h"
#include "Debug/GPD_ObjectPool.h"
#endif

void FSandboxModule::StartupModule()
{
	// 기본 모듈 시작 로직 호출
	FDefaultGameModuleImpl::StartupModule();

	UE_LOG(LogTemp, Warning, TEXT("!!! SANDBOX MODULE STARTUP !!!"));

#if WITH_GAMEPLAY_DEBUGGER
	// 2. 엔진의 GameplayDebugger 모듈을 가져와서 카테고리 등록
	IGameplayDebugger& DebuggerModule = IGameplayDebugger::Get();

	// "ObjectPool"이라는 이름으로 등록. 숫자 패드에서 비어있는 번호에 자동으로 할당됨
	DebuggerModule.RegisterCategory("ObjectPool", IGameplayDebugger::FOnGetCategory::CreateStatic(&FGameplayDebuggerCategory_ObjectPool::MakeInstance));

	// 등록 후 콘솔에 알림 (디버깅용)
	UE_LOG(LogTemp, Log, TEXT("GameplayDebugger: ObjectPool Category Registered."));
#endif
}

void FSandboxModule::ShutdownModule()
{
	FDefaultGameModuleImpl::ShutdownModule();

#if WITH_GAMEPLAY_DEBUGGER
	// 3. 종료 시에는 반드시 등록 해제 (메모리 누수 및 크래시 방지)
	if (IGameplayDebugger::IsAvailable())
	{
		IGameplayDebugger::Get().UnregisterCategory("ObjectPool");
	}
#endif
}

IMPLEMENT_PRIMARY_GAME_MODULE(FSandboxModule, Sandbox, "Sandbox");