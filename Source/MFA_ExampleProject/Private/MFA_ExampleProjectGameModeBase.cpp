// Author: Lucas Vilas-Boas
// Year: 2022
// Repo: https://github.com/lucoiso/UEModularFeatures_ExtraActions

#include "MFA_ExampleProjectGameModeBase.h"
#include "MFA_Character.h"
#include "MFA_PlayerController.h"
#include "MFA_PlayerState.h"

// Constructor: Sets default values for this controller's properties
AMFA_ExampleProjectGameModeBase::AMFA_ExampleProjectGameModeBase()
{
	// Set the default classes for this GameModeBase class	
	DefaultPawnClass = AMFA_Character::StaticClass();
	PlayerStateClass = AMFA_PlayerState::StaticClass();
	PlayerControllerClass = AMFA_PlayerController::StaticClass();
}
