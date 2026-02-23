// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_Fire.h"

#include "Character/BaseCharacter.h"

void UAnimNotify_Fire::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp == nullptr)
	{
		return;
	}

	if (AActor* Owner = MeshComp->GetOwner())
	{
		if (ABaseCharacter* Character = Cast<ABaseCharacter>(Owner))
		{
			Character->FireWeapon();
		}
	}
}
