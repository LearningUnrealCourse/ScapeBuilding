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

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Getting Player Viewpoint Location and Rotation
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->
		GetFirstPlayerController()->
		GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	//Draw a Green Line
	DrawDebugLine(
		GetWorld(), 
		PlayerViewPointLocation, 
		PlayerViewPointLocation+PlayerViewPointRotation.Vector()*Reach, //Calculating Line End using player rotation and reach
		FColor(0,255,0), 
		false, 
		0.f, 
		0, 
		10.f);

}

