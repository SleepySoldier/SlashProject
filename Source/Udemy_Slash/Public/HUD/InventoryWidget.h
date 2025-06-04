// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/SlashUserWidget.h"
#include "InventoryWidget.generated.h"

class UWeaponData;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnWeaponSelectedSignature, UWeaponData*);

class UUniformGridPanel;
class UButtonWidget_Editor;
/**
 * 
 */
UCLASS()
class UDEMY_SLASH_API UInventoryWidget : public USlashUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButtonWidget_Editor> BTN_Close;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWrapBox> BOX_Weapons;

	virtual void RefreshInventory(TArray<UWeaponData*> Weapons);
	UPROPERTY()
	TArray<class UButtonBase*> WeaponButtonsArray;
	
	FOnWeaponSelectedSignature OnWeaponSelected;
private:
	UFUNCTION()
	void CloseButtonClicked();
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UButtonBase> ItemButton;
	
	
};
