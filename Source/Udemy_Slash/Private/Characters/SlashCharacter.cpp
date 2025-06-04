#include "Characters/SlashCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera\CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Items/Item.h"
#include "Items/Weapons/Weapon.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "HUD/SlashHUD.h"
#include "HUD/SlashOverlay.h"
#include "Components/AttributeComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Items/Soul.h"
#include "Items/Treasure.h"
#include "Items/HealthPickup.h"
#include "Kismet/GameplayStatics.h"
#include "Udemy_Slash/Udemy_Slash.h"


// Sets default values
ASlashCharacter::ASlashCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);

	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	InteractionSphere->SetupAttachment(GetMesh());

	Hair = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh(), FName("HairSocket"));
		
    
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}
void ASlashCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitializePlayer();
	//CheckTraceTypeQuery();



}

void ASlashCharacter::CheckTraceTypeQuery()
{
	for (int32 i = 0; i < ETraceTypeQuery::TraceTypeQuery_MAX; ++i)
	{
		ETraceTypeQuery EnumValue = static_cast<ETraceTypeQuery>(i);
		FString EnumName = UEnum::GetValueAsString(EnumValue);
		FString ChannelName = UEnum::GetValueAsString(UEngineTypes::ConvertToCollisionChannel(static_cast<ETraceTypeQuery>(i)));
		UE_LOG(LogTemp, Warning, TEXT("ETraceTypeQuery Name: %s"), *EnumName);
		UE_LOG(LogTemp, Warning, TEXT("Collision Channel Name: %s"), *ChannelName);
	}
	
	for (int32 i = 0; i < EObjectTypeQuery::ObjectTypeQuery_MAX; ++i)
	{
		EObjectTypeQuery EnumValue = static_cast<EObjectTypeQuery>(i);
		FString EnumName = UEnum::GetValueAsString(EnumValue);
		FString ChannelName = UEnum::GetValueAsString(UEngineTypes::ConvertToCollisionChannel(static_cast<EObjectTypeQuery>(i)));
		UE_LOG(LogTemp, Warning, TEXT("EObjectTypeQuery Name: %s"), *EnumName);
		UE_LOG(LogTemp, Warning, TEXT("Collision Channel Name: %s"), *ChannelName);
	}
	
}

void ASlashCharacter::InitializePlayer()
{
	Tags.Add(FName("EngagableTarget"));

	//Add InputmappingContext to Actor.
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
		ASlashHUD* SlashHUD = Cast<ASlashHUD>(PlayerController->GetHUD());
		if (SlashHUD)
		{
			SlashOverlay = SlashHUD->GetSlashOverlay();
			if (SlashOverlay && Attributes)
			{
				SlashOverlay->SetHealthBarPercent(Attributes->GetHealthPercent());
				SlashOverlay->SetStaminaBarPercent(1.f);
				SlashOverlay->SetGold(0);
				SlashOverlay->SetSouls(0);
			}
		}

	}
}

void ASlashCharacter::Death_Implementation()
{
	Super::Death_Implementation();
	ActionState = EActionState::EAS_Dead;
	if (SlashOverlay)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, TEXT("InSlashOverlay") );
		SlashOverlay->PlayDeathAnimation();
	}


}

void ASlashCharacter::AttachWeaponToBack()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("S_WeaponSheath"));
	}
}

void ASlashCharacter::AttachWeaponToHand()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("WeaponSocket"));
	}
}

void ASlashCharacter::FinishEquipping()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void ASlashCharacter::HitReactEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void ASlashCharacter::Move(const FInputActionValue& Value) // WASD
{
	if (ActionState != EActionState::EAS_Unoccupied) return;

	const FVector2D MoveAxis = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	//Forward vector = direction controller is pointing.
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MoveAxis.X);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MoveAxis.Y);

}

void ASlashCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxis = Value.Get<FVector2D>();
	if (GetController())
	{
		AddControllerYawInput(LookAxis.X);
		AddControllerPitchInput(LookAxis.Y);
	}


}

void ASlashCharacter::Interact() // E
{
	if (!InteractActors.IsEmpty())
	{
		Cast<IPickupInterface>(InteractActors.Last())->InteractInput(this);
	}
	
}
//LMB
void ASlashCharacter::Attack() // RMB
{
	Super::Attack();
	if (CanAttack())
	{
		PlayAttackMontage();
		ActionState = EActionState::EAS_Attacking;		
	}

}
 
