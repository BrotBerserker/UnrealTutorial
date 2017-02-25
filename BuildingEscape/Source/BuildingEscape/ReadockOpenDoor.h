// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ReadockOpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UReadockOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UReadockOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;


	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnOpenRequest;
	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnInverseRequest;
	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnDoorCLosed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "-359", UIMax = "359"))
		float RotationAngle = 90.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0"))
		float MinTriggerMass = 5.f;

private:

	float startRoation;
	float doorMovementAngle = 0;
	int doorMovementDirection = 1;
	bool movingDoor = false;
	float doorLastOpenTime = 0;

	float GetToralMassOfActorsOnPLate();
	void CheckDoorPosition();
	void OpenDoor();
	void CloseDoor();

	UPROPERTY(EditAnywhere)
		float CloseDoorDelay = 0;
	UPROPERTY(EditAnywhere)
		bool ManualTrigger = false;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* TriggerSensor = nullptr;
	//UPROPERTY(EditAnywhere)
		//AActor* ActorThatOpens;
	//UPROPERTY(EditAnywhere, meta = (UIMin = "-359", UIMax = "359"))
	//	float RotationAngle;
	UPROPERTY(EditAnywhere, meta = (UIMin = "-359", UIMax = "359"))
		float RotationSpeed;

	
};
