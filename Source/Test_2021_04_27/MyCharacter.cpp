// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "MyInteractiveItem.h"
#include "Components/BoxComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add("PLAYER");

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PHYSICSHANDLE"));

	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector(0.0f, 0.0f, 30.0f));

	bUseControllerRotationYaw = false;
	Camera->bUsePawnControlRotation = true;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	TArray<AActor*> IgnoreActors;
	FHitResult HitResult;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1));

	bool Result = UKismetSystemLibrary::LineTraceSingleForObjects(
		GetWorld(),
		Camera->GetComponentLocation(),
		Camera->GetComponentLocation() + Camera->GetForwardVector() * 500.0f,
		ObjectTypes,
		false,
		IgnoreActors,
		EDrawDebugTrace::None,
		HitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		1.0f
	);

	if (CurrentTargetItem)
	{
		CurrentTargetItem->SetOutlineVisible(false);
		CurrentTargetItem = nullptr;
	}

	if (Result)
	{
		AMyInteractiveItem* Item = Cast<AMyInteractiveItem>(HitResult.Actor);
		if (Item)
		{
			CurrentTargetItem = Item;
			CurrentTargetItem->SetOutlineVisible(true);
		}
	}

	if (bIsGrabbing)
	{
		FVector GrabbedObjectLocation = Camera->GetComponentLocation() + Camera->GetForwardVector() * 200.0f;
		PhysicsHandle->SetTargetLocation(GrabbedObjectLocation);
	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("Turn"), this, &AMyCharacter::OnTurn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &AMyCharacter::OnLookUp);
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &AMyCharacter::OnMoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &AMyCharacter::OnMoveRight);

	PlayerInputComponent->BindAction(FName("LeftMouseButton"), EInputEvent::IE_Pressed, this, &AMyCharacter::OnPick);
	PlayerInputComponent->BindAction(FName("LeftMouseButton"), EInputEvent::IE_Released, this, &AMyCharacter::OnDrop);
}

void AMyCharacter::OnTurn(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void AMyCharacter::OnLookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void AMyCharacter::OnMoveForward(float AxisValue)
{
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(FRotator(0.0f, GetControlRotation().Yaw, 0.0f));
	AddMovementInput(ForwardVector, AxisValue);
}

void AMyCharacter::OnMoveRight(float AxisValue)
{
	FVector RightVector = UKismetMathLibrary::GetRightVector(FRotator(0.0f, GetControlRotation().Yaw, 0.0f));
	AddMovementInput(RightVector, AxisValue);
}

void AMyCharacter::OnPick()
{
	if (CurrentTargetItem)
	{
		bIsGrabbing = true;

		PhysicsHandle->GrabComponentAtLocationWithRotation(
			CurrentTargetItem->Collision,
			NAME_None,
			CurrentTargetItem->GetActorLocation(),
			FRotator::ZeroRotator
		);
	}
}

void AMyCharacter::OnDrop()
{
	PhysicsHandle->ReleaseComponent();
}

