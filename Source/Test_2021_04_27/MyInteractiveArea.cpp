#include "MyInteractiveArea.h"

#include "Components/BillboardComponent.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MyInteractiveItem.h"
#include "MyDoor.h"

AMyInteractiveArea::AMyInteractiveArea()
{
	PrimaryActorTick.bCanEverTick = false;

	UBillboardComponent* Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("BILLBOARD"));

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	PreviewMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PREVIEWMESH"));

	RootComponent = Trigger;
	PreviewMesh->SetupAttachment(RootComponent);
	Billboard->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UMaterialInstance> M_Preview(TEXT("MaterialInstanceConstant'/Game/Blueprints/MI_Preview.MI_Preview'"));
	if (M_Preview.Succeeded())
	{
		PreviewMaterial = M_Preview.Object;
	}
}

void AMyInteractiveArea::BeginPlay()
{
	Super::BeginPlay();
	
	if (Item)
	{
		PreviewMesh->SetStaticMesh(Item->Mesh->GetStaticMesh());
		PreviewMesh->SetRelativeScale3D(Item->Mesh->GetRelativeScale3D());
		TArray<UMaterialInterface*> Materials = Item->Mesh->GetMaterials();
		for (int i = 0; i < Materials.Num(); i++)
		{
			PreviewMesh->SetMaterial(i, PreviewMaterial);
		}
		PreviewMesh->SetCollisionProfileName(TEXT("NoCollision"));
	}
}

void AMyInteractiveArea::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMyInteractiveArea::OnItemOverlap);
}

void AMyInteractiveArea::OnItemOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyInteractiveItem* OverlappedItem = Cast<AMyInteractiveItem>(OtherActor);
	if (nullptr == OverlappedItem) return;

	if (OverlappedItem == Item)
	{
		TArray<UMaterialInterface*> Materials = Item->Mesh->GetMaterials();
		for (int i = 0; i < Materials.Num(); i++)
		{
			PreviewMesh->SetMaterial(i, Materials[i]);
		}
		PreviewMesh->SetCollisionProfileName(TEXT("BlockAll"));
		PreviewMesh->SetSimulatePhysics(true);
		PreviewMesh->SetEnableGravity(true);

		OverlappedItem->Destroy();
		Trigger->OnComponentBeginOverlap.Clear();
		
		if (Door)
		{
			Door->SetDoorOpen(true);
		}
	}
}


