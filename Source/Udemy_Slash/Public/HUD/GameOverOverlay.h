// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/SlashUserWidget.h"
#include "GameOverOverlay.generated.h"

/**
 * 
 */
UCLASS()
class UDEMY_SLASH_API UGameOverOverlay : public USlashUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> GameOverAnimation;
		

};
