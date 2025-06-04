// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/InventoryWidget.h"
#include "Components/WrapBox.h"
#include "HUD/ButtonBase.h"
#include "HUD/ButtonWidget_Editor.h"
#include "Items/Weapons/WeaponData.h"
#include "Kismet/GameplayStatics.h"

void UInventoryWidget::RefreshInventory(TArray<UWeaponData*> Weapons)
{
	BOX_Weapons->ClearChildren();
	
	for (UWeaponData* WeaponsItem : Weapons)
	{
		UButtonBase* WeaponButton = CreateWidget<UButtonBase>(this, ItemButton);
		WeaponButtonsArray.Add(WeaponButton);
		
		WeaponButton->SetText(WeaponsItem->WeaponName);
		
		BOX_Weapons->AddChild(WeaponButton);
		
		WeaponButton->WeaponInfo = WeaponsItem;
		WeaponButton->OnButtonClicked.AddLambda([this, WeaponButton](UWeaponData*)
		{
			OnWeaponSelected.Broadcast(WeaponButton->WeaponInfo);
			GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, TEXT("Button CLicked"));
		});
	}
	BTN_Close->OnButtonClicked.AddDynamic(this, &UInventoryWidget::CloseButtonClicked);
}


void UInventoryWidget::CloseButtonClicked()
{
	SetVisibility(ESlateVisibility::Hidden);
	BTN_Close->OnButtonClicked.RemoveAll(this);
	for (UButtonBase* WeaponButtons : WeaponButtonsArray)
	{
		WeaponButtons->OnButtonClicked.RemoveAll(this);
	}
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	PC->SetInputMode(FInputModeGameOnly());
	PC->SetShowMouseCursor(false);
	
}
