// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	auto PlayerTank = GetPlayerTank();

	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController possesses %s"), *ControlledTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController has no tank"));
	}

	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController against %s"), *PlayerTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController has no reference to player tank"));
	}

}

void ATankAIController::Tick(float DeltaTime) {
	if (GetControlledTank() && GetPlayerTank()) {
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
	auto* TankPC = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());

	if (TankPC) {
		return TankPC->GetControlledTank();
	}

	return nullptr;
}
