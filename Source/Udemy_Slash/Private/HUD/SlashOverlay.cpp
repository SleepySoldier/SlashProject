// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SlashOverlay.h"
#include "Characters/SlashCharacter.h"
#include "Components/Button.h"
#include "Components/InventoryComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "HUD/ButtonWidget_Editor.h"
#include "HUD/GameOverOverlay.h"
#include "HUD/InventoryWidget.h"
#include "Items/Weapons/WeaponData.h"
#include "Kismet/GameplayStatics.h"


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

void USlashOverlay::OpenMenu(TObjectPtr<ASlashCharacter> Player)
{
	PlayerRef = Player;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OpenMenuOverlay Called"));
	W_Inventory->BTN_Close->BTN_Button->OnClicked.AddDynamic(this, &USlashOverlay::OnClosePressed);
	TArray WeaponArray = PlayerRef->Inventory->WeaponDA;
	for (const auto Weapon : WeaponArray)
	{
		SelectedWeapon = Weapon->WeaponMesh;
		UButtonBase* Button = CreateWidget<UButtonBase>(this, ItemButton);
		
		ItemButtons.Add(Button);
		//TODO: Replace Text with button image
		Button->SetText(Weapon->WeaponName);
		if (GridCol == 5)
		{
			GridRow ++;
			GridCol = 0;
			W_Inventory->GRID_ItemSlot->AddChildToUniformGrid(Button, GridRow, GridCol);
			GridCol ++;
		}
		else
		{
			W_Inventory->GRID_ItemSlot->AddChildToUniformGrid(Button, GridRow, GridCol);
			GridCol++;
			Button->BTN_Button->OnClicked.AddDynamic(this, &USlashOverlay::OnWeaponSelected);
		}
	}
	W_Inventory->SetVisibility(ESlateVisibility::Visible);
}

void USlashOverlay::InitializeInventory()
{
}

void USlashOverlay::AddItemToInventory()
{
}

void USlashOverlay::OnClosePressed()
{
	W_Inventory->SetVisibility(ESlateVisibility::Hidden);
	GridCol = 0;
	GridRow = 0;
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	PC->SetInputMode(FInputModeGameOnly());
	PC->SetShowMouseCursor(false);
	W_Inventory->BTN_Close->BTN_Button->OnClicked.RemoveDynamic(this, &USlashOverlay::OnClosePressed);
	for (auto Button : ItemButtons)
	{
		Button->BTN_Button->OnClicked.RemoveDynamic(this, &USlashOverlay::OnWeaponSelected);
	}
}

void USlashOverlay::OnWeaponSelected()
{
	PlayerRef->EquipWeapon(SelectedWeapon);
}




