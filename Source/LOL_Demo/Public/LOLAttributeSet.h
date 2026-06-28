// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "LOLAttributeSet.generated.h"

/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class LOL_DEMO_API ULOLAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	ULOLAttributeSet();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void PreAttributeChange(const FGameplayAttribute& Attr, float& NewValue) override;
    virtual void PreAttributeBaseChange(const FGameplayAttribute& Attr, float& NewValue) const override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

    // ===== Vital =====
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Health, Category="Vital")
    FGameplayAttributeData Health;			ATTRIBUTE_ACCESSORS(ULOLAttributeSet, Health)
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxHealth, Category="Vital")
    FGameplayAttributeData MaxHealth;		ATTRIBUTE_ACCESSORS(ULOLAttributeSet, MaxHealth)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Mana, Category="Vital")
    FGameplayAttributeData Mana;            ATTRIBUTE_ACCESSORS(ULOLAttributeSet, Mana)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxMana, Category="Vital")
    FGameplayAttributeData MaxMana;         ATTRIBUTE_ACCESSORS(ULOLAttributeSet, MaxMana)

    // ===== Regen =====
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_HealthRegen, Category="Regen")
    FGameplayAttributeData HealthRegen;     ATTRIBUTE_ACCESSORS(ULOLAttributeSet, HealthRegen)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ManaRegen, Category="Regen")
    FGameplayAttributeData ManaRegen;       ATTRIBUTE_ACCESSORS(ULOLAttributeSet, ManaRegen)

    // ===== Offense =====
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_AttackDamage, Category="Offense")
    FGameplayAttributeData AttackDamage;    ATTRIBUTE_ACCESSORS(ULOLAttributeSet, AttackDamage)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_SpellPower, Category="Offense")
    FGameplayAttributeData SpellPower;    ATTRIBUTE_ACCESSORS(ULOLAttributeSet, SpellPower)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_AttackSpeed, Category="Offense")
    FGameplayAttributeData AttackSpeed;     ATTRIBUTE_ACCESSORS(ULOLAttributeSet, AttackSpeed)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CritChance, Category="Offense")
    FGameplayAttributeData CritChance;      ATTRIBUTE_ACCESSORS(ULOLAttributeSet, CritChance)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CritDamage, Category="Offense")
    FGameplayAttributeData CritDamage;      ATTRIBUTE_ACCESSORS(ULOLAttributeSet, CritDamage)

    // ===== Penetration =====
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ArmorPenFlat, Category="Penetration")
    FGameplayAttributeData ArmorPenFlat;    ATTRIBUTE_ACCESSORS(ULOLAttributeSet, ArmorPenFlat)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ArmorPenPercent, Category="Penetration")
    FGameplayAttributeData ArmorPenPercent; ATTRIBUTE_ACCESSORS(ULOLAttributeSet, ArmorPenPercent)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MagicPenFlat, Category="Penetration")
    FGameplayAttributeData MagicPenFlat;    ATTRIBUTE_ACCESSORS(ULOLAttributeSet, MagicPenFlat)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MagicPenPercent, Category="Penetration")
    FGameplayAttributeData MagicPenPercent; ATTRIBUTE_ACCESSORS(ULOLAttributeSet, MagicPenPercent)

    // ===== Defense =====
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Armor, Category="Defense")
    FGameplayAttributeData Armor;           ATTRIBUTE_ACCESSORS(ULOLAttributeSet, Armor)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MagicResistance, Category="Defense")
    FGameplayAttributeData MagicResistance; ATTRIBUTE_ACCESSORS(ULOLAttributeSet, MagicResistance)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Tenacity, Category="Defense")
    FGameplayAttributeData Tenacity;        ATTRIBUTE_ACCESSORS(ULOLAttributeSet, Tenacity)

    // ===== Utility =====
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_AbilityHaste, Category="Utility")
    FGameplayAttributeData AbilityHaste;    ATTRIBUTE_ACCESSORS(ULOLAttributeSet, AbilityHaste)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MovementSpeed, Category="Utility")
    FGameplayAttributeData MovementSpeed;   ATTRIBUTE_ACCESSORS(ULOLAttributeSet, MovementSpeed)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_PhysicalVamp, Category="Utility")
    FGameplayAttributeData PhysicalVamp;    ATTRIBUTE_ACCESSORS(ULOLAttributeSet, PhysicalVamp)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MagicVamp, Category="Utility")
    FGameplayAttributeData MagicVamp;       ATTRIBUTE_ACCESSORS(ULOLAttributeSet, MagicVamp)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_HealShieldPower, Category="Utility")
    FGameplayAttributeData HealShieldPower; ATTRIBUTE_ACCESSORS(ULOLAttributeSet, HealShieldPower)

    // ===== Meta =====
    UPROPERTY(BlueprintReadOnly, Category="Meta")
    FGameplayAttributeData IncomingDamage;  ATTRIBUTE_ACCESSORS(ULOLAttributeSet, IncomingDamage)
	UPROPERTY(BlueprintReadOnly, Category="Meta")
    FGameplayAttributeData IncomingHealing; ATTRIBUTE_ACCESSORS(ULOLAttributeSet, IncomingHealing)
	
protected:
	UFUNCTION() void OnRep_Health(const FGameplayAttributeData& Old) const;
	UFUNCTION() void OnRep_MaxHealth(const FGameplayAttributeData& Old) const;
	UFUNCTION() void OnRep_Mana(const FGameplayAttributeData& Old) const;
	UFUNCTION() void OnRep_MaxMana(const FGameplayAttributeData& Old) const;
	UFUNCTION() void OnRep_HealthRegen(const FGameplayAttributeData& Old) const;
	UFUNCTION() void OnRep_ManaRegen(const FGameplayAttributeData& Old) const;
	UFUNCTION() void OnRep_AttackDamage(const FGameplayAttributeData& Old) const;
	UFUNCTION() void OnRep_SpellPower(const FGameplayAttributeData& Old) const;
	UFUNCTION() void OnRep_AttackSpeed(const FGameplayAttributeData& Old) const;
	UFUNCTION() void OnRep_CritChance(const FGameplayAttributeData& Old) const;
	UFUNCTION() void OnRep_CritDamage(const FGameplayAttributeData& Old) const;
	UFUNCTION() void OnRep_ArmorPenFlat(const FGameplayAttributeData& Old) const;
	UFUNCTION() void OnRep_ArmorPenPercent(const FGameplayAttributeData& Old) const;
	UFUNCTION() void OnRep_MagicPenFlat(const FGameplayAttributeData& Old) const;
	UFUNCTION() void OnRep_MagicPenPercent(const FGameplayAttributeData& Old) const;
	UFUNCTION() void OnRep_Armor(const FGameplayAttributeData& Old) const;
	UFUNCTION() void OnRep_MagicResistance(const FGameplayAttributeData& Old) const;
	UFUNCTION() void OnRep_Tenacity(const FGameplayAttributeData& Old) const;
	UFUNCTION() void OnRep_AbilityHaste(const FGameplayAttributeData& Old) const;
	UFUNCTION() void OnRep_MovementSpeed(const FGameplayAttributeData& Old) const;
	UFUNCTION() void OnRep_PhysicalVamp(const FGameplayAttributeData& Old) const;
	UFUNCTION() void OnRep_MagicVamp(const FGameplayAttributeData& Old) const;
	UFUNCTION() void OnRep_HealShieldPower(const FGameplayAttributeData& Old) const;

private:
	void ClampAttribute(const FGameplayAttribute& Attr, float& NewValue) const;
	
};
