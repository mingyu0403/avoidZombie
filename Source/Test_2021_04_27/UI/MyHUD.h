// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class TEST_2021_04_27_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AMyHUD();
	
public:
	void ShowCrossHair(bool bIsShow);

public:
	UUserWidget* CrossHair;
};
