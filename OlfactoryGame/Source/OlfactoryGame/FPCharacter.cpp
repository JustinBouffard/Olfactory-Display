#include "FPCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"

// Sets default values
AFPCharacter::AFPCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetCapsuleComponent());
	Camera->SetRelativeLocation(FVector(0.f, 0.f, 64.f));
	Camera->bUsePawnControlRotation = true;

	bUseControllerRotationYaw = true;

	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->JumpZVelocity = 500.f;
}

// Called when the game starts or when spawned
void AFPCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(GetController())) 
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer())) 
		{
			Subsystem->AddMappingContext(DefaultContext, 0);
		}
	}
}

// Called to bind functionality to input
void AFPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPCharacter::Move);
		EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPCharacter::Look);
		EIC->BindAction(JumpAction, ETriggerEvent::Started, this, &AFPCharacter::Jump);
		EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &AFPCharacter::StopJumping);
	}
}

void AFPCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D Axis = Value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), Axis.Y);
	AddMovementInput(GetActorRightVector(), Axis.X);
}

void AFPCharacter::Look(const FInputActionValue& Value) 
{
	const FVector2D Axis = Value.Get<FVector2D>();
	AddControllerYawInput(Axis.X);
	AddControllerPitchInput(-Axis.Y);
}

