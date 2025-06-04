// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ButtonBase.h"
#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"


void UButtonBase::SetText(const FText& Text) const
{
	TXT_ButtonText->SetText(Text);
}

void UButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();
	BOX_Root->SetHeightOverride(BoxHeight);
	BOX_Root->SetWidthOverride(BoxWidth);
	
}

void UButtonBase::NativeConstruct()
{
	Super::NativeConstruct();
	BTN_Button->OnClicked.AddDynamic(this, &UButtonBase::OnClicked);
}

void UButtonBase::NativeDestruct()
{
	Super::NativeDestruct();
	BTN_Button->OnClicked.RemoveAll(this);
}


void UButtonBase::OnClicked()
{
	OnButtonClicked.Broadcast(WeaponInfo);
}





