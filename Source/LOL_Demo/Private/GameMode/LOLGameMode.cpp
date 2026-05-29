// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LOLGameMode.h"
#include "Camera/LOLTopCameraPawn.h"
#include "Player/LOLPlayerController.h"


ALOLGameMode::ALOLGameMode()
{
	DefaultPawnClass = ALOLTopCameraPawn::StaticClass();
	PlayerControllerClass = ALOLPlayerController::StaticClass();
}
