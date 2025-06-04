// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/AttackTraceState.h"
#include "Interfaces/HitInterface.h"
#include "Kismet/GameplayStatics.h"

void UAttackTraceState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	HitActors.Empty();
}

void UAttackTraceState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	USceneComponent* WeaponComponent = MeshComp->GetChildComponent(0);
	const FVector TraceStart = WeaponComponent->GetSocketLocation(SocketStart);
	const FVector TraceEnd = WeaponComponent->GetSocketLocation(SocketEnd);

	TArray<FHitResult> OutHits;
	for (FHitResult Hit : OutHits)
	{
		if (UKismetSystemLibrary::DoesImplementInterface(Hit.GetActor(), UHitInterface::StaticClass()))
		{
			HitActors.Add(Hit.GetActor());
			return;
		}
	}
	TArray<AActor*> IgnoreActors;
	UKismetSystemLibrary::SphereTraceMulti(MeshComp, TraceStart, TraceEnd, WeaponTraceRadius,
		ETraceTypeQuery::TraceTypeQuery3, false, IgnoreActors,
		EDrawDebugTrace::None, OutHits, true);
	
}

void UAttackTraceState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	USceneComponent* WeaponComponent = MeshComp->GetChildComponent(0);
	const FVector TraceEnd = WeaponComponent->GetSocketLocation(SocketEnd);
	for (auto HitActor : HitActors)
	{
		IHitInterface::Execute_GetHit(HitActor, TraceEnd, MeshComp->GetOwner());
	}
}
