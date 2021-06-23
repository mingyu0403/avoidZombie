#include "MyDoor.h"

#include "Components/StaticMeshComponent.h"

AMyDoor::AMyDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DOORFRAME"));
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DOOR"));
	DoorGlass = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DOORGLASS"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> SM_DoorFrame(TEXT("StaticMesh'/Game/SovietRoom/Meshes/Objects/Door01_Frame01.Door01_Frame01'"));
	if (SM_DoorFrame.Succeeded())
	{
		DoorFrame->SetStaticMesh(SM_DoorFrame.Object);
	}
	ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Door(TEXT("StaticMesh'/Game/SovietRoom/Meshes/Objects/Door01.Door01'"));
	if (SM_Door.Succeeded())
	{
		Door->SetStaticMesh(SM_Door.Object);
	}
	ConstructorHelpers::FObjectFinder<UStaticMesh> SM_DoorGlass(TEXT("StaticMesh'/Game/SovietRoom/Meshes/Objects/Door01_Glass01.Door01_Glass01'"));
	if (SM_DoorGlass.Succeeded())
	{
		DoorGlass->SetStaticMesh(SM_DoorGlass.Object);
	}
	
	RootComponent = DoorFrame;
	Door->SetupAttachment(RootComponent);
	DoorGlass->SetupAttachment(Door);

	Door->SetRelativeLocation(FVector(50.0f, 0.0f, 0.0f));
}

void AMyDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Door)
	{
		float NextAngle = bIsOpen ? DoorAngleOpen : DoorAngleClose;
		Door->SetRelativeRotation(
			FRotator(0.0f, FMath::FInterpTo(Door->GetRelativeRotation().Yaw, NextAngle, GetWorld()->GetDeltaSeconds(), 3.0f), 0.0f)
		);
	}
}

void AMyDoor::SetDoorOpen(bool IsOpen)
{
	bIsOpen = IsOpen;
}

