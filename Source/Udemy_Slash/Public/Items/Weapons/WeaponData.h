// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponData.generated.h"

/**
 * 
 */
UCLASS()
class UDEMY_SLASH_API UWeaponData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMesh> WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BaseAttackPower;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString SocketEnd;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString SocketTip;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D> WeaponImage;
};
