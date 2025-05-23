// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


class UWeaponData;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDEMY_SLASH_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();
	UPROPERTY()
	TArray<TObjectPtr<UWeaponData>> WeaponDA;

	UFUNCTION()
	virtual void AddWeaponToInventory(UWeaponData* NewWeapon);

		
};
