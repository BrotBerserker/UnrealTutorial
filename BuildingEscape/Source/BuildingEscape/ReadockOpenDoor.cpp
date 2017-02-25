// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "ReadockOpenDoor.h"

#define OUT


// Sets default values for this component's properties
UReadockOpenDoor::UReadockOpenDoor() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UReadockOpenDoor::BeginPlay() {
	Super::BeginPlay();

	auto transform = GetOwner()->GetTransform();
	startRoation = transform.GetRotation().Y;
	//ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

}


static bool IsBetween(float value, float a, float b) {
	return (value >= a && value <= b) || (value <= a && value >= b);
}

// Called every frame
void UReadockOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ManualTrigger) {
		OpenDoor();
		ManualTrigger = false;
	}

	if (TriggerSensor != NULL && GetToralMassOfActorsOnPLate() > MinTriggerMass/*&& ActorThatOpens != NULL
		&& TriggerSensor->IsOverlappingActor(ActorThatOpens)*/) {
		OpenDoor();
	}

	if (!movingDoor && GetWorld()->GetTimeSeconds() - doorLastOpenTime >= CloseDoorDelay) {
		CloseDoor();
	}

	if (movingDoor)
		CheckDoorPosition();
}

void UReadockOpenDoor::OpenDoor() {
	OnOpenRequest.Broadcast();
	doorMovementAngle = RotationAngle;
	doorMovementDirection = 1;
	movingDoor = true;
}

void UReadockOpenDoor::CloseDoor() {
	OnOpenRequest.Broadcast();
	OnInverseRequest.Broadcast();
	doorMovementAngle = 0;
	doorMovementDirection = -1;
	movingDoor = true;
}


float UReadockOpenDoor::GetToralMassOfActorsOnPLate() {
	float totalMass = 0.f;
	TArray<AActor*> ouverlappingActors;
	TriggerSensor->GetOverlappingActors(OUT ouverlappingActors);

	for (const auto& actor : ouverlappingActors) {
		//UE_LOG(LogTemp, Warning, TEXT("ActorFound: %s"), *actor->GetName());
		totalMass += actor->FindComponentByClass<UStaticMeshComponent>()->GetMass();
	}

	UE_LOG(LogTemp, Warning, TEXT("TotalMass: %f"), totalMass);
	return totalMass;
}

void UReadockOpenDoor::CheckDoorPosition() {
	auto transform = GetOwner()->GetTransform();
	bool lastStep = IsBetween(FRotator(GetOwner()->GetTransform().GetRotation()).Yaw,
							  startRoation + doorMovementAngle + RotationSpeed + 0.1,
							  startRoation + doorMovementAngle - RotationSpeed - 0.1);
	if (lastStep) {
		movingDoor = false;
		if (GetWorld()->GetTimeSeconds() - doorLastOpenTime>1)
			OnDoorCLosed.Broadcast();
		doorLastOpenTime = GetWorld()->GetTimeSeconds();
		return;
	}
	//auto newRotation = FRotator(transform.GetRotation()) + FRotator(0, doorMovementDirection * RotationSpeed, 0);
	//GetOwner()->SetActorRotation(newRotation);
}


