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

	UPROPERTY(EditAnywhere, Category = "Move")
	float moveRunSpeed = 500.f;

	UPROPERTY(EditAnywhere, Category = "Move")
	float moveWalkSpeed = 250.f;

	void Move(const FInputActionValue& Value);
	/** Called for looking input */
	void Look(FVector Value);

	void LookStart();
	void LookEnd();

	UFUNCTION(BlueprintNativeEvent)
	void Attack();

	// C++ 기본 구현을 제공하는 Attack_Implementation 함수 선언
	void Attack_Implementation();

private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class USpringArmComponent* Comp_SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class UCameraComponent* Camera;
};

