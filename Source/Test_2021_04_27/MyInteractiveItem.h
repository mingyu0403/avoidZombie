#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyInteractiveItem.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class TEST_2021_04_27_API AMyInteractiveItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyInteractiveItem();

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* Collision;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* OutlineMesh;

public:
	UMaterialInstance* OutlineMaterial;

public:
	void SetOutlineVisible(bool bIsVisible);
};
