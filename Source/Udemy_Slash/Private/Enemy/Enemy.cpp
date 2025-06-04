// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Enemy.h"
#include "Components/AttributeComponent.h"
#include "HUD/HealthBarComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "Items/Weapons/Weapon.h"
#include "Items/Soul.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	/* AI Perception, TODO: Component */
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 3000.f;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	AIPerception->ConfigureSense(*SightConfig);
	AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());

	HealthBarWidget = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(GetRootComponent());
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->MaxWalkSpeed = PatrolWalkSpeed;

}


void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitializeEnemy();
	Tags.Add(FName("Enemy"));
	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this,&AEnemy::OnPerception);
	
}

void AEnemy::InitializeEnemy()
{
	Tags.Add(FName("EngagableTarget"));
	EnemyController = Cast<AAIController>(GetController());
	HideHealthBar();
	MoveToTarget(PatrolTarget);
}


void AEnemy::Death_Implementation()
{
	Super::Death_Implementation();
	EnemyState = EEnemyState::EES_Dead;
	ClearAttackTimer();
	ClearPatrolTimer();
	HideHealthBar();
	SetLifeSpan(DeathLifeSpan);
	SpawnSoul();

}

void AEnemy::SpawnSoul()
{
	UWorld* World = GetWorld();
	if (World && SoulClass && Attributes)
	{
		ASoul* SpawnedSoul = World->SpawnActor<ASoul>(SoulClass, GetActorLocation(), GetActorRotation());
		if (SpawnedSoul) SpawnedSoul->SetSouls(Attributes->GetSouls());		
	}
}

bool AEnemy::InTargetRange(AActor* Target, double Radius)
{
	if (Target == nullptr) return false;
	const double DistanceToTarget = (Target->GetActorLocation() - GetActorLocation()).Size();
	return DistanceToTarget <= Radius;
}

void AEnemy::MoveToTarget(AActor* Target)
{
	if (EnemyController == nullptr || Target == nullptr) return;
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(Target);
	MoveRequest.SetAcceptanceRadius(AIMoveToRadius);
	EnemyController->MoveTo(MoveRequest);	
}

AActor* AEnemy::ChoosePatrolTarget()
{
	TArray<AActor*> ValidTargets;
	for (AActor* Target : PatrolTargets)
	{
		if (Target != PatrolTarget)
		{
			ValidTargets.AddUnique(Target);
		}
	}
	const int32 NumOfPatrolTargets = ValidTargets.Num();
	if (NumOfPatrolTargets > 0)
	{
		const int32 TargetSelection = FMath::RandRange(0, NumOfPatrolTargets - 1);
		return ValidTargets[TargetSelection];
	}
	return nullptr;
}

//Timer Function
void AEnemy::PatrolTimerFinshed()
{
	MoveToTarget(PatrolTarget);
}

void AEnemy::HideHealthBar()
{
	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(false);
	}
}

void AEnemy::ShowHealthBar()
{
	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(true);
	}
}

void AEnemy::LoseInterest()
{
	CombatTarget = nullptr;
	HideHealthBar();
}

void AEnemy::StartPatrolling()
{
	EnemyState = EEnemyState::EES_Patrolling;
	GetCharacterMovement()->MaxWalkSpeed = PatrolWalkSpeed;
	MoveToTarget(PatrolTarget);
}

void AEnemy::ChaseTarget()
{
	EnemyState = EEnemyState::EES_Chasing;
	GetCharacterMovement()->MaxWalkSpeed = ChaseWalkSpeed;
	MoveToTarget(CombatTarget);
}

bool AEnemy::isOutsideCombatRadius()
{
	return !InTargetRange(CombatTarget, CombatRadius);
}

bool AEnemy::isOutsideAttackRadius()
{
	return !InTargetRange(CombatTarget, AttackRadius);
}

bool AEnemy::isInsideAttackRadius()
{
	return InTargetRange(CombatTarget, AttackRadius);
}

bool AEnemy::isChasing()
{
	return EnemyState == EEnemyState::EES_Chasing;
}

bool AEnemy::isAttacking()
{
	return EnemyState == EEnemyState::EES_Attacking;
}

