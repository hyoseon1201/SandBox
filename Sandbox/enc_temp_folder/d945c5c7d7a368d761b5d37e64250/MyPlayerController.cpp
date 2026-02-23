// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MyPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/Character.h"
#include "Character/BaseCharacter.h"

void AMyPlayerController::SetUIInputMode(bool bEnableUI)
{
    bIsUIInputMode = bEnableUI;
    bShowMouseCursor = bEnableUI;

    if (bEnableUI)
    {
        FInputModeGameAndUI InputMode;
        InputMode.SetHideCursorDuringCapture(false);
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        SetInputMode(InputMode);

        SetIgnoreLookInput(true);
    }
    else
    {
        FInputModeGameOnly InputMode;
        SetInputMode(InputMode);

        SetIgnoreLookInput(false);
    }
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        if (DefaultMappingContext)
        {
            Subsystem->RemoveMappingContext(DefaultMappingContext);
            Subsystem->AddMappingContext(DefaultMappingContext, MappingPriority);
        }
    }
}

void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Move);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Jump);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Look);
        EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &AMyPlayerController::Fire);
        EnhancedInputComponent->BindAction(ChangeInputModeAction, ETriggerEvent::Started, this, &AMyPlayerController::ChangeInputMode);
    }
}

void AMyPlayerController::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    APawn* ControlledPawn = GetPawn();

    if (ControlledPawn != nullptr)
    {
        const FRotator Rotation = GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
        ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
    }
}

void AMyPlayerController::Jump(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        if (ACharacter* ControlledCharacter = Cast<ACharacter>(ControlledPawn))
        {
            ControlledCharacter->Jump();
        }
    }
}

void AMyPlayerController::Look(const FInputActionValue& Value)
{
    if (bIsUIInputMode) return;

    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (APawn* ControlledPawn = GetPawn())
    {
        AddYawInput(LookAxisVector.X);

        AddPitchInput(-LookAxisVector.Y);
    }
}

void AMyPlayerController::Fire(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        if (ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(ControlledPawn))
        {
            MyCharacter->FireWeapon();
        }
    }
}

void AMyPlayerController::ChangeInputMode(const FInputActionValue& Value)
{
    SetUIInputMode(!bIsUIInputMode);
}
