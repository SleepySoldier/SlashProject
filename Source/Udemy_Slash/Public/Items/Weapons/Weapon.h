// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Weapon.generated.h"

class USoundBase;
class UBoxComponent;
/**
 * 
 */
UCLASS()
class UDEMY_SLASH_API AWeapon : public AItem
{
	GENERATED_BODY()
public:
	AWeapon();
	void Equip(USceneComponent* InParent, FName InSocketName, AActor* NewOwner, APawn* NewInstigator);

	void DeactivateParticleEffect();

	void DisableSphereCollision();

	void PlayEquipSound();

	void AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName);

	TArray<AActor*> IgnoreActors;


protected:
	virtual void BeginPlay() override;
	//Use ShpereOverlap form Item.h. virtual not required, but override at end is.
	
	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool ActorIsSameType(AActor* OtherActor);

	void ExecuteGetHit(FHitResult& BoxHit, AActor* Hitter);
	
	UFUNCTION(BlueprintImplementableEvent)
	void CreateFields(const FVector& FieldLocation);

private:

	void BoxTrace(FHitResult& BoxHit);

	UPROPERTY(EditAnywhere, Category = "WeaponProperties")
	FVector BoxTraceExtent = FVector(5.5f);
	UPROPERTY(EditAnywhere, Category = "WeaponProperties")
	bool bShowBoxDebug = false;

	UPROPERTY(EditAnywhere, Category = WeaponProperties)
	USoundBase* EquipSound;

	UPROPERTY(VisibleAnywhere, Category = WeaponProperties)
	UBoxComponent* WeaponBox;

	UPROPERTY(EditAnywhere, Category = "WeaponProperties")
	float Damage = 20.f;
	


public:
	FORCEINLINE UBoxComponent* GetWeaponBox() const { return WeaponBox; }
};
