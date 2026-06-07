// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LOLPlayerState.generated.h"

/**
 * 
 */

class ALOLHeroCharacter;

UCLASS()
class LOL_DEMO_API ALOLPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	ALOLHeroCharacter* GetControlledHero() const { return ControlledHero; }
	
	void SetControlledHero(ALOLHeroCharacter* NewHero);
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
private:
	UPROPERTY(ReplicatedUsing=OnRep_ControlledHero)
	TObjectPtr<ALOLHeroCharacter> ControlledHero;
	
	UFUNCTION()
	void OnRep_ControlledHero();
};
