// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LOLHeroCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "AIController.h"


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
}

// Called when the game starts or when spawned
void ALOLHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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