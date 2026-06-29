// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LOLHeroCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "AIController.h"
#include "AbilitySystem/LOLAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/LOLAttributeSet.h"


// Sets default values
ALOLHeroCharacter::ALOLHeroCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AAIController::StaticClass();
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	MovementComponent->bOrientRotationToMovement = true;
	MovementComponent->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	MovementComponent->MaxWalkSpeed = 325.0f;
	MovementComponent->bConstrainToPlane = true;
	MovementComponent->bSnapToPlaneAtStart = true;
	
	AbilitySystemComponent = CreateDefaultSubobject<ULOLAbilitySystemComponent>(TEXT("ASC"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<ULOLAttributeSet>(FName("AttributeSet"));
}

UAbilitySystemComponent* ALOLHeroCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ALOLHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilitySystem();
}

// Called when the game starts or when spawned
void ALOLHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAbilitySystem();
}

void ALOLHeroCharacter::InitAbilitySystem()
{
	if (bAbilitySystemInitialized || !AbilitySystemComponent || !AttributeSet) return;
	bAbilitySystemInitialized = true;
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSet->GetMovementSpeedAttribute())
		.AddUObject(this, &ALOLHeroCharacter::OnMovementSpeedChanged);
	
	if (HasAuthority()) InitDefaultAttributes();
}

void ALOLHeroCharacter::InitDefaultAttributes()
{
	if (!DefaultAttributesEffect) return;
	FGameplayEffectContextHandle Ctx = AbilitySystemComponent->MakeEffectContext();
	Ctx.AddSourceObject(this);
	const FGameplayEffectSpecHandle Spec = 
		AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributesEffect, 1.f, Ctx);
	
	if (Spec.IsValid())
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
}

void ALOLHeroCharacter::OnMovementSpeedChanged(const FOnAttributeChangeData& Data)
{
	GetCharacterMovement()->MaxWalkSpeed = Data.NewValue;
}

// Called every frame
void ALOLHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALOLHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ALOLHeroCharacter::IssueMoveOrder(const FVector& TargetLocation)
{
	if (AController* HeroController = GetController())
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(HeroController, TargetLocation);
	}
}
