// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LOLPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class UEnhancedInputLocalPlayerSubsystem;
class ALOLTopCameraPawn;
class ALOLHeroCharacter;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class LOL_DEMO_API ALOLPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ALOLPlayerController();
	
	ALOLHeroCharacter* GetHeroCharacter() const;
	void SetHeroCharacter(ALOLHeroCharacter* NewHeroCharacter);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="LOL|Input")
	UInputMappingContext* IMC_LOL;
	UPROPERTY(EditDefaultsOnly, Category="LOL|Input|Camera")
	UInputAction* IA_MoveCamera;
	UPROPERTY(EditDefaultsOnly, Category="LOL|Input|Camera")
	UInputAction* IA_ToggleLock;
	UPROPERTY(EditDefaultsOnly, Category="LOL|Input|Camera")
	UInputAction* IA_CenterCamera;
	UPROPERTY(EditDefaultsOnly, Category="LOL|Input|Hero")
	UInputAction* IA_ClickCommand;
	
	UPROPERTY(EditDefaultsOnly, Category="LOL|Camera")
	float EdgeThresholdPixels = 8.f;
	UPROPERTY(EditDefaultsOnly, Category="LOL|Camera")
	float SoftZonePixels = 40.f;
	UPROPERTY(EditDefaultsOnly, Category="LOL|Camera")
	float EdgePanStrength     = 1.f;
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick( float DeltaTime ) override;
	
	void OnMoveCamera(const FInputActionValue& Value);
	void OnToggleLock(const FInputActionValue& Value);
	void OnCenterCamera(const FInputActionValue& Value);
	void OnClickCommand(const FInputActionValue& Value);
	
private:
	UPROPERTY()
	ALOLTopCameraPawn* CameraPawn;
	bool bCameraLocked = false;
	
	float ComputeAxisIntensity(float Pos, float Size) const;
	
	UPROPERTY()
	ALOLHeroCharacter* HeroCharacter;
};
