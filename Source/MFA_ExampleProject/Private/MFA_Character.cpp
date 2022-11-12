// Author: Lucas Vilas-Boas
// Year: 2022
// Repo: https://github.com/lucoiso/MFA_ExampleProject

#include "MFA_Character.h"
#include "MFA_PlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/GameFrameworkComponentManager.h"
#include "AbilitySystemComponent.h"
#include "InputAction.h"

// Default variable used on camera rotation
constexpr float BaseTurnRate = 45.f;
// Default variable used on camera rotation
constexpr float BaseLookUpRate = 45.f;

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
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, UGameFrameworkComponentManager::NAME_GameActorReady);
}

// Called when the game ends or the character dies
void AMFA_Character::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver(this);
	Super::EndPlay(EndPlayReason);
}

void AMFA_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
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

			UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, UGameFrameworkComponentManager::NAME_GameActorReady);
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

		UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, UGameFrameworkComponentManager::NAME_GameActorReady);
	}
}

// Returns character associated Ability System Component
UAbilitySystemComponent* AMFA_Character::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

#pragma region Default Movimentation Functions
// Function to manage camera rotation via mouse movement
void AMFA_Character::ChangeCameraAxis(const FInputActionValue& Value)
{
	GetController<APlayerController>()->AddYawInput(-1.f * Value[1] * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	GetController<APlayerController>()->AddPitchInput(Value[0] * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

// Function to manage Walk related inputs: W, A, S and D
void AMFA_Character::Move(const FInputActionValue& Value)
{
	if (Value.GetMagnitude() != 0.0f && !IsMoveInputIgnored())
	{
		const FRotator YawRotation(0, GetControlRotation().Yaw, 0);

		const FVector DirectionX = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector DirectionY = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(DirectionX, Value[1]);
		AddMovementInput(DirectionY, Value[0]);
	}
}

// There's a modular ability to manage the character's jump,
// this function is a "normal" jump function that can be used if jump isn't a ability
void AMFA_Character::PerformJump(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT(" %s called with Input Action Value %s (magnitude %f)"), *FString(__func__), *Value.ToString(), Value.GetMagnitude());

	Value.Get<bool>() ? Jump() : StopJumping();
}
#pragma endregion Default Movimentation Functions
