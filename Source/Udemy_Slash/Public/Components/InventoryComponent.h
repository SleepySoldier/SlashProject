// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


USTRUCT(BlueprintType)
struct FItemInfoStruct
{
	GENERATED_BODY()

	UPROPERTY()
	bool bT0Inventory = false;
	UPROPERTY()
	bool bIsStackable = false;
	UPROPERTY()
	bool bIsHealingItem = false;
	UPROPERTY()
	double ItemHealAmount;
	UPROPERTY()
	FText ItemName;
	UPROPERTY()
	FText ItemDescription;
	UPROPERTY()
	int32 ItemAmount;
	UPROPERTY()
	TObjectPtr<UStaticMesh> ItemMesh;
	UPROPERTY()
	TObjectPtr<UTexture2D> ItemImage;
	UPROPERTY()
	int32 MaxStackSize;
	
};

class UWeaponData;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
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
	
	TArray<FItemInfo> Items;

private:
	int32 InventorySize = 30;
};
