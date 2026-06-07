// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LOLPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Camera/LOLTopCameraPawn.h"
#include "Character/LOLHeroCharacter.h"
#include "PlayerState/LOLPlayerState.h"


ALOLPlayerController::ALOLPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

}

void ALOLPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (IA_MoveCamera) EIC->BindAction(IA_MoveCamera, ETriggerEvent::Triggered, this, &ALOLPlayerController::OnMoveCamera);
		if (IA_CenterCamera) EIC->BindAction(IA_CenterCamera, ETriggerEvent::Started, this, &ALOLPlayerController::OnCenterCamera);
		if (IA_ToggleLock) EIC->BindAction(IA_ToggleLock, ETriggerEvent::Started, this, &ALOLPlayerController::OnToggleLock);
		if (IA_ClickCommand) EIC->BindAction(IA_ClickCommand, ETriggerEvent::Started, this, &ALOLPlayerController::OnClickCommand);
	}
}

void ALOLPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	InputModeData.SetHideCursorDuringCapture(false);
	APlayerController::SetInputMode(InputModeData);
	
	UEnhancedInputLocalPlayerSubsystem* LocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (LocalPlayerSubsystem && IMC_LOL)
	{
		LocalPlayerSubsystem->AddMappingContext(IMC_LOL, 0);
	}
	
	CameraPawn = Cast<ALOLTopCameraPawn>(GetPawn());
	
}

void ALOLPlayerController::PlayerTick( float DeltaTime )
{
	Super::PlayerTick( DeltaTime );
	
	if (!CameraPawn) return;

	ALOLHeroCharacter* HeroCharacter = GetControlledHero();
	
	if (bCameraLocked && HeroCharacter)
	{
		CameraPawn->SetActorLocation(HeroCharacter->GetActorLocation());
	}
	else
	{
		float MX, MY;
		if (GetMousePosition(MX, MY))
		{
			int32 ViewportSizeX, ViewportSizeY;
			GetViewportSize(ViewportSizeX, ViewportSizeY);
		
			FVector2D Dir(
			  ComputeAxisIntensity(MX, static_cast<float>(ViewportSizeX)),
			  ComputeAxisIntensity(MY, static_cast<float>(ViewportSizeY))
			  );
		
			UEnhancedInputLocalPlayerSubsystem* LocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
			if (!Dir.IsNearlyZero() && IA_MoveCamera && LocalPlayerSubsystem)
			{
				LocalPlayerSubsystem->InjectInputForAction(IA_MoveCamera, FInputActionValue(Dir), {}, {});
			}
		}
	}
	
	
}

void ALOLPlayerController::OnMoveCamera(const FInputActionValue& Value)
{
	if (!CameraPawn) return;
	
	const FVector2D Dir = Value.Get<FVector2D>();
	
	const FVector WorldDir(-Dir.Y, Dir.X, 0.f);
	CameraPawn->AddMovementInput(WorldDir, EdgePanStrength);
	
}

void ALOLPlayerController::OnToggleLock(const FInputActionValue& Value)
{
	bCameraLocked = !bCameraLocked;
}

void ALOLPlayerController::OnCenterCamera(const FInputActionValue& Value)
{
	ALOLHeroCharacter* HeroCharacter = GetControlledHero();
	if (!CameraPawn || !HeroCharacter) return;
	
	CameraPawn->SetActorLocation(HeroCharacter->GetActorLocation());
}

void ALOLPlayerController::OnClickCommand(const FInputActionValue& Value)
{
	ALOLHeroCharacter* HeroCharacter = GetControlledHero();
	if (!CameraPawn || !HeroCharacter) return;
	
	FHitResult Hit;
	if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
	{
		HeroCharacter->IssueMoveOrder(Hit.ImpactPoint);
	}
	
}

float ALOLPlayerController::ComputeAxisIntensity(float Pos, float Size) const
{
	if (Pos <= EdgeThresholdPixels + SoftZonePixels)
	{
		const float Dist = EdgeThresholdPixels + SoftZonePixels - Pos;
		return -FMath::Clamp(Dist / SoftZonePixels, 0.f, 1.f);
	}
	if (Pos >= Size - EdgeThresholdPixels - SoftZonePixels)
	{
		const float Dist = Pos - (Size - EdgeThresholdPixels - SoftZonePixels);
		return +FMath::Clamp(Dist / SoftZonePixels, 0.f, 1.f);
	}
	return 0.f;
}


ALOLHeroCharacter* ALOLPlayerController::GetControlledHero() const
{
	ALOLPlayerState* PS = GetPlayerState<ALOLPlayerState>();
	if (!PS)
	{
		UE_LOG(LogTemp, Warning, TEXT("[GetControlledHero] PlayerState is NULL (cast to ALOLPlayerState failed?)"));
		return nullptr;
	}

	ALOLHeroCharacter* Hero = PS->GetControlledHero();
	if (!Hero)
	{
		UE_LOG(LogTemp, Warning, TEXT("[GetControlledHero] PlayerState OK but ControlledHero is NULL (Hero never assigned)"));
	}
	return Hero;
}
