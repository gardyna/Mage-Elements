// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MageAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class MAGEGAME_API UMageAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UMageAttributeSet();
	
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	UPROPERTY(BlueprintReadOnly, Category = "Vitals")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UMageAttributeSet, Health)
	
	UPROPERTY(BlueprintReadOnly, Category = "Vitals")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UMageAttributeSet, MaxHealth)
	
	UPROPERTY(BlueprintReadOnly, Category = "Vitals")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UMageAttributeSet, Mana)
	
	UPROPERTY(BlueprintReadOnly, Category = "Vitals")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UMageAttributeSet, MaxMana)
	
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UMageAttributeSet, MoveSpeed)
	
	// transient inbox for damage, never a stored stat
	UPROPERTY(BlueprintReadOnly, Category = "Meta")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UMageAttributeSet, IncomingDamage)
	
};
