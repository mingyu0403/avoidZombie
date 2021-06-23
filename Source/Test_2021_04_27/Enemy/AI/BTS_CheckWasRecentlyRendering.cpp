#include "BTS_CheckWasRecentlyRendering.h"

#include "AIController.h"
#include "../MyEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTS_CheckWasRecentlyRendering::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* MyBB = OwnerComp.GetAIOwner()->GetBlackboardComponent();
	if (MyBB == nullptr) return ;

	AMyEnemy* me = Cast<AMyEnemy>(OwnerComp.GetAIOwner()->GetPawn());

	bool isRendered = me->WasRecentlyRendered(0.1f);
	me->GetMesh()->bPauseAnims = isRendered;
	MyBB->SetValueAsBool(FName("bIsPause"), isRendered);
}
