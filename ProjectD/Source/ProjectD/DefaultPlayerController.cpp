// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerCharacter.h"

ADefaultPlayerController::ADefaultPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;	
}

void ADefaultPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetAimingClickAction, ETriggerEvent::Started, this, &ADefaultPlayerController::OnAimingInputStarted);
		EnhancedInputComponent->BindAction(SetAimingClickAction, ETriggerEvent::Triggered, this, &ADefaultPlayerController::OnSetAimingTriggered);
		EnhancedInputComponent->BindAction(SetAimingClickAction, ETriggerEvent::Completed, this, &ADefaultPlayerController::OnSetAimingReleased);
		EnhancedInputComponent->BindAction(SetAimingClickAction, ETriggerEvent::Canceled, this, &ADefaultPlayerController::OnSetAimingReleased);
		
		EnhancedInputComponent->BindAction(SetAttackClickAction, ETriggerEvent::Started, this, &ADefaultPlayerController::OnAttackInputStarted);
		EnhancedInputComponent->BindAction(SetAttackClickAction, ETriggerEvent::Completed, this, &ADefaultPlayerController::OnAttackInputReleased);
	}
}

void ADefaultPlayerController::BeginPlay()
{
	Super::BeginPlay();
	Cls_playerCharacter = Cast<APlayerCharacter>(GetPawn());
}

void ADefaultPlayerController::OnAimingInputStarted()
{
	//클릭 시작
	Cls_playerCharacter->LookStart();
}

void ADefaultPlayerController::OnSetAimingTriggered()
{
	
	FHitResult Hit;
	bool bHitSuccessful = false;

	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

	if (Cls_playerCharacter != nullptr)
	{
		FVector WorldDirection = (CachedDestination - Cls_playerCharacter->GetActorLocation()).GetSafeNormal();
		Cls_playerCharacter->Look(WorldDirection);
	}
}

void ADefaultPlayerController::OnSetAimingReleased()
{
	//클릭 끝
	Cls_playerCharacter->LookEnd();
}

void ADefaultPlayerController::OnAttackInputStarted()
{
}

void ADefaultPlayerController::OnAttackInputReleased()
{
}
