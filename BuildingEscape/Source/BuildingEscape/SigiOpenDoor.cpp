// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "SigiOpenDoor.h"

bool openingDoor = false;

// Sets default values for this component's properties
USigiOpenDoor::USigiOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USigiOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}


// Called every frame
void USigiOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (isDoorTriggered()) {
		openingDoor = true;
	}

	if (openingDoor) {
		OpenDoor();
	}
}

bool USigiOpenDoor::isDoorTriggered()
{
	if (PressurePlate == NULL) {
		return false;
	}
	if (ActorThatOpens == NULL) {
		return false;
	}
	return PressurePlate->IsOverlappingActor(ActorThatOpens);
}

void USigiOpenDoor::OpenDoor()
{
	FRotator rot = FRotator(GetOwner()->GetTransform().GetRotation());
	float angle = rot.GetDenormalized().Yaw;

	float angleDiff = angle - maxAngle;
	if (angleDiff >= 0 && angleDiff <= FMath::Abs(openSpeed)) {
		openingDoor = false;
		return;
	}

	rot += FRotator(0, openSpeed, 0);

	GetOwner()->SetActorRotation(rot);
}

