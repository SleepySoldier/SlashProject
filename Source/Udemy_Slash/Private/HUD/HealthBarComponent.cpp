// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/HealthBarComponent.h"
#include "HUD/HealthBar.h"
#include "Components/ProgressBar.h"


void UHealthBarComponent::SetHealthPercent(float Percent)
{
	if (HealthBarWidget == nullptr)
	{
		HealthBarWidget = Cast<UHealthBar>(GetUserWidgetObject());
	}
	if (HealthBarWidget && HealthBarWidget->BAR_Health)
	{
		HealthBarWidget->BAR_Health->SetPercent(Percent);
	}
}

UHealthBarComponent::UHealthBarComponent()
{
	UHealthBarComponent::bDrawAtDesiredSize = true;
}



