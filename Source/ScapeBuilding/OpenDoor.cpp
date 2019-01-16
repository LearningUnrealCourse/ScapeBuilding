// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

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

	if (!Opener)
	{
		Opener = GetWorld()->GetFirstPlayerController()->GetPawn();
	}
	UE_LOG(LogTemp, Warning, TEXT("Opener: %s"), *Opener->GetName());

	RotateDoor(0);
	UE_LOG(LogTemp, Warning, TEXT("Begin Play!"));

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
	if (PressurePlate && PressurePlate->IsOverlappingActor(Opener)) {
		RotateDoor(DeltaTime);
	}
	else {
		RotateDoor(-DeltaTime);
	}
}

void UOpenDoor::RotateDoor(float DeltaTime) {
	AActor* owner = GetOwner();
	FRotator currentRotation = owner->GetActorRotation();

	if ((currentRotation.Yaw >= OpenAngle && DeltaTime > 0) || (currentRotation.Yaw <= 90 && DeltaTime < 0)) {
		currentRotation.Yaw -= DeltaTime*100;
		owner->SetActorRotation(currentRotation);
	}
}

