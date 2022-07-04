// Author: Lucas Vilas-Boas
// Year: 2022
// Repo: https://github.com/lucoiso/UEModularFeatures_ExtraActions

#include "MFA_PlayerState.h"
#include "AbilitySystemComponent.h"

// Constructor: Sets default values for this controller's properties
AMFA_PlayerState::AMFA_PlayerState()
{
	// Enable/Disable Tick()
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	// Create the ABSC
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));
}

/* Player associated Ability System Component */
UAbilitySystemComponent* AMFA_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
