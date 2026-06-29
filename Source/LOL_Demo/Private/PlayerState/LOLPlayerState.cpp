// Fill out your copyright notice in the Description page of Project Settings.

#include "Net/UnrealNetwork.h"
#include "PlayerState/LOLPlayerState.h"

#include "Character/LOLHeroCharacter.h"

void ALOLPlayerState::SetControlledHero(ALOLHeroCharacter* NewHero)
{
	if (ControlledHero)
	{
		ControlledHero->SetOwner(nullptr);
	}

	ControlledHero = NewHero;

	if (NewHero)
	{
		NewHero->SetOwner(GetPlayerController());
	}
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