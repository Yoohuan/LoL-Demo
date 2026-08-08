// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "LOLHeroCharacter.generated.h"

class ULOLAbilitySystemComponent;
class ULOLAttributeSet;
class UGameplayEffect;
struct FOnAttributeChangeData;

UCLASS()
class LOL_DEMO_API ALOLHeroCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ALOLHeroCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	ULOLAttributeSet* GetAttributeSet() const { return AttributeSet; }
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_Controller() override;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, Category="GAS")
	TObjectPtr<ULOLAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<ULOLAttributeSet> AttributeSet;
	UPROPERTY(EditDefaultsOnly, Category="GAS")
	TSubclassOf<UGameplayEffect> DefaultAttributesEffect;   // 指向 GE_DefaultAttributes
	
	void InitAbilitySystem();      // 幂等：两端各跑一次
	void InitDefaultAttributes();  // 仅服务器
	void OnMovementSpeedChanged(const FOnAttributeChangeData& Data);

	// 玩家英雄的本地寻路跟随：路径点间距小于该值视为到达
	UPROPERTY(EditDefaultsOnly, Category="LOL|Move")
	float PathAcceptanceRadius = 50.f;

private:
	bool bAbilitySystemInitialized = false;

	// 本地路径跟随状态（仅本地玩家控制端使用，不复制）
	TArray<FVector> PathPoints;
	int32 NextPathPointIndex = -1;
	void TickPathSteering();

public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category="LOL|Move")
	void IssueMoveOrder(const FVector& TargetLocation);

};
