// Author: Lucas Vilas-Boas
// Year: 2022
// Repo: https://github.com/lucoiso/MFA_ExampleProject

#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Character.h>
#include <AbilitySystemInterface.h>
#include <InputActionValue.h>
#include "MFA_Character.generated.h"

class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UAbilitySystemComponent;

UCLASS()
class MFA_EXAMPLEPROJECT_API AMFA_Character : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called on server when the player is possessed by a controller
	virtual void PossessedBy(AController* InController) override;

	// Called on client when the player state is initialized
	virtual void OnRep_PlayerState() override;

public:
	// Constructor: Sets default values for this character's properties
	AMFA_Character();

protected:
	// Called when the components is about to start being initialized
	virtual void PreInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the game ends or the character dies
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	TWeakObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

#pragma region Default Movimentation Functions
	UFUNCTION()
		void ChangeCameraAxis(const FInputActionValue& Value);
	UFUNCTION()
		void Move(const FInputActionValue& Value);
	UFUNCTION()
		void PerformJump(const FInputActionValue& Value);
#pragma endregion Default Movimentation Functions

public:
	/* Returns character associated Ability System Component */
	UFUNCTION(BlueprintPure)
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
