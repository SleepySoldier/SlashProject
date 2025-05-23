// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class UDEMY_SLASH_API AHealthPickup : public AItem
{
	GENERATED_BODY()
	

public:

	FORCEINLINE float GetHealhAmountRestored() const { return HealthRestored; }

	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;


private:

	UPROPERTY(EditAnywhere, Category = "Pickup Properties")
	float HealthRestored = 25.f;

};
