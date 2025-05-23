// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/PickupInterface.h"
#include "ItemBase.generated.h"

class UWeaponData;
class USphereComponent;
class UNiagaraComponent;

UCLASS()
class UDEMY_SLASH_API AItemBase : public AActor, public IPickupInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();
	
	//UFUNCTION()
	//virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void InteractInput(class ASlashCharacter* Player) override;
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UWeaponData>> WeaponsArray;
protected:

private:
	UPROPERTY(EditAnywhere, Category = "Defaults")
	TObjectPtr<UNiagaraComponent> ItemEffect;
	UPROPERTY(EditAnywhere, Category = "Defaults")
	TObjectPtr<USphereComponent> SphereOverlap;
	


};
