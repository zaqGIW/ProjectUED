// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

// Perception으로 AI 시야 및 정보 넘김
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "EnemyCharacter.h"

#include "EnemyAIController.generated.h"

class UAISenseConfig_Sight;
class UBehaviorTree;
class UBlackboardComponent;
class UBehaviorTreeComponent;
class UAIPerceptionComponent;
/**
 * 
 * AI 의 적 탐색과정
 * 1. Perceptino컴포넌트의 Sight, hear 요소들에서 Player위치 파악
 * 2. EQS의 최적의 이동위치로 공격 및 아이템 사용하게 유도
 */
UCLASS()
class PROJECTD_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();
protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	UAISenseConfig_Sight* SightConfig; // 시야정보 전달함

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite , Category = "AI")
	UBehaviorTree* EnemyBT; // 외부에서 설정할 BT ( 설계도)

	UPROPERTY()
	UBehaviorTreeComponent* BTComponent;

	// 메모리 실행기
	UPROPERTY()
	UBlackboardComponent* BBComponent;

	// PerceptionCallBack
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	// Stimulus : AI 가 감지한 정보에 대한 상세정보구조체
public:
	FORCEINLINE UBlackboardComponent* GetBlackboardComponent() const { return BBComponent; }

	UPROPERTY()
	bool bIsTargetVisible;
private:
	UPROPERTY()

	
	float SightRadius;
	float HalfVisionAngleRad; // 시야각의 절반을 라디안으로 저장해서 연산 편하게 하기
};
