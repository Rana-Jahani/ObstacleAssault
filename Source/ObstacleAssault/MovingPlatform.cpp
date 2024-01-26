// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
	UE_LOG(LogTemp, Display, TEXT("Configured Moved Distance: %f"), MoveDistance);
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	// Move platform forwards	
	// Reverse direction of motion if gone too far
	if (ShouldPlatformReturn())
	{
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = - PlatformVelocity;
	}
	else
	{
		// Get current location
		FVector CurrentLocation = GetActorLocation();
		// Add a vector to that location (a local vector)
		CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
		// Set the location
		SetActorLocation(CurrentLocation);
	}
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > MoveDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(StartLocation, GetActorLocation());
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);

	//Old code:
	//FRotator CurrentRotation = GetActorRotation();
	//CurrentRotation = CurrentRotation + RotationVelocity * DeltaTime;
	//SetActorRotation(CurrentRotation);
}

