// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"
#include "Items/Weapons/WeaponData.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UInventoryComponent::AddWeaponToInventory(UWeaponData* NewWeapon)
{
	WeaponsArray.Add(NewWeapon);
	FString WeaponName = NewWeapon->GetName();
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("WeaponName: %s"), *WeaponName));
}

UStaticMesh* UInventoryComponent::SetInitialWeapon()
{
	return WeaponsArray[0]->WeaponMesh;
}




