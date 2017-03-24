// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesses %s"), *ControlledTank->GetName());
	} else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController has no tank"));
	}
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}


bool ATankPlayerController::GetSightRayHitLocation(FVector &outHitLocation) const {
	if (!PlayerUI) { return false; }

	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairXLocation);
	FVector CameraWorldDirection;
	FHitResult HitLocation;

	if (GetLookDirection(ScreenLocation, CameraWorldDirection)) {
		if (GetLookVectorHitLocation(CameraWorldDirection, HitLocation)) {
			outHitLocation = HitLocation.Location;
			return true;
		}
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &outLookDirection) const {
	FVector CameraWorldLocation;

	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		outLookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector Direction, FHitResult &outHitResult) const {
	FVector Start = PlayerCameraManager->GetCameraLocation();
	FVector End = Start + Direction * LineTraceRange;
	
	return GetWorld()->LineTraceSingleByChannel(
		outHitResult,
		Start,
		End,
		ECollisionChannel::ECC_Visibility,
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner()),
		FCollisionResponseParams()
	);
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) { return; }

	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation)) {
		GetControlledTank()->AimAt(HitLocation);
	}
}
