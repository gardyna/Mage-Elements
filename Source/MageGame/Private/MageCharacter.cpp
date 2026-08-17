#include "MageCharacter.h"

#include "AbilitySystemComponent.h"
#include "MageAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMageCharacter::AMageCharacter()
{
 	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UMageAttributeSet>(TEXT("Attributes"));

}

UAbilitySystemComponent* AMageCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void AMageCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAbilitySystem();
}

void AMageCharacter::InitAbilitySystem()
{
	if (!AbilitySystemComponent || !AttributeSet)
	{
		return;
	}
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	if (DefaultAttributeEffects)
	{
		FGameplayEffectContextHandle Context = AbilitySystemComponent->MakeEffectContext();
		Context.AddSourceObject(this);
		
		const FGameplayEffectSpecHandle Spec = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffects, 1.0f, Context);

		if (Spec.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
		}
	}
	
	for (const TSubclassOf<UGameplayAbility>& Ability : StartupAbilities)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, this));
	}
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		UMageAttributeSet::GetMoveSpeedAttribute())
	.AddUObject(this, &AMageCharacter::OnMoveSpeedChanged);

	if (UCharacterMovementComponent* Movement = GetCharacterMovement())
	{
		Movement->MaxWalkSpeed = AttributeSet->GetMoveSpeed();
	}
}

void AMageCharacter::OnMoveSpeedChanged(const FOnAttributeChangeData& Data)
{
	if (UCharacterMovementComponent* Movement = GetCharacterMovement())
	{
		Movement->MaxWalkSpeed = Data.NewValue;
	}
}
