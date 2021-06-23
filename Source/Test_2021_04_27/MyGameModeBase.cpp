#include "MyGameModeBase.h"

#include "MyCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "UI/MyHUD.h"

AMyGameModeBase::AMyGameModeBase()
{
	ConstructorHelpers::FClassFinder<AMyCharacter> BP_MyCharacter(TEXT("Blueprint'/Game/Blueprints/BP_Character.BP_Character_C'"));
	if (BP_MyCharacter.Succeeded())
	{
		DefaultPawnClass = BP_MyCharacter.Class;
	}
	HUDClass = AMyHUD::StaticClass();
}
