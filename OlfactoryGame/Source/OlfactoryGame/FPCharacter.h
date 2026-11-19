#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "FPCharacter.generated.h"

class UCameraComponent;
class UInputAction;
class UInputMappingContext;

UCLASS(Blueprintable)
class OLFACTORYGAME_API AFPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFPCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DefaultContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* JumpAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
};
