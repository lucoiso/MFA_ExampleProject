// Author: Lucas Vilas-Boas
// Year: 2022
// Repo: https://github.com/lucoiso/MFA_ExampleProject

#pragma once

#include <CoreMinimal.h>
#include <AttributeSet.h>
#include <AbilitySystemComponent.h>
#include "MFA_AttributeSet.generated.h"

// A helper macro defined on line 414 of AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class MFA_EXAMPLEPROJECT_API UMFA_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	// Constructor: Sets default values for this controller's properties
	UMFA_AttributeSet();

	// Implements the attribute property
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Stamina;

	// Implements the attribute accessors using the helper macro defined on line 414 of AttributeSet.h
	// and line 13 of this file
	ATTRIBUTE_ACCESSORS(UMFA_AttributeSet, Stamina)

private:
	// Called before the attribute is modified: will use it to clamp the stamina attribute in a range [0, 100]
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
};
