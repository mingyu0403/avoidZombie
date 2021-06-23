// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyDoor.generated.h"

class UStaticMeshComponent;

UCLASS()
class TEST_2021_04_27_API AMyDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyDoor();

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorFrame;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Door;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorGlass;

public:
	float DoorAngleClose = 0.0f;
	float DoorAngleOpen = 80.0f;

	bool bIsOpen = false;

public:
	void SetDoorOpen(bool IsOpen);

};
