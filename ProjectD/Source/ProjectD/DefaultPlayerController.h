// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DefaultPlayerController.generated.h"




UCLASS()
class PROJECTD_API ADefaultPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ADefaultPlayerController();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SetAimingClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SetAttackClickAction;


protected:
	class APlayerCharacter* Cls_playerCharacter;

	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;

	virtual void BeginPlay();

	void OnAimingInputStarted();
	void OnSetAimingTriggered();
	void OnSetAimingReleased();

	void OnAttackInputStarted();
	void OnAttackInputReleased();

private:
	FVector CachedDestination;

};
