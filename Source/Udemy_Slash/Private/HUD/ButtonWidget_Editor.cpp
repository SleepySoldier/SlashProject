// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ButtonWidget_Editor.h"
#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"



void UButtonWidget_Editor::NativePreConstruct()
{
	Super::NativePreConstruct();
	TXT_ButtonText->SetText(ButtonText);
	BOX_Root->SetHeightOverride(BoxHeight);
	BOX_Root->SetWidthOverride(BoxWidth);
}

void UButtonWidget_Editor::NativeConstruct()
{
	Super::NativeConstruct();
	BTN_Button->OnClicked.AddDynamic(this, &UButtonWidget_Editor::OnClicked);
}

void UButtonWidget_Editor::NativeDestruct()
{
	Super::NativeDestruct();
	BTN_Button->OnClicked.RemoveAll(this);
}

void UButtonWidget_Editor::OnClicked()
{
	OnButtonClicked.Broadcast();
}