// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/LOLAttributeSet.h"
#include "GameplayEffectExtension.h"
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
	ClampAttribute(Attr, NewValue);
	if (Attr == GetMaxHealthAttribute())      AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	else if (Attr == GetMaxManaAttribute())   AdjustAttributeForMaxChange(Mana,   MaxMana,   NewValue, GetManaAttribute());
}

void ULOLAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attr, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attr, NewValue);
	ClampAttribute(Attr, NewValue);
}

void ULOLAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	const FGameplayAttribute& Attr = Data.EvaluatedData.Attribute;

	if (Attr == GetIncomingDamageAttribute())
	{
		const float Dmg = GetIncomingDamage();
		SetIncomingDamage(0.f);                       // 用完即清
		if (Dmg > 0.f)
		{
			SetHealth(FMath::Clamp(GetHealth() - Dmg, 0.f, GetMaxHealth()));
			if (GetHealth() <= 0.f) { /* 广播死亡 / 打 State.Dead 标签 */ }
		}
	}
	else if (Attr == GetIncomingHealingAttribute())
	{
		const float Heal = GetIncomingHealing();
		SetIncomingHealing(0.f);
		SetHealth(FMath::Clamp(GetHealth() + Heal, 0.f, GetMaxHealth()));
	}
}

void ULOLAttributeSet::OnRep_Health(const FGameplayAttributeData& Old) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULOLAttributeSet, Health, Old);
}

void ULOLAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& Old) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULOLAttributeSet, MaxHealth, Old);
}

void ULOLAttributeSet::OnRep_Mana(const FGameplayAttributeData& Old) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULOLAttributeSet, Mana, Old);
}

void ULOLAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& Old) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULOLAttributeSet, MaxMana, Old);
}

void ULOLAttributeSet::OnRep_HealthRegen(const FGameplayAttributeData& Old) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULOLAttributeSet, HealthRegen, Old);
}

void ULOLAttributeSet::OnRep_ManaRegen(const FGameplayAttributeData& Old) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULOLAttributeSet, ManaRegen, Old);
}

void ULOLAttributeSet::OnRep_AttackDamage(const FGameplayAttributeData& Old) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULOLAttributeSet, AttackDamage, Old);
}

void ULOLAttributeSet::OnRep_SpellPower(const FGameplayAttributeData& Old) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULOLAttributeSet, SpellPower, Old);
}

void ULOLAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& Old) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULOLAttributeSet, AttackSpeed, Old);
}

void ULOLAttributeSet::OnRep_CritChance(const FGameplayAttributeData& Old) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULOLAttributeSet, CritChance, Old);
}

void ULOLAttributeSet::OnRep_CritDamage(const FGameplayAttributeData& Old) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULOLAttributeSet, CritDamage, Old);
}

void ULOLAttributeSet::OnRep_ArmorPenFlat(const FGameplayAttributeData& Old) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULOLAttributeSet, ArmorPenFlat, Old);
}

void ULOLAttributeSet::OnRep_ArmorPenPercent(const FGameplayAttributeData& Old) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULOLAttributeSet, ArmorPenPercent, Old);
}

void ULOLAttributeSet::OnRep_MagicPenFlat(const FGameplayAttributeData& Old) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULOLAttributeSet, MagicPenFlat, Old);
}

void ULOLAttributeSet::OnRep_MagicPenPercent(const FGameplayAttributeData& Old) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULOLAttributeSet, MagicPenPercent, Old);
}

void ULOLAttributeSet::OnRep_Armor(const FGameplayAttributeData& Old) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULOLAttributeSet, Armor, Old);
}

void ULOLAttributeSet::OnRep_MagicResistance(const FGameplayAttributeData& Old) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULOLAttributeSet, MagicResistance, Old);
}

void ULOLAttributeSet::OnRep_Tenacity(const FGameplayAttributeData& Old) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULOLAttributeSet, Tenacity, Old);
}

void ULOLAttributeSet::OnRep_AbilityHaste(const FGameplayAttributeData& Old) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULOLAttributeSet, AbilityHaste, Old);
}

void ULOLAttributeSet::OnRep_MovementSpeed(const FGameplayAttributeData& Old) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULOLAttributeSet, MovementSpeed, Old);
}

void ULOLAttributeSet::OnRep_PhysicalVamp(const FGameplayAttributeData& Old) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULOLAttributeSet, PhysicalVamp, Old);
}

void ULOLAttributeSet::OnRep_MagicVamp(const FGameplayAttributeData& Old) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULOLAttributeSet, MagicVamp, Old);
}

void ULOLAttributeSet::OnRep_HealShieldPower(const FGameplayAttributeData& Old) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULOLAttributeSet, HealShieldPower, Old);
}

void ULOLAttributeSet::AdjustAttributeForMaxChange(const FGameplayAttributeData& Affected,
	const FGameplayAttributeData& Max, float NewMax, const FGameplayAttribute& AffectedProp) const
{
	UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
	const float CurMax = Max.GetCurrentValue();
	if (ASC && !FMath::IsNearlyEqual(CurMax, NewMax))
	{
		const float Cur = Affected.GetCurrentValue();
		const float Delta = (CurMax > 0.f) ? (Cur * NewMax / CurMax - Cur) : NewMax;
		ASC->ApplyModToAttributeUnsafe(AffectedProp, EGameplayModOp::Additive, Delta);
	}
}

void ULOLAttributeSet::ClampAttribute(const FGameplayAttribute& Attr, float& NewValue) const
{
	if (Attr == GetHealthAttribute())            NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	else if (Attr == GetManaAttribute())         NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	else if (Attr == GetMaxHealthAttribute()
		  || Attr == GetMaxManaAttribute())      NewValue = FMath::Max(NewValue, 1.f);
	else if (Attr == GetAttackSpeedAttribute())  NewValue = FMath::Clamp(NewValue, 0.2f, 2.5f);
	else if (Attr == GetCritChanceAttribute()
		  || Attr == GetArmorPenPercentAttribute()
		  || Attr == GetMagicPenPercentAttribute()
		  || Attr == GetTenacityAttribute())     NewValue = FMath::Clamp(NewValue, 0.f, 1.f);
	else if (Attr == GetCritDamageAttribute())   NewValue = FMath::Max(NewValue, 1.f);
	else if (Attr == GetArmorAttribute()
		  || Attr == GetMagicResistanceAttribute())
	{
		// 允许为负（减甲/破魔抗）——故意不钳制
		// 若想给护甲设个下限可写：NewValue = FMath::Max(NewValue, -100.f);
	}
	else NewValue = FMath::Max(NewValue, 0.f);   // AD/法强/穿透flat/AH/移速/吸血/HSP/回复/Meta
}
