// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/SlashUserWidget.h"
#include "SlashOverlay.generated.h"

class UButtonBase;
class UInventoryWidget;
class ASlashCharacter;
class UProgressBar;
class UTextBlock;
class UWidgetAnimation;
class UGameOverOverlay;

/**
 * 
 */



UCLASS()
class UDEMY_SLASH_API USlashOverlay : public USlashUserWidget
{
	GENERATED_BODY()
	


public: 

	void SetHealthBarPercent(float Percent);

	void SetStaminaBarPercent(float Percent);

	void SetGold(int32 Gold);

	void SetSouls(int32 Souls);

	virtual void PlayDeathAnimation();
	
	void OpenMenu(TObjectPtr<ASlashCharacter> Player);

	void InitializeInventory();

	void AddItemToInventory();
	
protected:
	UFUNCTION()
	void OnClosePressed();
	UFUNCTION()
	void OnWeaponSelected();

	UPROPERTY()
	TObjectPtr<ASlashCharacter> PlayerRef;
	UPROPERTY()
	TObjectPtr<UStaticMesh> SelectedWeapon;
private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> BAR_Health;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> BAR_Stamina;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TXT_Souls;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TXT_Gold;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UGameOverOverlay> W_Died;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInventoryWidget> W_Inventory;

	int32 GridRow;
	int32 GridCol;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UButtonBase> ItemButton;
	UPROPERTY()
	TArray<UButtonBase*> ItemButtons;



	



};
