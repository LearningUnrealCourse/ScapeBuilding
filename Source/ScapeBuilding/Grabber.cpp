// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Controller.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	GetPhysicsHandle();
	BindInputComponent();
}

void UGrabber::GetPhysicsHandle() 
{
	// Look for attached Physics Handle
	PhysicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandler) {
		UE_LOG(LogTemp, Error, TEXT("%s needs a PhysicsHandle added as a component"), *GetOwner()->GetName());
	}
}

void UGrabber::BindInputComponent() 
{
	//Look for Input Component added at runtime
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("%s, InputComponent has been added at runtime"), *GetOwner()->GetName());
		///Bind the input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s, InputComponent has not been added at runtime"), *GetOwner()->GetName());
	}
}

void UGrabber::Grab() {
	//Check if hitting some PhysicsBody
	FHitResult Hit = GetLineTracingCollision();

	if (Hit.GetActor() != NULL) {
		UE_LOG(LogTemp, Warning, TEXT("Hitting: %s"), *Hit.GetActor()->GetName());
	}
}

FHitResult UGrabber::GetLineTracingCollision()
{
	//Getting Player Viewpoint Location and Rotation
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->
		GetFirstPlayerController()->
		GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	//Calculating Line End using player rotation and reach
	FVector LineEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector()*Reach;

	//Line tracing (Ray casting)
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerViewPointLocation,
		LineEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);

	return Hit;
}

void UGrabber::Release() 
{
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