bool AEnemy::isDead()
{
	return EnemyState == EEnemyState::EES_Dead;
}

bool AEnemy::isEngaged()
{
	return EnemyState == EEnemyState::EES_Enagaged;
}

bool AEnemy::CanAttack()
{
	bool bCanAttack = 
		isInsideAttackRadius() && 
		!isAttacking() && 
		!isEngaged() &&
		!isDead();
	return bCanAttack;
}

void AEnemy::HandleDamage(float DamageAmount)
{
	Super::HandleDamage(DamageAmount);
	if (HealthBarWidget)
	{
		HealthBarWidget->SetHealthPercent(Attributes->GetHealthPercent());
	}
}

int32 AEnemy::PlayDeathMontage()
{
	const int32 Selection = Super::PlayDeathMontage();
	TEnumAsByte<EDeathPose> Pose(Selection);
	if (Pose < EDeathPose::EDP_Max)
	{
		DeathPose = Pose;
	}
	return Selection;

}

void AEnemy::AttackEnd()
{
	EnemyState = EEnemyState::EES_None;
	CheckCombatTarget();
}


void AEnemy::ClearPatrolTimer()
{
	GetWorldTimerManager().ClearTimer(PatrolTimer);
}

void AEnemy::StartAttackTimer()
{
	EnemyState = EEnemyState::EES_Attacking;
	const float AttackTime = FMath::RandRange(attackMin, attackMax);
	GetWorldTimerManager().SetTimer(AttackTimer, this, &AEnemy::Attack, AttackTime);
}
void AEnemy::ClearAttackTimer()
{
	GetWorldTimerManager().ClearTimer(AttackTimer);
}
void AEnemy::CheckPatrolTarget()
{
	if (InTargetRange(PatrolTarget, PatrolRadius))
	{
		PatrolTarget = ChoosePatrolTarget();
		const float WaitTime = FMath::FRandRange(PatrolWaitMin, PatrolWaitMax);
		GetWorldTimerManager().SetTimer(PatrolTimer, this, &AEnemy::PatrolTimerFinshed, WaitTime);
	}
}

void AEnemy::CheckCombatTarget()
{
	if (isOutsideCombatRadius())
	{
		ClearAttackTimer();
		LoseInterest();
		if (!isEngaged()) StartPatrolling();
	}

	else if (isOutsideAttackRadius() && !isChasing())
	{
		ClearAttackTimer();
		if (!isEngaged()) ChaseTarget();
	}
	else if (CanAttack())
	{
		ClearAttackTimer();
		StartAttackTimer();
	}
}

void AEnemy::OnPerception(AActor* Actor, FAIStimulus Stimulus)
{
	bool bHasBeenSensed = Stimulus.WasSuccessfullySensed();
	if (bHasBeenSensed && Actor->ActorHasTag(FName("Player")))
	{
		const bool bShouldChaseTarget = 
       	EnemyState != EEnemyState::EES_Dead &&
       	EnemyState != EEnemyState::EES_Chasing &&
       	EnemyState < EEnemyState::EES_Attacking &&
       	Actor->ActorHasTag(FName("EngagableTarget"));
       
       	if (bShouldChaseTarget)
       	{
       		CombatTarget = Actor;
       		ClearPatrolTimer();
       		ChaseTarget();
       	}
	}

}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isDead()) return;
	if (EnemyState > EEnemyState::EES_Patrolling)
	{
		CheckCombatTarget();
	}
	else
	{
		CheckPatrolTarget();
	}
}


void AEnemy::Attack()
{
	Super::Attack();
	if (CombatTarget == nullptr) return;
	EnemyState = EEnemyState::EES_Enagaged;
	PlayAttackMontage();
}


float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, TEXT("DamageRecieved"));
	HealthBarWidget->SetHealthPercent(Attributes->GetHealthPercent());
	ClearPatrolTimer();
	ClearAttackTimer();
	CombatTarget = EventInstigator->GetPawn();
	
	if (!isDead())
	{
		ShowHealthBar();
		EnemyState = EEnemyState::EES_Patrolling;
		CheckCombatTarget();
	}
	else
	{
		Death();
	}

	return DamageAmount;
}

void AEnemy::Destroyed()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->Destroy();
	}
}




