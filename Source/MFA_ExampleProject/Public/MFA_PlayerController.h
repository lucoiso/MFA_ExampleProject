// Author: Lucas Vilas-Boas
// Year: 2022
// Repo: https://github.com/lucoiso/MFA_ExampleProject

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AbilityInputBinding.h"
#include "InputActionValue.h"
#include "MFA_PlayerController.generated.h"

class UInputAction;
/**
 * 
 */
UCLASS()
class MFA_EXAMPLEPROJECT_API AMFA_PlayerController : public APlayerController, public IAbilityInputBinding
{
	GENERATED_BODY()

public:
	// Constructor: Sets default values for this controller's properties
	AMFA_PlayerController();

	/* This function came from IAbilityInputBinding interface,
	 * provided by GameFeatures_ExtraActions plugin to manage ability bindings */
	UFUNCTION()
	virtual void SetupAbilityInputBinding_Implementation(UInputAction* Action, const int32 InputID) override;

	/* This function came from IAbilityInputBinding interface,
	 * provided by GameFeatures_ExtraActions plugin to manage ability bindings */
	UFUNCTION()
	virtual void RemoveAbilityInputBinding_Implementation(const UInputAction* Action) const override;

private:
	// FAbilityInputData is a custom private struct to handle the bindings of the input to the ability
	struct FAbilityInputData
	{
		uint32 OnPressedHandle = 0;
		uint32 OnReleasedHandle = 0;
		uint32 InputID = 0;
	};

	// A Ptr to store the Blueprint Enumeration and manage the ability input Ids from C++
	TWeakObjectPtr<UEnum> InputEnumHandle;

	// A map to store the ability input bindings
	TMap<UInputAction*, FAbilityInputData> AbilityActionBindings;

#pragma region Default Movimentation Functions
	UFUNCTION()
	void ChangeCameraAxis(const FInputActionValue& Value);
	UFUNCTION()
	void Move(const FInputActionValue& Value) const;
	UFUNCTION()
	void Jump(const FInputActionValue& Value) const;
#pragma endregion Default Movimentation Functions

	// Function to manage the input bindings of the added abilities when a key is pressed
	void OnAbilityInputPressed(UInputAction* Action) const;

	// Function to manage the input bindings of the added abilities when a key is released
	void OnAbilityInputReleased(UInputAction* Action) const;
};
