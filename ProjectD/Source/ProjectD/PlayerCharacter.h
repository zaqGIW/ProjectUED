// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"


struct FInputActionValue;


UCLASS()


class PROJECTD_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* MoveAction;

	void Move(const FInputActionValue& Value);
	/** Called for looking input */
	void Look(FVector Value);

	void LookStart();
	void LookEnd();

private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class USpringArmComponent* Comp_SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class UCameraComponent* Camera;
};

