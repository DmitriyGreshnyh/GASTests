// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/Characters/SCharacterBase.h"
#include "GameplayAbilitySystem/AttributesSets/SBasicAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SAbilitySystemComponent.h"
#include "../../Engine/Classes/GameFramework/Character.h"
#include "../../Engine/Classes/GameFramework/Actor.h"
#include "SCombatAttributeSet.h"
#include "Abilities/SGameplayAbility.h"

// Sets default values
ASCharacterBase::ASCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Add ability system component
	AbilitySystemComponent = CreateDefaultSubobject<USAbilitySystemComponent>(TEXT("ASbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(ASCReplicationMode);

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(35.0f, 90.0f);

	// Don't rotate when controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.f;

	// Add the basic attribute set
	BasicAttributeSet = CreateDefaultSubobject<USBasicAttributeSet>(TEXT("BasicAttributeSet"));

	// Add Combat attribute set
	CombatAttributeSet = CreateDefaultSubobject<USCombatAttributeSet>(TEXT("CombatAttributeSet"));
}

// Called when the game starts or when spawned
void ASCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	// Subscribe on State.Death tag added to character
	AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag("State.Death")).AddUObject(this, &ASCharacterBase::OnDeadTagChanged);
}

void ASCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		GrantAbilities(StartingAbilities);
	}
}

void ASCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void ASCharacterBase::OnDeadTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		HandleDeath();
	}
}

void ASCharacterBase::HandleDeath_Implementation()
{
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->DisableMovement();

	// Impulse
	FVector Impulse = GetActorForwardVector() * -10000;
	Impulse.Z = 15000;
	GetMesh()->AddImpulseAtLocation(Impulse, GetActorLocation());
}

// Called every frame
void ASCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

TArray<FGameplayAbilitySpecHandle> ASCharacterBase::GrantAbilities(TArray<TSubclassOf<UGameplayAbility>> AbilitiesToGrant)
{
	// Only Server must grant Abilities
	if (!AbilitySystemComponent || !HasAuthority()) return TArray<FGameplayAbilitySpecHandle>();

	TArray<FGameplayAbilitySpecHandle> AbilityHandles;

	for (TSubclassOf<UGameplayAbility> Ability : AbilitiesToGrant)
	{

		int32 InputID = -1;
		if (const USGameplayAbility* SAbilityCDO = GetDefault<USGameplayAbility>(Ability)) // Get default values of class CDO - Class default object
		{
			InputID = static_cast<int32>(SAbilityCDO->AbilityInputID);
		}


		FGameplayAbilitySpecHandle SpecHandle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, InputID, this));

		AbilityHandles.Add(SpecHandle);
	}

	SendAbilitiesChangedEvent();

	return AbilityHandles;
}

void ASCharacterBase::RemoveAbilities(TArray<FGameplayAbilitySpecHandle> AbilityHandlesToRemove)
{

	if (!AbilitySystemComponent || !HasAuthority()) return;

	for (FGameplayAbilitySpecHandle AbilityHandle : AbilityHandlesToRemove)
	{
		AbilitySystemComponent->ClearAbility(AbilityHandle);
	}

	SendAbilitiesChangedEvent();
}

void ASCharacterBase::SendAbilitiesChangedEvent()
{
	FGameplayEventData EventData;
	EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Events.Abilities.Changed")); // TODO: Remove hardcoded tag
	EventData.Instigator = this;
	EventData.Target = this;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, EventData.EventTag, EventData);
}

void ASCharacterBase::ServerSendGameplayEventToSelf_Implementation(FGameplayEventData EventData)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, EventData.EventTag, EventData);
}

