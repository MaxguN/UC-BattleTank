// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


void UTankAimingComponent::AimAt(FVector Target, float LaunchSpeed) {
	if (!Barrel || !Turret) { return; }

	FVector Direction;
	bool success = UGameplayStatics::SuggestProjectileVelocity(
		this,
		Direction,
		Barrel->GetSocketLocation(FName("Projectile")),
		Target,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (success) {
		Direction = Direction.GetSafeNormal();
		MoveBarrelTowards(Direction);
	}
	else {

		UE_LOG(LogTemp, Warning, TEXT("no solution"));
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector Direction) {
	if (!Barrel || !Turret) { return; }

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = Direction.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	//UE_LOG(LogTemp, Warning, TEXT("%f delta rotator %s"), GetWorld()->TimeSeconds, *DeltaRotator.ToString());

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet) {
	Turret = TurretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
