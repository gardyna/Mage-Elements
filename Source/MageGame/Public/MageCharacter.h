// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GameplayEffectTypes.h"
#include "MageCharacter.generated.h"

class UAbilitySystemComponent;
class UMageAttributeSet;
class UGameplayEffect;
class UGameplayAbility;

UCLASS()
class MAGEGAME_API AMageCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMageCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UMageAttributeSet> AttributeSet;
	
	/** Instant effects applied once at startup to set opening attribue values */
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TSubclassOf<UGameplayEffect> DefaultAttributeEffects;
	
	/** Abilities granted when the character initialises */
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
	void InitAbilitySystem();
	void OnMoveSpeedChanged(const FOnAttributeChangeData& Data);

};