void ASlashCharacter::DodgeEnd()
{
	Super::DodgeEnd();
	ActionState = EActionState::EAS_Unoccupied;
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Weapon, ECR_Overlap);
	GetMesh()->SetCollisionResponseToChannel(ECC_Weapon, ECR_Overlap);
}

bool ASlashCharacter::CanAttack()
{
	return ActionState == EActionState::EAS_Unoccupied &&
		CharacterState != ECharacterState::ECS_Unequipped;
}


bool ASlashCharacter::CanDisarm()
{
	return ActionState == EActionState::EAS_Unoccupied &&
		CharacterState != ECharacterState::ECS_Unequipped;
}

bool ASlashCharacter::CanArm()
{
	return ActionState == EActionState::EAS_Unoccupied &&
		CharacterState == ECharacterState::ECS_Unequipped &&
		EquippedWeapon;
}

void ASlashCharacter::Disarm()
{
	PlayEquipMontage(FName("Unequip"));
	CharacterState = ECharacterState::ECS_Unequipped;
	ActionState = EActionState::EAS_EqiuppingWeapon;
}

void ASlashCharacter::Arm()
{
	PlayEquipMontage(FName("Equip"));
	CharacterState = ECharacterState::ECS_EquippedOneHanded;
	ActionState = EActionState::EAS_EqiuppingWeapon;
}


void ASlashCharacter::Dodge() // Left CTRL
{
	if (isOccupied() || !hasEnoughStamina()) return;

	Super::PlayDodgeMontage();
	ActionState = EActionState::EAS_Dodge;
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Weapon, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Weapon, ECR_Ignore);
	if (Attributes && SlashOverlay)
	{
		Attributes->UseStamina(Attributes->GetDodgeCost());
		SlashOverlay->SetStaminaBarPercent(Attributes->GetStaminaPercent());
	}

}
bool ASlashCharacter::hasEnoughStamina()
{
	return Attributes && Attributes->GetStamina() > Attributes->GetDodgeCost();
}
bool ASlashCharacter::isOccupied()
{
	return ActionState != EActionState::EAS_Unoccupied;
}
void ASlashCharacter::Sheath() //Z
{
	if (CanDisarm())
	{
		Disarm();
	}
	else if (CanArm())
	{
		Arm();
	}
}

void ASlashCharacter::OpenMenu()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	PC->SetInputMode(FInputModeUIOnly());
	PC->SetShowMouseCursor(true);
	SlashOverlay->OpenMenu(this);
}

void ASlashCharacter::LockOn()
{
	if (LockOnTarget == nullptr)
	{
		LockOnSphereTrace();
	}
	
	else
	{
		LockOnTarget = nullptr;
	}

}

void ASlashCharacter::LockOnSphereTrace()
{
	const FVector TraceStart = GetActorLocation();
	const FVector TraceEnd = (GetActorForwardVector() *= LockOnDistance) + TraceStart;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	TArray<FHitResult> OutHits;
	//Trace channel has to be set to "Block" on target, not overlap
	const bool bHit = UKismetSystemLibrary::SphereTraceMulti(
		this,
		TraceStart, TraceEnd,
		LockOnRadius,
		UEngineTypes::ConvertToTraceType(ECC_MeleeWeapon),
		false, ActorsToIgnore, EDrawDebugTrace::ForDuration,
		OutHits, true);
	if (bHit)
	{
		for (const FHitResult& Array : OutHits)
        	{
				if (UKismetSystemLibrary::DoesImplementInterface(Array.GetActor(), UHitInterface::StaticClass()))
				{
					LockOnTarget = Array.GetActor();
					GetCharacterMovement()->bOrientRotationToMovement = false;
					CameraBoom->SocketOffset.Set(0.f, 10.f, 100.f);
					break;
				}
        	}
		GetWorldTimerManager().SetTimer(LockOnTimerHandle, this, &ASlashCharacter::LockOnActive, .01f, true);
	}
}

