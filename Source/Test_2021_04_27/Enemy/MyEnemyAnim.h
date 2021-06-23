#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyEnemyAnim.generated.h"

UENUM(BlueprintType)
enum class E_ENEMY_STATE : uint8
{
	E_IDLE,
	E_CHASE,
};

UCLASS()
class TEST_2021_04_27_API UMyEnemyAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "state")
	float Speed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "state")
	E_ENEMY_STATE CurrentState;
};
