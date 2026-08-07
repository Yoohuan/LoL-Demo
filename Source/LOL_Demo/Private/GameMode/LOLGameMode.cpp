// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LOLGameMode.h"
#include "Character/LOLHeroCharacter.h"
#include "Player/LOLPlayerController.h"
#include "PlayerState/LOLPlayerState.h"


ALOLGameMode::ALOLGameMode()
{
	// 相机不再是默认 Pawn（改为 PC 本地生成）；默认 Pawn = 英雄，见 GetDefaultPawnClassForController
	PlayerControllerClass = ALOLPlayerController::StaticClass();
	PlayerStateClass = ALOLPlayerState::StaticClass();
}

UClass* ALOLGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (HeroClass)
	{
		return HeroClass;
	}
	UE_LOG(LogTemp, Warning, TEXT("[LOLGameMode] HeroClass 未设置，回退到引擎默认 Pawn"));
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ALOLGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPC)
{
	// Super 内部完成：FindPlayerStart → 生成英雄 → NewPC->Possess(英雄)
	// （PossessedBy 会把英雄 Owner 设为 PC，归属链自动就绪）
	Super::HandleStartingNewPlayer_Implementation(NewPC);

	if (!NewPC) return;

	if (ALOLPlayerState* PS = NewPC->GetPlayerState<ALOLPlayerState>())
	{
		PS->SetControlledHero(Cast<ALOLHeroCharacter>(NewPC->GetPawn()));
	}
}