// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LOLGameMode.h"
#include "Camera/LOLTopCameraPawn.h"


ALOLGameMode::ALOLGameMode()
{
	DefaultPawnClass = ALOLTopCameraPawn::StaticClass();
}
