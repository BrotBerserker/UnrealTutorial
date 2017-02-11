// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "PositionReport.h"


// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	auto name = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s says: Banana!"), *name);


	auto transform = GetOwner()->GetTransform();
	UE_LOG(LogTemp, Warning, TEXT("%s Pos: %s"), *name, *transform.ToString());
	UE_LOG(LogTemp, Warning, TEXT("X: %f"), transform.GetLocation().X);
	UE_LOG(LogTemp, Warning, TEXT("Y: %f"), transform.GetLocation().Y);
	UE_LOG(LogTemp, Warning, TEXT("Z: %f"), transform.GetLocation().Z);	
	
}


// Called every frame
void UPositionReport::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );


	auto name = GetOwner()->GetName();
	auto transform = GetOwner()->GetTransform();
	UE_LOG(LogTemp, Warning, TEXT("%s Pos: %s"), *name, *transform.ToString());
	//transform.TransformPosition (transform.GetLocation() + FVector(0,0,10) );
	GetOwner()->SetActorLocation(transform.GetLocation() + FVector(0, 0, 10));
}

