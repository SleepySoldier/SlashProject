// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDEMY_SLASH_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributeComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void RegenStamina(float DeltaTime);
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float Health = 100.f;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float Stamina = 100.f;

	bool canRestoreHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float MaxStamina = 100.f;


	UPROPERTY(EditAnywhere, Category = "ActorAttributes")
	int32 Gold;

	UPROPERTY(EditAnywhere, Category = "ActorAttributes")
	int32 Souls;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float DodgeCost = 15.f;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float StaminaRegenRate = 3.f;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	int32 CharacterLevel = 1;
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	double BaseAttack;
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	double BaseDefense;

	

public:	
	void RecieveDamage(float Damage);
	void UseStamina(float StaminaCost);
	float GetHealthPercent();
	float GetStaminaPercent();
	bool isAlive();
	void AddSouls(int32 NumberOfSouls);
	void AddGold(int32 AmountOfGold);

	void AddHealth(float AmountOfHealth);
	FORCEINLINE int32 GetGold() const { return Gold; }

	FORCEINLINE int32 GetSouls() const { return Souls; }
		
	FORCEINLINE float GetDodgeCost() const { return DodgeCost; }
	FORCEINLINE float GetStamina() const { return Stamina; }

	FORCEINLINE float GetHealhAmountRestored() const { return Health; }



};
