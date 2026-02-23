// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/DebugMenuWidgetController.h"

#include "Character/BaseCharacter.h" 
#include "Component/CombatComponent.h"

void UDebugMenuWidgetController::ToggleDebugOption(EDebugOptionType OptionType, bool bEnable)
{
	switch (OptionType)
	{
		case EDebugOptionType::ObjectPooling:
		{
			if (PlayerController)
			{
				ABaseCharacter* PlayerCharacter = Cast<ABaseCharacter>(PlayerController->GetPawn());
				if (PlayerCharacter)
				{
					UCombatComponent* CombatComp = PlayerCharacter->GetCombatComponent();
					if (CombatComp)
					{
						CombatComp->SetUseObjectPooling(bEnable);

						UE_LOG(LogTemp, Warning, TEXT("오브젝트 풀링 모드 : %s"), CombatComp->GetUseObjectPooling() ? TEXT("ON") : TEXT("OFF"));
					}
				}
			}
			break;
		}
	}
}
