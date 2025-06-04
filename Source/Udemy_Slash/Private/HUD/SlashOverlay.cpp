// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SlashOverlay.h"
#include "Characters/SlashCharacter.h"
#include "Components/InventoryComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "HUD/GameOverOverlay.h"
#include "HUD/InventoryWidget.h"
#include "Items/Weapons/WeaponData.h"


void USlashOverlay::SetHealthBarPercent(float Percent)
{
	if (BAR_Health)
	{
		BAR_Health->SetPercent(Percent);
	}
}

void USlashOverlay::SetStaminaBarPercent(float Percent)
{
	if (BAR_Stamina)
	{
		BAR_Stamina->SetPercent(Percent);
	}
}

void USlashOverlay::SetGold(int32 Gold)
{
	if (TXT_Gold)
	{
		const FText GoldText = FText::FromString(FString::Printf(TEXT("%d"), Gold));
		TXT_Gold->SetText(GoldText);
	}
}

void USlashOverlay::SetSouls(int32 Souls)
{
	if (TXT_Souls)
	{
		const FText SoulsText = FText::FromString(FString::Printf(TEXT("%d"), Souls));
		TXT_Souls->SetText(SoulsText);
	}
}

void USlashOverlay::PlayDeathAnimation()
{
	GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Red, TEXT("DeathAnimationOverlay Called"));
	
	
	if (W_Died)
	{
		W_Died->SetVisibility(ESlateVisibility::Visible);
		W_Died->PlayAnimationForward(W_Died->GameOverAnimation);
	}
	
}

void USlashOverlay::OpenMenu(ASlashCharacter* Player)
{
	PlayerRef = Player;
	TArray WeaponArray = PlayerRef->Inventory->WeaponsArray;
	W_Inventory->RefreshInventory(WeaponArray);
	
	for (const auto Weapon : WeaponArray)
	{
		SelectedWeapon = (Weapon->WeaponMesh);
		W_Inventory->OnWeaponSelected.AddLambda([this, Player](UWeaponData*){Player->EquipWeapon(SelectedWeapon);});
	}
	
	W_Inventory->SetVisibility(ESlateVisibility::Visible);
}






