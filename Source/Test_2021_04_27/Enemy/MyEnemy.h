#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyEnemyAnim.h"

#include "MyEnemy.generated.h"

class UPawnSensingComponent;

UCLASS()
class TEST_2021_04_27_API AMyEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AMyEnemy();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPawnSensingComponent* PawnSensing;

public:
	UPROPERTY(VisibleAnywhere)
	UMyEnemyAnim* AnimBP;

public:
	UFUNCTION()
	void OnSeePawn(APawn* Pawn);
	
	void SetTarget(APawn* Pawn);
};
