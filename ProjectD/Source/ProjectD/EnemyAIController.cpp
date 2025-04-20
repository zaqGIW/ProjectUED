// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"


// Perception
#include "Perception/AISense_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

#include "GameFramework/Character.h"

AEnemyAIController::AEnemyAIController()
{
	// Component Initialize
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

	SetPerceptionComponent(*AIPerceptionComponent);

    // 시야 설정
    SightConfig->SightRadius = 1500.f; // 1500
    SightConfig->LoseSightRadius = 1800.f; // 1800
    SightConfig->PeripheralVisionAngleDegrees = 90.f;
    SightConfig->SetMaxAge(5.f);
    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

    AIPerceptionComponent->SetDominantSense(*SightConfig->GetSenseImplementation());

    // 콜백 바인딩
    AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetPerceptionUpdated);

    // BT 컴포넌트
    BTComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
    BBComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}

void AEnemyAIController::BeginPlay()
{
    Super::BeginPlay();
}

void AEnemyAIController::Tick(float DeltaTime)
{
    //Super::Tick(DeltaTime);
}

// EnemyCharacter에서 이 컨트롤러가 활성화 될때 BT 동작하게함
void AEnemyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(InPawn))
    {
        if (EnemyBT) // 언리얼 에디터에서 설정한 BehaviorTree 가 있는경우
        {
            BBComponent->InitializeBlackboard(*EnemyBT->BlackboardAsset);
            BTComponent->StartTree(*EnemyBT);
        }
    }

}

void AEnemyAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    if (BBComponent) return;

    if (Stimulus.WasSuccessfullySensed())
    {
        // 플레이어 발견
        BBComponent->SetValueAsObject(TEXT("TargetActor"), Actor);
        BBComponent->SetValueAsVector(TEXT("LastKnownLocation"), Actor->GetActorLocation());
    }
    else
    {
        // 놓침
        BBComponent->ClearValue(TEXT("TargetActor"));
    }
}