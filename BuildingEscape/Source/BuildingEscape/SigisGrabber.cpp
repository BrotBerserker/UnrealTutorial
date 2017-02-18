// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "SigisGrabber.h"


// Sets default values for this component's properties
USigisGrabber::USigisGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USigisGrabber::BeginPlay()
{
	Super::BeginPlay();

	InitializeShit();
}

void USigisGrabber::InitializeShit()
{
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!physicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("No physics handler found on actor: %s"), *GetOwner()->GetName());
	}

	pawnInput = GetOwner()->FindComponentByClass<UInputComponent>();

	if (!pawnInput) {
		UE_LOG(LogTemp, Error, TEXT("No input component found on actor: %s"), *GetOwner()->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Input component: %s"), *pawnInput->GetName());
		pawnInput->BindAction("Grab", IE_Pressed, this, &USigisGrabber::Grab);
	}
}

void USigisGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("GRAB DAT SHIT BRO"));
}


// Called every frame
void USigisGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	FVector pos;
	FRotator rot;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(pos, rot);

	FVector lineEnd = pos + rot.Vector() * reach;
	FColor color;

	FHitResult hitResult;
	bool hit = GetWorld()->LineTraceSingleByObjectType(hitResult, pos, lineEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), FCollisionQueryParams(FName(TEXT("")), false, GetOwner()));
	if (hit) {
		FString name = hitResult.GetActor()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Es wurde gehittet: %s"), *name);
		color = FColorList::Blue;
	} else {
		color = FColorList::Yellow;
	}

	DrawDebugLine(GetWorld(), pos, lineEnd, color, false, 0, 0, 20);
	
	//UE_LOG(LogTemp, Warning, TEXT("View point: Pos: %s, Rot: %s"), *pos.ToString(), *rot.ToString());
}
