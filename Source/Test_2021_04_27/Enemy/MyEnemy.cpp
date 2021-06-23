#include "MyEnemy.h"

#include "Perception/PawnSensingComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AMyEnemy::AMyEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PAWNSENSING"));

	ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Enemy(TEXT("SkeletalMesh'/Game/ZombiePackV1/ZombieAA/Mesh/SK_ZombieAA.SK_ZombieAA'"));
	if (SK_Enemy.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Enemy.Object);
	}
	ConstructorHelpers::FClassFinder<UAnimInstance> ABP_Anim(TEXT("AnimBlueprint'/Game/Blueprints/Enemy/ABP_Enemy.ABP_Enemy_C'"));
	if (ABP_Anim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ABP_Anim.Class);
	}

	PawnSensing->SightRadius = 500.0f;
	PawnSensing->SetPeripheralVisionAngle(60.0f);
	GetCharacterMovement()->MaxWalkSpeed = 100.0f;
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
}

void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AnimBP = Cast<UMyEnemyAnim>(GetMesh()->GetAnimInstance());
	PawnSensing->OnSeePawn.AddDynamic(this, &AMyEnemy::OnSeePawn);
}

void AMyEnemy::OnSeePawn(APawn* Pawn)
{
	if (Pawn->ActorHasTag("PLAYER"))
	{
		SetTarget(Pawn);
	}
}

void AMyEnemy::SetTarget(APawn* Pawn)
{
	UE_LOG(LogClass, Warning, TEXT("asd"));
	UBlackboardComponent* MyBB = UAIBlueprintHelperLibrary::GetBlackboard(this);
	if (MyBB)
	{
		MyBB->SetValueAsObject(FName("TargetActor"), Pawn);
		AnimBP->CurrentState = E_ENEMY_STATE::E_CHASE;
	}
}


