// Author: Lucas Vilas-Boas
// Year: 2022
// Repo: https://github.com/lucoiso/MFA_ExampleProject

#include "MFA_AttributeSet.h"

// Constructor: Sets default values for this controller's properties
UMFA_AttributeSet::UMFA_AttributeSet() : Stamina(100.f)
{
}

// Called before the attribute is modified: will use it to clamp the stamina attribute in a range [0, 100]
void UMFA_AttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue, 0.f, 100.f);
	}
}
