// Fill out your copyright notice in the Description page of Project Settings.


#include "LOLAttributeSet.h"
#include "Net/UnrealNetwork.h"

ULOLAttributeSet::ULOLAttributeSet()
{
	InitMaxHealth(640.f);  
	InitHealth(640.f);
	InitMaxMana(280.f);   
	InitMana(280.f);
	InitAttackDamage(60.f); 
	InitAttackSpeed(0.65f);
	InitArmor(30.f);      
	InitMagicResistance(32.f);
	InitCritDamage(2.0f); 
	InitMovementSpeed(325.f);
}


void ULOLAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps );
	DOREPLIFETIME_CONDITION_NOTIFY(ULOLAttributeSet, Health,    COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULOLAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULOLAttributeSet, Mana,    COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULOLAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULOLAttributeSet, HealthRegen,    COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULOLAttributeSet, ManaRegen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULOLAttributeSet, AttackDamage,    COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULOLAttributeSet, SpellPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULOLAttributeSet, AttackSpeed,    COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULOLAttributeSet, CritChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULOLAttributeSet, CritDamage,    COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULOLAttributeSet, ArmorPenFlat, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULOLAttributeSet, ArmorPenPercent,    COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULOLAttributeSet, MagicPenFlat, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULOLAttributeSet, MagicPenPercent,    COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULOLAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULOLAttributeSet, MagicResistance,    COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULOLAttributeSet, Tenacity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULOLAttributeSet, AbilityHaste,    COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULOLAttributeSet, MovementSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULOLAttributeSet, PhysicalVamp,    COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULOLAttributeSet, MagicVamp, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULOLAttributeSet, HealShieldPower,    COND_None, REPNOTIFY_Always);
	
}

void ULOLAttributeSet::PreAttributeChange(const FGameplayAttribute& Attr, float& NewValue)
{
	Super::PreAttributeChange(Attr, NewValue);
}

void ULOLAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attr, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attr, NewValue);
}

void ULOLAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

void ULOLAttributeSet::OnRep_Health(const FGameplayAttributeData& Old) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULOLAttributeSet, Health, Old);
}

void ULOLAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& Old) const
{
}

void ULOLAttributeSet::OnRep_Mana(const FGameplayAttributeData& Old) const
{
}

void ULOLAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& Old) const
{
}

void ULOLAttributeSet::OnRep_HealthRegen(const FGameplayAttributeData& Old) const
{
}

void ULOLAttributeSet::OnRep_ManaRegen(const FGameplayAttributeData& Old) const
{
}

void ULOLAttributeSet::OnRep_AttackDamage(const FGameplayAttributeData& Old) const
{
}

void ULOLAttributeSet::OnRep_SpellPower(const FGameplayAttributeData& Old) const
{
}

void ULOLAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& Old) const
{
}

void ULOLAttributeSet::OnRep_CritChance(const FGameplayAttributeData& Old) const
{
}

void ULOLAttributeSet::OnRep_CritDamage(const FGameplayAttributeData& Old) const
{
}

void ULOLAttributeSet::OnRep_ArmorPenFlat(const FGameplayAttributeData& Old) const
{
}

void ULOLAttributeSet::OnRep_ArmorPenPercent(const FGameplayAttributeData& Old) const
{
}

void ULOLAttributeSet::OnRep_MagicPenFlat(const FGameplayAttributeData& Old) const
{
}

void ULOLAttributeSet::OnRep_MagicPenPercent(const FGameplayAttributeData& Old) const
{
}

void ULOLAttributeSet::OnRep_Armor(const FGameplayAttributeData& Old) const
{
}

void ULOLAttributeSet::OnRep_MagicResistance(const FGameplayAttributeData& Old) const
{
}

void ULOLAttributeSet::OnRep_Tenacity(const FGameplayAttributeData& Old) const
{
}

void ULOLAttributeSet::OnRep_AbilityHaste(const FGameplayAttributeData& Old) const
{
}

void ULOLAttributeSet::OnRep_MovementSpeed(const FGameplayAttributeData& Old) const
{
}

void ULOLAttributeSet::OnRep_PhysicalVamp(const FGameplayAttributeData& Old) const
{
}

void ULOLAttributeSet::OnRep_MagicVamp(const FGameplayAttributeData& Old) const
{
}

void ULOLAttributeSet::OnRep_HealShieldPower(const FGameplayAttributeData& Old) const
{
}

void ULOLAttributeSet::ClampAttribute(const FGameplayAttribute& Attr, float& NewValue) const
{
}
