// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class UCameraComponent;
class UPhysicsHandleComponent;
class AMyInteractiveItem;

UCLASS()
class TEST_2021_04_27_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	UPROPERTY(VisibleAnywhere, Category="Character")
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = "Character")
	UPhysicsHandleComponent* PhysicsHandle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Character")
	float WalkSpeed = 350.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character")
	bool bIsGrabbing = false;

public:
	AMyInteractiveItem* CurrentTargetItem;

public:
	UFUNCTION()
	void OnTurn(float AxisValue);
	UFUNCTION()
	void OnLookUp(float AxisValue);
	UFUNCTION()
	void OnMoveForward(float AxisValue);
	UFUNCTION()
	void OnMoveRight(float AxisValue);
	UFUNCTION()
	void OnPick();
	UFUNCTION()
	void OnDrop();
};
