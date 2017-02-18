// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ReadocksGrabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UReadocksGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UReadocksGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;

	

	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPrimitiveComponent* GetGrabbableComponent();

private:
	//struct Asdf {
	//	int A;
	//	int B;
	//};

	float reach = 100.f;
	
	FVector currentPos;
	FRotator currentRot;	

	UPhysicsHandleComponent* physicsHandle = nullptr;
	UInputComponent* pawnInput = nullptr;

	void FindAndInitComponents();
	void Grab();
	void Release();

	//Asdf Test();
};
