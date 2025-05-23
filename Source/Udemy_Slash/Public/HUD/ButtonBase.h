// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/SlashUserWidget.h"
#include "ButtonBase.generated.h"

class UButton;
class USizeBox;
class UTextBlock;
/**
 * 
 */
UCLASS()
class UDEMY_SLASH_API UButtonBase : public USlashUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	FText ButtonText;
	UPROPERTY(EditAnywhere)
	double BoxWidth = 80.f;
	UPROPERTY(EditAnywhere)
	double BoxHeight = 80.f;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> BOX_Root;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BTN_Button;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TXT_ButtonText;

	void SetText(const FText& Text);

protected:

	virtual void NativePreConstruct() override;
};
