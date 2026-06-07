// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LOLGameMode.generated.h"

class ALOLHeroCharacter;

UCLASS()
class LOL_DEMO_API ALOLGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ALOLGameMode();
	
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPC) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Hero")
	TSubclassOf<ALOLHeroCharacter> HeroClass;
	
};
