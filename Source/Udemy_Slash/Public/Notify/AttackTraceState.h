// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AttackTraceState.generated.h"

/**
 * 
 */
UCLASS()
class UDEMY_SLASH_API UAttackTraceState : public UAnimNotifyState
{
	GENERATED_BODY()
private:

	void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
	UPROPERTY()
	TArray<AActor*> HitActors;

	UPROPERTY(EditDefaultsOnly)
	FName SocketStart;
	UPROPERTY(EditDefaultsOnly)
	FName SocketEnd;
	UPROPERTY(EditDefaultsOnly)
	float WeaponTraceRadius = 10.f;
};