void ASlashCharacter::LockOnActive()
{

	if (LockOnTarget)
	{
		FVector SelfLocation = GetActorLocation();
		FVector LookAtTarget = LockOnTarget->GetActorLocation();
		GetController()->SetControlRotation(UKismetMathLibrary::FindLookAtRotation(SelfLocation, LookAtTarget));

		FVector CameraLocation = GetActorLocation();
		FRotator CameraLookAtRotation = UKismetMathLibrary::FindLookAtRotation(CameraLocation, LookAtTarget);
		Camera->SetWorldRotation(CameraLookAtRotation);
	}
	else
	{
		ClearLockOnTimer();
	}
}

void ASlashCharacter::ClearLockOnTimer()
{
	if (LockOnTarget == nullptr)
	{
		LockOnTimerHandle.Invalidate();
		GetCharacterMovement()->bOrientRotationToMovement = true;
		CameraBoom->SocketOffset.Set(0.f, 0.f, 60.f);
		Camera->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	}

}
void ASlashCharacter::PlayEquipMontage(const FName& SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && EquipMontage)
	{
		AnimInstance->Montage_Play(EquipMontage);
		AnimInstance->Montage_JumpToSection(SectionName, EquipMontage);
	}
}

void ASlashCharacter::AttackEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}

// Called to bind functionality to input
void ASlashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Jump);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Interact);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Attack);
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Dodge);
		EnhancedInputComponent->BindAction(SheathAction, ETriggerEvent::Started, this, &ASlashCharacter::Sheath);
		EnhancedInputComponent->BindAction(LockOnAction, ETriggerEvent::Started, this, &ASlashCharacter::LockOn);
		EnhancedInputComponent->BindAction(MenuAction, ETriggerEvent::Started, this, &ASlashCharacter::OpenMenu);
	}
}

void ASlashCharacter::Jump()
{
	if (isUnoccupied())
	{
		Super::Jump();
	}
}

// See interactable icon, get reference.
void ASlashCharacter::OverlapInteractable(AActor* OtherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("StartInteracting."));
	InteractActors.AddUnique(OtherActor);
	Cast<IPickupInterface>(InteractActors.Last())->OnSeeInteractable(true);
}

void ASlashCharacter::StopOverlapInteractable(AActor* OtherActor)
{
	if (InteractActors.Contains(OtherActor))
	{
		Cast<IPickupInterface>(OtherActor)->OnSeeInteractable(false);
		InteractActors.Remove(OtherActor);
	}

}

bool ASlashCharacter::isUnoccupied()
{
	return ActionState == EActionState::EAS_Unoccupied;
}

float ASlashCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if(isAlive()) ActionState = EActionState::EAS_HitReaction;
	
	SetHUDHealth();

	return DamageAmount;
}

void ASlashCharacter::Tick(float DeltaTime)
{
	if (Attributes)
	{
		Attributes->RegenStamina(DeltaTime);
		SlashOverlay->SetStaminaBarPercent(Attributes->GetStaminaPercent());
	}
}

void ASlashCharacter::EquipWeapon(UStaticMesh* NewWeaponMesh)
{
	Super::EquipWeapon(NewWeaponMesh);
	CharacterState = ECharacterState::ECS_EquippedOneHanded;
}

void ASlashCharacter::SetHUDHealth() const
{
	if (SlashOverlay && Attributes) SlashOverlay->SetHealthBarPercent(Attributes->GetHealthPercent());
}


void ASlashCharacter::SetOverlappingItem(AItem* Item)
{
	OverlappingItem = Item;
}

void ASlashCharacter::AddSouls(ASoul* Soul)
{
	if (Attributes && SlashOverlay)
	{
		Attributes->AddSouls(Soul->GetSouls());
		SlashOverlay->SetSouls(Attributes->GetSouls());
	}


}

void ASlashCharacter::AddGold(ATreasure* Gold)
{
	if (Attributes && SlashOverlay)
	{
		Attributes->AddGold(Gold->GetGold());
		SlashOverlay->SetGold(Attributes->GetGold());
	}
}

void ASlashCharacter::PickupHeal(AHealthPickup* HealthRestored)
{
	if (Attributes->canRestoreHealth())
	{
		Attributes->AddHealth(HealthRestored->GetHealhAmountRestored());
		SetHUDHealth();
	}

}




