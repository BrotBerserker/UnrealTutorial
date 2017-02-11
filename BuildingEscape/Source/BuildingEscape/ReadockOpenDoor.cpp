// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "ReadockOpenDoor.h"


float startRoation;

// Sets default values for this component's properties
UReadockOpenDoor::UReadockOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UReadockOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	auto transform = GetOwner()->GetTransform();
	startRoation = transform.GetRotation().Y;
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}


static bool IsBetween(float value, float a, float b) {
	return (value >= a && value <= b) || (value <= a && value >= b);
}

// Called every frame
void UReadockOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (TriggerSensor!= NULL && ActorThatOpens!= NULL 
		&& TriggerSensor->IsOverlappingActor(ActorThatOpens))
		openDoor = true;

	if(openDoor)
		OpenDoor();

}

void UReadockOpenDoor::OpenDoor() {
	auto transform = GetOwner()->GetTransform();
	bool lastStep = IsBetween(FRotator(GetOwner()->GetTransform().GetRotation()).Yaw, startRoation + RotationAngle + RotationSpeed + 0.1, startRoation + RotationAngle - RotationSpeed - 0.1);
	if (lastStep) {
		openDoor = false;
		return;
	}
	auto newRotation = FRotator(transform.GetRotation()) + FRotator(0, RotationSpeed, 0);
	//newRotation.Yaw = lastStep ? startRoation + RotationAngle : newRotation.Yaw;
	GetOwner()->SetActorRotation(newRotation);
}


