
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class USphereComponent;
class UNiagaraSystem;

enum class EItemState : uint8
{
	EIS_Hovering,
	EIS_Equipped
};

UCLASS()
class UDEMY_SLASH_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	

	AItem();
	virtual void Tick(float DeltaTime) override;
protected:

	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float Amplitude = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float TimeConstant = 5.f;

	UFUNCTION(BlueprintPure)
	float TransformedSin();

	UFUNCTION(BlueprintPure)
	float TransformedCos();

	//function tempalte, can use any input supported by the code you want to use, ie. if math, inputs must support math. similar to function library.
	template<typename T>
	T Avg(T First, T Second);

	//Use ShpereOverlap form PrimitveComponents.h and put into a usable function 
	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* ItemMesh;

	EItemState ItemState = EItemState::EIS_Hovering;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, Category = "Effects")
	class UNiagaraComponent* ParticleEffect;

	virtual void SpawnPickupParticle();

	virtual void SpawnPickupSound();


	UPROPERTY(EditAnywhere, Category = "Custom")
	UNiagaraSystem* PickupEffect;
	UPROPERTY(EditAnywhere, Category = "Custom")
	USoundBase* PickupSound;



private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))//expose RunningTime to event graph as a private variable.
	float RunningTime;



};

//template functions use 
template<typename T>
inline T AItem::Avg(T First, T Second)
{
	return (First + Second) / 2;
}
