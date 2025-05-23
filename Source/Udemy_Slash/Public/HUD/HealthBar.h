// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/SlashUserWidget.h"
#include "HealthBar.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class UDEMY_SLASH_API UHealthBar : public USlashUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> BAR_Health;

};
