// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "SigisGrabber.h"


USigisGrabber::ViewPoint::ViewPoint(FVector spos, FRotator srot, FVector stargetpos) {
	pos = spos;
	rot = srot;
	targetpos = stargetpos;
}


// Sets default values for this component's properties
USigisGrabber::USigisGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USigisGrabber::BeginPlay()
{
	Super::BeginPlay();

	InitializeShit();
}

// Initializes physicsHandler and input component
void USigisGrabber::InitializeShit()
{
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!physicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("No physics handler found on actor: %s"), *GetOwner()->GetName());
	}

	pawnInput = GetOwner()->FindComponentByClass<UInputComponent>();

	if (!pawnInput) {
		UE_LOG(LogTemp, Error, TEXT("No input component found on actor: %s"), *GetOwner()->GetName());
	} else {
		pawnInput->BindAction("Grab", IE_Pressed, this, &USigisGrabber::Grab);
		pawnInput->BindAction("Grab", IE_Released, this, &USigisGrabber::Release);
	}
}

// Grabs the current grabbable component
void USigisGrabber::Grab() {
	if (!grabbableComponent) {
		return;
	}
	physicsHandle->GrabComponentAtLocationWithRotation(grabbableComponent, NAME_None, grabbableComponent->GetOwner()->GetActorLocation(), grabbableComponent->GetOwner()->GetActorRotation());
}

// Releases the currently grabbed component
void USigisGrabber::Release() {
	if(!physicsHandle->GrabbedComponent){
		return;
	}
	physicsHandle->ReleaseComponent();
}


// Called every frame
void USigisGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	
	if (physicsHandle->GrabbedComponent) {
		physicsHandle->SetTargetLocation(getViewPoint().targetpos);
	} else { 
		grabbableComponent = findGrabbableComponent();
	}
}

// Returns the grabbable component that the player is currently looking at, or null
UPrimitiveComponent* USigisGrabber::findGrabbableComponent() {
	ViewPoint vp = getViewPoint();

	FColor color;
	UPrimitiveComponent* grabbable = nullptr;

	FHitResult hitResult;
	bool hit = GetWorld()->LineTraceSingleByObjectType(hitResult, vp.pos, vp.targetpos, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), FCollisionQueryParams(FName(TEXT("")), false, GetOwner()));
	if (hit) {
		grabbable = hitResult.GetComponent();
		// TODO: Display "Press E to grab" in GUI
		//color = FColorList::Blue;
	} else {
		//color = FColorList::Yellow;
	}

	//DrawDebugLine(GetWorld(), vp.pos, vp.targetpos, color, false, 0, 0, 20);
	return grabbable;
}

// Returns the current PlayerViewPoint and the point he is looking at within his grab range
USigisGrabber::ViewPoint USigisGrabber::getViewPoint()
{
	FVector pos;
	FRotator rot;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(pos, rot);

	FVector targetpos = pos + rot.Vector() * reach;
	return ViewPoint(pos, rot, targetpos);
}
