// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LOLGameMode.h"
#include "Camera/LOLTopCameraPawn.h"
#include "Character/LOLHeroCharacter.h"
#include "Player/LOLPlayerController.h"
#include "PlayerState/LOLPlayerState.h"


ALOLGameMode::ALOLGameMode()
{
	DefaultPawnClass = ALOLTopCameraPawn::StaticClass();
	PlayerControllerClass = ALOLPlayerController::StaticClass();
	PlayerStateClass = ALOLPlayerState::StaticClass();
}


void ALOLGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPC)
{
	Super::HandleStartingNewPlayer_Implementation(NewPC);
	
	if (!HeroClass || !NewPC) return;
	
	AActor* Anchor = FindPlayerStart(NewPC);
	const FVector  Loc = Anchor ? Anchor->GetActorLocation() : FVector::ZeroVector;
	const FRotator Rot = Anchor ? Anchor->GetActorRotation() : FRotator::ZeroRotator;
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Owner = NewPC;
	
	ALOLHeroCharacter* Hero = GetWorld()->SpawnActor<ALOLHeroCharacter>(
			HeroClass, Loc, Rot, SpawnParams);

	if (!Hero)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hero spawn failed at %s"), *Loc.ToString());
		return;
	}
	
	if (ALOLPlayerState* PS = NewPC->GetPlayerState<ALOLPlayerState>())
	{
		PS->SetControlledHero(Hero);
	}
	
}