// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ButtonWidget_Editor.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"



void UButtonWidget_Editor::NativePreConstruct()
{
	Super::NativePreConstruct();
	TXT_ButtonText->SetText(ButtonText);
	BOX_Root->SetHeightOverride(BoxHeight);
	BOX_Root->SetWidthOverride(BoxWidth);
}
