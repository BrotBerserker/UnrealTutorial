// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "SigisGrabber.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API USigisGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USigisGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	
private: 

	struct ViewPoint {
		FVector pos;
		FRotator rot;
		FVector targetpos;

		ViewPoint(FVector spos, FRotator srot, FVector stargetpos);
	};

	float reach = 150.f;

	void InitializeShit();

	void Grab();
	void Release();

	UPhysicsHandleComponent* physicsHandle = nullptr;
	UInputComponent* pawnInput = nullptr;

	UPrimitiveComponent* grabbableComponent = nullptr;
	UPrimitiveComponent* findGrabbableComponent();

	ViewPoint getViewPoint();
};
