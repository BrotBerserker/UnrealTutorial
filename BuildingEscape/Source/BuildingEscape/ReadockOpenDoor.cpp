// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "ReadockOpenDoor.h"


float startRoation;
float doorMovementAngle = 0;
int doorMovementDirection = 1;
bool movingDoor = false;
float doorLastOpenTime = 0;

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

	if (ManualTrigger) {
		OpenDoor();
		ManualTrigger = false;
	}

	if (TriggerSensor != NULL && ActorThatOpens != NULL
		&& TriggerSensor->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();
	}

	if (!movingDoor && GetWorld()->GetTimeSeconds()-doorLastOpenTime >= CloseDoorDelay) {
		CloseDoor();
	}

	if(movingDoor)
		MoveDoor();
}

void UReadockOpenDoor::OpenDoor() {
	doorMovementAngle = RotationAngle;
	doorMovementDirection = -1;
	movingDoor = true;
}

void UReadockOpenDoor::CloseDoor() {
	doorMovementAngle = 0;
	doorMovementDirection = -1;
	movingDoor = true;
}


void UReadockOpenDoor::MoveDoor() {
	auto transform = GetOwner()->GetTransform();
	bool lastStep = IsBetween(FRotator(GetOwner()->GetTransform().GetRotation()).Yaw, 
							  startRoation + doorMovementAngle+ RotationSpeed + 0.1, 
							  startRoation + doorMovementAngle - RotationSpeed - 0.1);
	if (lastStep) {
		movingDoor = false;
		doorLastOpenTime = GetWorld()->GetTimeSeconds();
		return;
	}
	auto newRotation = FRotator(transform.GetRotation()) + FRotator(0, doorMovementDirection * RotationSpeed, 0);
	//newRotation.Yaw = lastStep ? startRoation + RotationAngle : newRotation.Yaw;
	GetOwner()->SetActorRotation(newRotation);
}


