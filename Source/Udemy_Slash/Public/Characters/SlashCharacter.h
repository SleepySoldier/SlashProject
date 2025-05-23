#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InputActionValue.h"
#include "CharacterTypes.h"
#include "Interfaces/PickupInterface.h"
#include "SlashCharacter.generated.h"

class USlashOverlay;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class AItem;
class UAnimMontage;
class ATreasure;
class ASoul;
class AHealthPickup;



UCLASS()
class UDEMY_SLASH_API ASlashCharacter : public ABaseCharacter, public  IPickupInterface
{
	GENERATED_BODY()

public:
	ASlashCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;
	
	virtual void SetOverlappingItem(AItem* Item) override;
	virtual void AddSouls(ASoul* Soul) override;

	virtual void AddGold(ATreasure* Gold) override;

	virtual void PickupHeal(AHealthPickup* HealthRestored) override;
	//GetEnum
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }

	FORCEINLINE EActionState GetActionState() const { return ActionState; }

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
    
    virtual void EquipWeapon(UStaticMesh* NewWeaponMesh) override;




protected:
	virtual void BeginPlay() override;

	void CheckTraceTypeQuery();

	void SetHUDHealth() const;

	virtual void Death_Implementation() override;

	/* input actions */
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> InputMappingContext;
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> AttackAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> DodgeAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> SheathAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> LockOnAction;
	
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MenuAction;

	/* input actions */
	UFUNCTION(BlueprintCallable)
	void AttachWeaponToBack();

	UFUNCTION(BlueprintCallable)
	void AttachWeaponToHand();

	UFUNCTION(BlueprintCallable)
	void FinishEquipping();
	UFUNCTION(BlueprintCallable)
	void HitReactEnd();

	/** * Callback for input */
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void Interact();
	virtual void Attack() override;
	void Dodge();
	bool hasEnoughStamina();
	bool isOccupied();
	void Sheath();
	void OpenMenu();

	void LockOnActive();

	/** * Combat */
	void EquipWeapon(AWeapon* Weapon);
	virtual void AttackEnd() override;

	virtual void DodgeEnd() override;
	virtual bool CanAttack() override;
	void PlayEquipMontage(const FName& SectionName);
	bool CanDisarm();
	bool CanArm();

	void Disarm();
	void Arm();

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USlashOverlay> SlashOverlay;
	
	UPROPERTY()
	TObjectPtr<AActor> LockOnTarget;

	UPROPERTY()
	FTimerHandle LockOnTimerHandle;

	void LockOn();
	void LockOnSphereTrace();
	void ClearLockOnTimer();

	UPROPERTY()
	TObjectPtr<AActor> InteractTarget;
	

	
private:

	bool isUnoccupied();

	void InitializePlayer();

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_Unoccupied;

	UPROPERTY(EditAnywhere, Category = Outfit)
	TObjectPtr<USkeletalMeshComponent> Hair;

	UPROPERTY(VisibleInstanceOnly)
	TObjectPtr<AItem> OverlappingItem;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	TObjectPtr<UAnimMontage> EquipMontage;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	float LockOnDistance = 300.f;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	float LockOnRadius = 400.f;


};
