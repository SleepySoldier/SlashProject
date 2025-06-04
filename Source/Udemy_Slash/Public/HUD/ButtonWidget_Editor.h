// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ButtonBase.h"
#include "ButtonWidget_Editor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClicked);
/**
 * 
 */
UCLASS()
class UDEMY_SLASH_API UButtonWidget_Editor : public USlashUserWidget
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

	UPROPERTY()
	FOnButtonClicked OnButtonClicked;
	UFUNCTION()
	void OnClicked();


protected:
	
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;




};
