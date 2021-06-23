#include "MyEnemyAnim.h"

#include "MyEnemy.h"
#include "GameFramework/PawnMovementComponent.h"

void UMyEnemyAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AMyEnemy* Owner = Cast<AMyEnemy>(TryGetPawnOwner());
	if (Owner)
	{
		Speed = Owner->GetMovementComponent()->Velocity.Size();
	}
}
