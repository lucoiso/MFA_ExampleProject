// Author: Lucas Vilas-Boas
// Year: 2022
// Repo: https://github.com/lucoiso/UEModularFeatures_ExtraActions

#include "MFA_Character.h"
#include "MFA_PlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/GameFrameworkComponentManager.h"
#include "AbilitySystemComponent.h"

// Constructor: Sets default values for this character's properties
AMFA_Character::AMFA_Character()
{
	// Enable/Disable Tick()
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

#pragma region Default ACharacter properties
	GetCapsuleComponent()->InitCapsuleSize(50.f, 50.0f);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 300.f;
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.375f;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	GetCharacterMovement()->GravityScale = 1.25f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = true;
	FollowCamera->SetRelativeLocation(FVector(50.f, 50.f, 50.f));
#pragma endregion Default ACharacter properties
}

// Called when the components is about to start being initialized
void AMFA_Character::PreInitializeComponents()
{
	UGameFrameworkComponentManager::AddGameFrameworkComponentReceiver(this);
	Super::PreInitializeComponents();
}

// Called when the game starts or when spawned
void AMFA_Character::BeginPlay()
{
	Super::BeginPlay();
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(
		this, UGameFrameworkComponentManager::NAME_GameActorReady);
}

// Called when the game ends or the character dies
void AMFA_Character::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver(this);
	Super::EndPlay(EndPlayReason);
}

// Called on server when the player is possessed by a controller
void AMFA_Character::PossessedBy(AController* InController)
{
	Super::PossessedBy(InController);

	// Check if this character is controlled by a player or AI
	if (InController->IsPlayerController())
	{
		// Initialize the ability system component that is stored by Player State
		if (AMFA_PlayerState* State = GetPlayerState<AMFA_PlayerState>())
		{
			AbilitySystemComponent = State->GetAbilitySystemComponent();
			AbilitySystemComponent->InitAbilityActorInfo(State, this);

			UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(
				this, UGameFrameworkComponentManager::NAME_GameActorReady);
		}
	}
	else
	{
		// Bot / AI
		// Initialize the ability system component that is stored by AI Controller

		// Unnecessary in this project
	}
}

// Called on client when the player state is initialized
void AMFA_Character::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Initialize the ability system component that is stored by Player State
	if (AMFA_PlayerState* State = GetPlayerState<AMFA_PlayerState>())
	{
		AbilitySystemComponent = State->GetAbilitySystemComponent();
		AbilitySystemComponent->InitAbilityActorInfo(State, this);

		UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(
			this, UGameFrameworkComponentManager::NAME_GameActorReady);
	}
}

// Returns character associated Ability System Component
UAbilitySystemComponent* AMFA_Character::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}
