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
	Player->Inventory->AddWeaponToInventory(WeaponsArray[0]);
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Interacting with player");
	Destroy();
}





