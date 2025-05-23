// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Characters/CharacterTypes.h"
#include "Enemy.generated.h"


class UHealthBarComponent;
class UAISenseConfig_Sight;
class UAIPerceptionComponent;

UCLASS()
class UDEMY_SLASH_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemy();
	virtual void Tick(float DeltaTime) override; 
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override; 
	virtual void Destroyed() override;

protected:
	virtual void BeginPlay() override;

	/**
	*Play Montage Functions
	*/
	virtual void Death_Implementation() override;

	void SpawnSoul();

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EDeathPose> DeathPose;
	UPROPERTY(BlueprintReadOnly)
	EEnemyState EnemyState = EEnemyState::EES_Patrolling;
	bool InTargetRange(AActor* Target, double Radius);
	void MoveToTarget(AActor* Target);
	AActor* ChoosePatrolTarget();
	
	UFUNCTION()
	void OnPerception(AActor* Actor, FAIStimulus Stimulus);
	
	virtual void Attack() override;
	virtual bool CanAttack() override;

	virtual void HandleDamage(float DamageAmount) override;

	virtual int32 PlayDeathMontage() override;
	virtual void AttackEnd() override;


private:

	/* Components */	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UHealthBarComponent> HealthBarWidget;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAIPerceptionComponent> AIPerception;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAISenseConfig_Sight> SightConfig;
	

	/* Components */

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AWeapon> WeaponClass;


	/* Navigation */



	UPROPERTY(EditAnywhere, Category = "AI_Navigation")
	float PatrolWaitMin = 5.f;

	UPROPERTY(EditAnywhere, Category = "AI_Navigation")
	float PatrolWaitMax = 10.f;
	UPROPERTY()
	class AAIController* EnemyController;
	UPROPERTY(EditInstanceOnly, Category = "AI_Navigation")
	TObjectPtr<AActor> PatrolTarget;
	UPROPERTY(EditInstanceOnly, Category = "AI_Navigation")
	TArray<AActor*> PatrolTargets;

	UPROPERTY(EditAnywhere, Category = "AI_Navigation")
	float ChaseWalkSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = "AI_Navigation")
	float PatrolWalkSpeed = 150.f;
	void PatrolTimerFinshed();

	UPROPERTY(EditAnywhere)
	double CombatRadius = 900.f;

	UPROPERTY(EditAnywhere)
	double PatrolRadius = 300.f;

	UPROPERTY(EditAnywhere)
	double AttackRadius = 150.f;

	UPROPERTY(EditAnywhere)
	double AIMoveToRadius = 120.f;
	/** AI Behavior */
	
	void HideHealthBar();
	void ShowHealthBar();
	void LoseInterest();
	void StartPatrolling();
	void ChaseTarget();

	bool isOutsideCombatRadius();
	bool isOutsideAttackRadius();
	bool isInsideAttackRadius();
	bool isChasing();
	bool isAttacking();
	bool isDead();
	bool isEngaged();
	void ClearPatrolTimer();
	void CheckPatrolTarget();
	void CheckCombatTarget();

	/** AI Behavior */
	void StartAttackTimer();
	void ClearAttackTimer();

	FTimerHandle AttackTimer;
	FTimerHandle PatrolTimer;


	void SpawnDefaultWeapon();
	void InitializeEnemy();

	UPROPERTY(EditAnywhere, Category = "Combat")
	float attackMin = .5f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float attackMax = 1.f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float DeathLifeSpan = 6.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class ASoul> SoulClass;

};
