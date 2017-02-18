// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "ReadocksGrabber.h"


#define OUT

// Sets default values for this component's properties
UReadocksGrabber::UReadocksGrabber() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UReadocksGrabber::BeginPlay() {
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));

	FindComponents();

}

void UReadocksGrabber::FindComponents() {
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	pawnInput = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!physicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("No UPhysicsHandleComponent found on %s!"), *GetOwner()->GetName());
	}
	if (!pawnInput) {
		UE_LOG(LogTemp, Error, TEXT("No UInputComponent found on %s!"), *GetOwner()->GetName());
		/// Bind input
	} else {
		pawnInput->BindAction("Grab", IE_Pressed, this, &UReadocksGrabber::Grab);
	}
}

void UReadocksGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
}

// Called every frame
void UReadocksGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// Get player view point this tick
	FVector pos;
	FRotator rot;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT pos, OUT rot);
	//UE_LOG(LogTemp, Warning, TEXT("Vect: %s \n Rot: %s"), *pos.ToString(), *rot.ToString());

	auto lineTrace = pos + rot.Vector() * reach;

	/// Ray-cast
	FHitResult hitResult;
	bool hit = GetWorld()->LineTraceSingleByObjectType(
		OUT hitResult,
		pos,
		lineTrace,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner()));
	if (hit) {
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *hitResult.GetActor()->GetName());
		DrawDebugLine(GetWorld(), pos, lineTrace, FColorList::Red, false, 0, 0, 5);
	} else {
		DrawDebugLine(GetWorld(), pos, lineTrace, FColorList::Orange, false, 0, 0, 5);
	}
	//
}

