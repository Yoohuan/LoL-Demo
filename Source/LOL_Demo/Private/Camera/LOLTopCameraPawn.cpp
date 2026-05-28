// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/LOLTopCameraPawn.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"


// Sets default values
ALOLTopCameraPawn::ALOLTopCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* Root = CreateDefaultSubobject<USpringArmComponent>("Root");
	SetRootComponent(Root);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(Root);
	SpringArm->TargetArmLength = 1800.f;
	SpringArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw   = false;
	SpringArm->bInheritRoll  = false;
	SpringArm->bEnableCameraLag = true;       // 平滑跟随
	SpringArm->CameraLagSpeed  = 10.f;
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->SetFieldOfView(40.f);
	
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>("Movement");
	Movement->MaxSpeed = 3000.f;
	Movement->Acceleration = 20000.f;
	Movement->Deceleration = 20000.f;
	
}

// Called when the game starts or when spawned
/*void ALOLTopCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}*/

// Called every frame
/*void ALOLTopCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}*/

// Called to bind functionality to input
/*void ALOLTopCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}*/

