// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "SigisPositionReport.h"



// Sets default values for this component's properties
USigisPositionReport::USigisPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USigisPositionReport::BeginPlay()
{
	Super::BeginPlay();

	FString name = GetOwner()->GetName();

	FString transform = GetOwner()->GetTransform().ToString();

	UE_LOG(LogTemp, Warning, TEXT("Dies das %s"), *name);
	
}


// Called every frame
void USigisPositionReport::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	UE_LOG(LogTemp, Warning, TEXT("Updating location"));

	FVector oldLocation = GetOwner()->GetTransform().GetLocation();

	FVector newLocation = oldLocation + FVector(1, 0, 0);

	GetOwner()->SetActorLocation(newLocation);

}

