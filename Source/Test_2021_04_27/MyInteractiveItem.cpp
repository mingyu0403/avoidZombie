#include "MyInteractiveItem.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

AMyInteractiveItem::AMyInteractiveItem()
{
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("COLLISION"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	OutlineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OUTLINEMESH"));

	RootComponent = Collision;
	Mesh->SetupAttachment(RootComponent);
	OutlineMesh->SetupAttachment(Mesh);

	Collision->SetCollisionProfileName(TEXT("PickingItem"));
	Collision->SetSimulatePhysics(true);

	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	OutlineMesh->SetCollisionProfileName(TEXT("NoCollision"));

	ConstructorHelpers::FObjectFinder<UMaterialInstance> M_Outline(TEXT("MaterialInstanceConstant'/Game/Blueprints/MI_Outline.MI_Outline'"));
	if (M_Outline.Succeeded())
	{
		OutlineMaterial = M_Outline.Object;
	}
}

void AMyInteractiveItem::BeginPlay()
{
	Super::BeginPlay();

	UStaticMesh* UsedMesh = Mesh->GetStaticMesh();
	if (UsedMesh)
	{
		OutlineMesh->SetStaticMesh(UsedMesh);

		TArray<UMaterialInterface*> Materials = OutlineMesh->GetMaterials();
		for (int i = 0; i < Materials.Num(); i++)
		{
			OutlineMesh->SetMaterial(i, OutlineMaterial);
		}
	}

	SetOutlineVisible(false);
}

void AMyInteractiveItem::SetOutlineVisible(bool bIsVisible)
{
	OutlineMesh->SetVisibility(bIsVisible);
}
