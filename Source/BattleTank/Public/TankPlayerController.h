// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "UMG.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	bool GetSightRayHitLocation(FVector &outHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector &outLookDirection) const;
	bool GetLookVectorHitLocation(FVector Direction, FHitResult &outHitLocation) const;
	void AimTowardsCrosshair();


protected:
	UPROPERTY(BlueprintReadWrite)
	UWidget* PlayerUI = nullptr;

private:
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;
	
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;
};
