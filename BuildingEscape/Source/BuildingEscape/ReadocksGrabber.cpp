// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "ReadocksGrabber.h"


#define OUT


// Sets default values for this component's properties
UReadocksGrabber::UReadocksGrabber() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UReadocksGrabber::BeginPlay() {
	Super::BeginPlay();	
	FindAndInitComponents();
	//UGameplayStatics::SetGamePaused(GetWorld(), true);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ERROR!"));	
}

void UReadocksGrabber::FindAndInitComponents() {
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	pawnInput = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!physicsHandle) {
		UE_LOG(LogTemp, Fatal, TEXT("No UPhysicsHandleComponent found on %s!"), *GetOwner()->GetName());
	}
	if (!pawnInput) {
		UE_LOG(LogTemp, Fatal, TEXT("No UInputComponent found on %s!"), *GetOwner()->GetName());
	} else {
		/// Bind input
		pawnInput->BindAction("Grab", IE_Pressed, this, &UReadocksGrabber::Grab);
		pawnInput->BindAction("Grab", IE_Released, this, &UReadocksGrabber::Release);
	}
}

void UReadocksGrabber::Grab() {
	auto component = GetGrabbableComponent();
	if (component) {
		physicsHandle->GrabComponentAtLocationWithRotation(component, NAME_None, component->GetOwner()->GetActorLocation(), component->GetOwner()->GetActorRotation());		
	}
}

void UReadocksGrabber::Release() {
	physicsHandle->ReleaseComponent();
}


//UReadocksGrabber::Asdf UReadocksGrabber::Test() { Asdf b;  return b; }

void UReadocksGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// update current position and rotation
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT currentPos, OUT currentRot);

	auto lineTrace = currentPos + currentRot.Vector() * reach;
	if(physicsHandle->GrabbedComponent)
		physicsHandle->SetTargetLocation(lineTrace);
	
}

UPrimitiveComponent* UReadocksGrabber::GetGrabbableComponent() {
	auto lineTrace = currentPos + currentRot.Vector() * reach;

	/// Ray-cast
	FHitResult hitResult;
	bool hit = GetWorld()->LineTraceSingleByObjectType(
		OUT hitResult,
		currentPos,
		lineTrace,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner()));
	if (hit) {
		//UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *hitResult.GetActor()->GetName());
		DrawDebugLine(GetWorld(), currentPos, lineTrace, FColorList::Red, false, 0, 0, 5);
	}
	DrawDebugLine(GetWorld(), currentPos, lineTrace, FColorList::Orange, false, 0, 0, 5);
	return hitResult.GetComponent();
}


