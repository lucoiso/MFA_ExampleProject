// Author: Lucas Vilas-Boas
// Year: 2022
// Repo: https://github.com/lucoiso/MFA_ExampleProject

#include "MFA_PlayerController.h"
#include "MFA_Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedPlayerInput.h"
#include "InputAction.h"
#include "AbilitySystemComponent.h"
#include "MFEA_Settings.h"

// Constructor: Sets default values for this controller's properties
AMFA_PlayerController::AMFA_PlayerController()
{
	// Enable/Disable Tick()
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Get and store the Blueprint Enumeration with the Ability InputID values
	if (const UMFEA_Settings* MF_Settings = GetDefault<UMFEA_Settings>();
		!MF_Settings->InputIDEnumeration.IsNull())
	{
		InputEnumHandle = MF_Settings->InputIDEnumeration.LoadSynchronous();
	}
}

/* This function came from IAbilityInputBinding interface,
 * provided by GameFeatures_ExtraActions plugin to manage ability bindings */
void AMFA_PlayerController::SetupAbilityBindingByInput_Implementation(UInputAction* Action, const int32 InputID)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
		ensureAlwaysMsgf(IsValid(EnhancedInputComponent), TEXT("%s have a invalid EnhancedInputComponent"), *GetName()))
	{
		// FAbilityInputData is a custom private struct to handle the bindings of the input to the ability
		const FAbilityInputData AbilityBinding
		{
			EnhancedInputComponent->BindAction(Action, ETriggerEvent::Started, this, &AMFA_PlayerController::OnAbilityInputPressed, Action).GetHandle(),
			EnhancedInputComponent->BindAction(Action, ETriggerEvent::Completed, this, &AMFA_PlayerController::OnAbilityInputReleased, Action).GetHandle(),
			static_cast<uint32>(InputID)
		};

		// Store the binding handles in the array of FAbilityInputData
		AbilityActionBindings.Add(Action, AbilityBinding);
	}
}

/* This function came from IAbilityInputBinding interface,
 * provided by GameFeatures_ExtraActions plugin to manage ability bindings */
void AMFA_PlayerController::RemoveAbilityInputBinding_Implementation(const UInputAction* Action)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
		ensureAlwaysMsgf(IsValid(EnhancedInputComponent), TEXT("%s have a invalid EnhancedInputComponent"), *GetName()))
	{
		EnhancedInputComponent->RemoveBindingByHandle(AbilityActionBindings.FindRef(Action).OnPressedHandle);
		EnhancedInputComponent->RemoveBindingByHandle(AbilityActionBindings.FindRef(Action).OnReleasedHandle);
	}
}

// Function to manage the input bindings of the added abilities when a key is pressed
void AMFA_PlayerController::OnAbilityInputPressed(UInputAction* Action) const
{
	if (!IsValid(GetPawn()))
	{
		return;
	}

	const uint32 InputID = AbilityActionBindings.FindRef(Action).InputID;

	// Check if controller owner is valid and owns a ability system component
	if (const AMFA_Character* ControllerOwner = GetPawn<AMFA_Character>();
		ensureAlwaysMsgf(IsValid(ControllerOwner->GetAbilitySystemComponent()),
		                 TEXT("%s owner have a invalid AbilitySystemComponent"), *GetName()))
	{
		// Send the input pressed event to the ability system component with the found input ID
		ControllerOwner->GetAbilitySystemComponent()->AbilityLocalInputPressed(InputID);

		// Verify if the found input ID is equal to Confirm or Cancel input from the specified Enumeration class
		if (ensureAlwaysMsgf(InputEnumHandle.IsValid(), TEXT("%s have a invalid InputEnumHandle"), *GetName()))
		{
			if (InputID == InputEnumHandle->GetValueByName("Confirm", EGetByNameFlags::CheckAuthoredName))
			{
				ControllerOwner->GetAbilitySystemComponent()->LocalInputConfirm();
			}

			else if (InputID == InputEnumHandle->GetValueByName("Cancel", EGetByNameFlags::CheckAuthoredName))
			{
				ControllerOwner->GetAbilitySystemComponent()->LocalInputCancel();
			}
		}
	}
}

// Function to manage the input bindings of the added abilities when a key is released
void AMFA_PlayerController::OnAbilityInputReleased(UInputAction* Action) const
{
	if (!IsValid(GetPawn()))
	{
		return;
	}

	const uint32 InputID = AbilityActionBindings.FindRef(Action).InputID;

	// Check if controller owner is valid and owns a ability system component
	if (const AMFA_Character* ControllerOwner = GetPawn<AMFA_Character>();
		ensureAlwaysMsgf(IsValid(ControllerOwner->GetAbilitySystemComponent()),
		                 TEXT("%s owner have a invalid AbilitySystemComponent"), *GetName()))
	{
		// Send the input released event to the ability system component with the found input ID
		ControllerOwner->GetAbilitySystemComponent()->AbilityLocalInputReleased(InputID);
	}
}