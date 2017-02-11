// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ReadockOpenDoor.generated.h"


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

	void MoveDoor();
	void OpenDoor();
	void CloseDoor();

private:


	UPROPERTY(EditAnywhere)
		float CloseDoorDelay = 0;
	UPROPERTY(EditAnywhere)
		bool ManualTrigger = false;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* TriggerSensor;
	UPROPERTY(EditAnywhere)
		AActor* ActorThatOpens;
	UPROPERTY(EditAnywhere, meta = (UIMin = "-359", UIMax = "359"))
		float RotationAngle;
	UPROPERTY(EditAnywhere, meta = (UIMin = "-359", UIMax = "359"))
		float RotationSpeed;

	
};
