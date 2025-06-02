// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemBase.h"
#include "NiagaraComponent.h"
#include "Characters/SlashCharacter.h"
#include "Components/InventoryComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	SphereOverlap->SetupAttachment(GetRootComponent());
	
	ItemEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ItemEffect"));
	ItemEffect->SetupAttachment(SphereOverlap);

}

void AItemBase::InteractInput(class ASlashCharacter* Player)
{
	if (WeaponsArray.Num() > 1)
	{
		int32 ItemSelection = FMath::RandRange(0, WeaponsArray.Num() - 1);
		Player->Inventory->AddWeaponToInventory(WeaponsArray[ItemSelection]);
	}
	else
	{
		Player->Inventory->AddWeaponToInventory(WeaponsArray[0]);
	}
	Destroy();
	
}

void AItemBase::OnSeeInteractable(bool bHasSeen)
{
	IPickupInterface::OnSeeInteractable(bHasSeen);
	if (bHasSeen)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You are interacting with this item."));
	}
}






