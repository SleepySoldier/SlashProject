// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/SlashUserWidget.h"
#include "InventoryWidget.generated.h"

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
	TObjectPtr<UUniformGridPanel> GRID_ItemSlot;
};
