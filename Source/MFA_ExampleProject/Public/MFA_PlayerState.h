// Author: Lucas Vilas-Boas
// Year: 2022
// Repo: https://github.com/lucoiso/MFA_ExampleProject

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "MFA_PlayerState.generated.h"

class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class MFA_EXAMPLEPROJECT_API AMFA_PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AMFA_PlayerState();

	/* Returns associated Ability System Component */
	UFUNCTION(BlueprintPure, Category = "Project Elementus | Functions")
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	/* Player associated Ability System Component */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Project Elementus | Properties",
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
};
