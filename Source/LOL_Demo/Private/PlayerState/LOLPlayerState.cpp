// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerState/LOLPlayerState.h"

#include "Net/UnrealNetwork.h"
#include "Character/LOLHeroCharacter.h"

void ALOLPlayerState::SetControlledHero(ALOLHeroCharacter* NewHero)
{
	// Owner/归属链现在由 Possess 流程自动维护（APawn::PossessedBy → SetOwner(Controller)），
	// 这里只记录"当前操控的是谁"。未来英雄切换：PC->Possess(新英雄) + 本函数更新指向，
	// 旧英雄 SpawnDefaultController() 交还 AI。
	ControlledHero = NewHero;
}

UAbilitySystemComponent* ALOLPlayerState::GetControlledHeroASC() const
{
	return ControlledHero ? ControlledHero->GetAbilitySystemComponent() : nullptr;
}

ULOLAttributeSet* ALOLPlayerState::GetControlledHeroAttributeSet() const
{
	return ControlledHero ? ControlledHero->GetAttributeSet() : nullptr;
}

void ALOLPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ALOLPlayerState, ControlledHero);
}

void ALOLPlayerState::OnRep_ControlledHero()
{
	
}