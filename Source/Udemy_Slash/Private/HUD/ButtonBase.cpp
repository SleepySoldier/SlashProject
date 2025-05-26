// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ButtonBase.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"

void UButtonBase::SetText(const FText& Text)
{
	TXT_ButtonText->SetText(Text);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Text: %s"), Text));
	
}

void UButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();
	BOX_Root->SetHeightOverride(BoxHeight);
	BOX_Root->SetWidthOverride(BoxWidth);
	
}



