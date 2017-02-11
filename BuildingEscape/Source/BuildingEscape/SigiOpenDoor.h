// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "SigiOpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API USigiOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USigiOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	bool isDoorTriggered();

	void OpenDoor();

private:

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpens;

	UPROPERTY(EditAnywhere)
	float openSpeed = 2;

	UPROPERTY(EditAnywhere, meta = (UIMin = "0", UIMax = "359", ClampMin = "0", ClampMax = "359"))
	float maxAngle = 180;
	
};
