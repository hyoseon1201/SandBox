// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/CombatComponent.h"
#include "Actor/BaseProjectile.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(GetMesh(), FName("WeaponSocket"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
}

UCombatComponent* ABaseCharacter::GetCombatComponent()
{
	return CombatComponent;
}

void ABaseCharacter::PlayAttackMontage()
{
	// 1. 이미 공격 중이거나 몽타주가 없으면 실행 안 함 (중복 클릭 방지)
	if (bIsAttacking || !AttackMontage) return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		bIsAttacking = true;

		// 2. 몽타주 재생! (엔진이 알아서 UpperBody 슬롯으로 보내줍니다)
		AnimInstance->Montage_Play(AttackMontage);

		// 3. 몽타주가 끝났을 때 다시 공격 가능하게 플래그 리셋
		FOnMontageEnded MontageEndedDelegate;
		MontageEndedDelegate.BindLambda([this](UAnimMontage* Montage, bool bInterrupted)
			{
				bIsAttacking = false;
			});
		AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, AttackMontage);
	}
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (CombatComponent && DefaultProjectileClass && DefaultProjectileData)
	{
		CombatComponent->EquipWeaponData(DefaultProjectileClass, DefaultProjectileData);
	}
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::FireWeapon()
{
	if (!CombatComponent || !WeaponMesh)
	{
		return;
	}

	FVector SpawnLocation = WeaponMesh->GetSocketLocation(FName("TipSocket"));
	FRotator SpawnRotation = GetActorRotation();

	CombatComponent->Fire(SpawnLocation, SpawnRotation);
}

