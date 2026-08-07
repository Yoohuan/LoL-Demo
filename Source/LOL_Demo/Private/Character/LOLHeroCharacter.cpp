// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LOLHeroCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "AbilitySystem/LOLAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/LOLAttributeSet.h"


// Sets default values
ALOLHeroCharacter::ALOLHeroCharacter()
{
	// 本地路径跟随需要逐帧喂输入
	PrimaryActorTick.bCanEverTick = true;
	
	// 玩家英雄由 PC 占有（客户端 Autonomous Proxy，CMC 预测生效）；
	// 只有关卡里手摆的英雄（假人/野怪测试用）才自动交给 AI
	AutoPossessAI = EAutoPossessAI::PlacedInWorld;
	AIControllerClass = AAIController::StaticClass();
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	MovementComponent->bOrientRotationToMovement = true;
	MovementComponent->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	MovementComponent->MaxWalkSpeed = 325.0f;
	MovementComponent->bConstrainToPlane = true;
	MovementComponent->bSnapToPlaneAtStart = true;
	
	AbilitySystemComponent = CreateDefaultSubobject<ULOLAbilitySystemComponent>(TEXT("ASC"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<ULOLAttributeSet>(FName("AttributeSet"));
}

UAbilitySystemComponent* ALOLHeroCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ALOLHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (!bAbilitySystemInitialized)
	{
		InitAbilitySystem();
	}
	else
	{
		// 重占有（英雄切换 / AI↔玩家交接）：ActorInfo 里缓存的 Controller 已过期，刷新
		AbilitySystemComponent->RefreshAbilityActorInfo();
	}
}

void ALOLHeroCharacter::OnRep_Controller()
{
	Super::OnRep_Controller();
	// 拥有客户端上 Controller 指针到达/变更时，刷新 ActorInfo 缓存的 PlayerController
	if (bAbilitySystemInitialized && AbilitySystemComponent)
	{
		AbilitySystemComponent->RefreshAbilityActorInfo();
	}
}

// Called when the game starts or when spawned
void ALOLHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAbilitySystem();
}

void ALOLHeroCharacter::InitAbilitySystem()
{
	if (bAbilitySystemInitialized || !AbilitySystemComponent || !AttributeSet) return;
	bAbilitySystemInitialized = true;
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSet->GetMovementSpeedAttribute())
		.AddUObject(this, &ALOLHeroCharacter::OnMovementSpeedChanged);
	
	if (HasAuthority()) InitDefaultAttributes();
}

void ALOLHeroCharacter::InitDefaultAttributes()
{
	if (!DefaultAttributesEffect) return;
	FGameplayEffectContextHandle Ctx = AbilitySystemComponent->MakeEffectContext();
	Ctx.AddSourceObject(this);
	const FGameplayEffectSpecHandle Spec = 
		AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributesEffect, 1.f, Ctx);
	
	if (Spec.IsValid())
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
}

void ALOLHeroCharacter::OnMovementSpeedChanged(const FOnAttributeChangeData& Data)
{
	GetCharacterMovement()->MaxWalkSpeed = Data.NewValue;
}

// Called every frame
void ALOLHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickPathSteering();
}

// Called to bind functionality to input
void ALOLHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ALOLHeroCharacter::IssueMoveOrder(const FVector& TargetLocation)
{
	if (IsPlayerControlled() && IsLocallyControlled())
	{
		// 玩家英雄：本地建路 + 逐帧 AddMovementInput（见 TickPathSteering）。
		// 不用 SimpleMoveToLocation：UPathFollowingComponent 在联机客户端上请求会被立即作废
		// （实测 5.7：路径接受后数帧内 NO_MOVE，无输入产生）；而手动输入走 CMC 预测管线已验证可靠。
		PathPoints.Reset();
		NextPathPointIndex = -1;
		UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(
			GetWorld(), GetActorLocation(), TargetLocation, this);
		if (NavPath && NavPath->IsValid() && NavPath->PathPoints.Num() > 1)
		{
			PathPoints = NavPath->PathPoints;
			NextPathPointIndex = 1;   // 0 号点是起点自身
		}
	}
	else if (AController* HeroController = GetController())
	{
		// AI（小兵/假人/未来的野怪）：服务器权威寻路，原路径保留
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(HeroController, TargetLocation);
	}
}

void ALOLHeroCharacter::TickPathSteering()
{
	if (NextPathPointIndex < 0 || NextPathPointIndex >= PathPoints.Num()) return;

	FVector ToTarget = PathPoints[NextPathPointIndex] - GetActorLocation();
	ToTarget.Z = 0.f;

	if (ToTarget.SizeSquared() <= FMath::Square(PathAcceptanceRadius))
	{
		++NextPathPointIndex;
		if (NextPathPointIndex >= PathPoints.Num())
		{
			PathPoints.Reset();
			NextPathPointIndex = -1;   // 到达终点，靠 CMC 制动自然停下
		}
		return;
	}

	AddMovementInput(ToTarget.GetSafeNormal());
}
