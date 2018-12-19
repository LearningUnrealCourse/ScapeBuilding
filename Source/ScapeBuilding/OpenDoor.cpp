// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	OpenDoor(0);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
	if (PressurePlate && PressurePlate->IsOverlappingActor(Opener)) {
		OpenDoor(DeltaTime);
	}
	else {
		OpenDoor(-DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float DeltaTime) {
	AActor* owner = GetOwner();
	FRotator currentRotation = owner->GetActorRotation();

	if ((currentRotation.Yaw >= OpenAngle && DeltaTime > 0) || (currentRotation.Yaw <= 90 && DeltaTime < 0)) {
		UE_LOG(LogTemp, Warning, TEXT("Current Rotation: %f"), currentRotation.Yaw);
		currentRotation.Yaw -= DeltaTime*100;
		owner->SetActorRotation(currentRotation);
	}
}

