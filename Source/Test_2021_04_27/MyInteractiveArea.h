#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyInteractiveArea.generated.h"

class UBoxComponent;
class AMyInteractiveItem;
class AMyDoor;

UCLASS()
class TEST_2021_04_27_API AMyInteractiveArea : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyInteractiveArea();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* Trigger;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PreviewMesh;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interactive")
	AMyInteractiveItem* Item;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interactive")
	AMyDoor* Door;

public:
	UMaterialInstance* PreviewMaterial;

public:
	UFUNCTION()
	void OnItemOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
