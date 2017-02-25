// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "SigiOpenDoor.h"


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

	if (!ensure(PressurePlate != nullptr)) {
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("ALARM!"));
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}


// Called every frame
void USigiOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (isOpenDoorTriggered()) {
		state = DoorState::OPENING;
	}

	if (isCloseDoorTriggered()) {
		state = DoorState::CLOSING;
	}

	if (state == DoorState::OPENING) {
		OpenDoor();
	}

	if (state == DoorState::CLOSING) {
		CloseDoor();
	}
}

bool USigiOpenDoor::isCloseDoorTriggered()
{
	if (state != DoorState::OPEN) {
		return false;
	}
	if (isTriggerTriggered()) {
		return false;
	}
	return LastDoorOpenTime + DoorCloseDelay <= GetWorld()->GetTimeSeconds();
}

bool USigiOpenDoor::isOpenDoorTriggered()
{
	if (state != DoorState::CLOSED) {
		return false;
	}
	if (PressurePlate == NULL) {
		return false;
	}
	return isTriggerTriggered();
}

bool USigiOpenDoor::isTriggerTriggered()
{
	return GetTotalMassOfActorsOnPlate() > TriggerMass;
}

void USigiOpenDoor::OpenDoor()
{
	//FRotator rot = FRotator(GetOwner()->GetTransform().GetRotation());
	//float angle = rot.GetDenormalized().Yaw;

	//float angleDiff = angle - openAngle;
	//if (angleDiff >= 0 && angleDiff <= FMath::Abs(openSpeed)) {
	//	state = DoorState::OPEN;
	//	LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	//	return;
	//}

	//rot += FRotator(0, openSpeed, 0);

	//GetOwner()->SetActorRotation(rot);

	OnOpenRequest.Broadcast();
	state = DoorState::OPEN;
	LastDoorOpenTime = GetWorld()->GetTimeSeconds();

}

void USigiOpenDoor::CloseDoor()
{
	//FRotator rot = FRotator(GetOwner()->GetTransform().GetRotation());
	//float angle = rot.GetDenormalized().Yaw;

	//float angleDiff = angle - closedAngle;
	//if (angleDiff >= 0 && angleDiff <= FMath::Abs(openSpeed)) {
	//	state = DoorState::CLOSED;
	//	return;
	//}

	//rot += FRotator(0, -openSpeed, 0);

	//GetOwner()->SetActorRotation(rot);
	OnCloseRequest.Broadcast();
	state = DoorState::CLOSED;
}

float USigiOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float totalMass = 0.f;

	TArray<AActor*> actors;
	PressurePlate->GetOverlappingActors(actors);

	for (const auto& actor : actors) {
		totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		//UE_LOG(LogTemp, Warning, TEXT("Mass: %s"), *actor->GetName())
	}

	//UE_LOG(LogTemp, Warning, TEXT("Mass: %f"), totalMass)

	return totalMass;
}


