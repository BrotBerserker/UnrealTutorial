// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "SigiOpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

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

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpenRequest;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnCloseRequest;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0", UIMax = "359", ClampMin = "0", ClampMax = "359"))
	float openAngle = 180;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0", UIMax = "359", ClampMin = "0", ClampMax = "359"))
	float closedAngle = 180;

private:

	enum DoorState {
		OPEN,
		CLOSED,
		OPENING,
		CLOSING
	};

	int state = DoorState::CLOSED;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay;

	UPROPERTY(EditAnywhere)
	float TriggerMass;

	float LastDoorOpenTime;

	UPROPERTY(EditAnywhere)
	float openSpeed = 2;

	bool isCloseDoorTriggered();

	bool isOpenDoorTriggered();

	bool isTriggerTriggered();

	void OpenDoor();

	void CloseDoor();

	float GetTotalMassOfActorsOnPlate();

};
