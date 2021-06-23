#include "MyHUD.h"

#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

AMyHUD::AMyHUD()
{
	ConstructorHelpers::FClassFinder<UUserWidget> UW_CrossHair(TEXT("WidgetBlueprint'/Game/Blueprints/UI/CrossHair.CrossHair_C'"));
	if (UW_CrossHair.Succeeded())
	{
		CrossHair = CreateWidget<UUserWidget>(GetWorld(), UW_CrossHair.Class);
		if (CrossHair)
		{
			CrossHair->AddToViewport();
			ShowCrossHair(true);
		}
	}
}

void AMyHUD::ShowCrossHair(bool bIsShow)
{
	if (CrossHair)
	{
		CrossHair->SetVisibility(bIsShow ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}
