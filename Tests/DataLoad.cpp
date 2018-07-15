#include "TestUnit.hpp"

#include "gtest/gtest.h"

TEST(Data, SingleMarineInsideBunker) {
  FAP::FastAPproximation fap;

  fap.addUnitPlayer1(
    FAP::makeUnit()
      .setUnitType(BWAPI::UnitTypes::Terran_Bunker)
      .setPosition({0, 0})
      .setHealth(BWAPI::UnitTypes::Terran_Bunker.maxHitPoints())
      .setShields(BWAPI::UnitTypes::Terran_Bunker.maxShields())
      .setFlying(false)
      .setElevation(-1)
      .setScore(5)
      .setAttackerCount(1)
      .setArmorUpgrades(0)
      .setAttackUpgrades(0)
      .setShieldUpgrades(0)
      .setSpeedUpgrade(false)
      .setAttackSpeedUpgrade(false)
      .setAttackCooldownRemaining(0)
      .setStimmed(false)
      .setRangeUpgrade(false)
  );

  auto bunker = fap.getState().first->front();

  EXPECT_EQ(bunker.unitType, BWAPI::UnitTypes::Terran_Bunker);

  EXPECT_EQ(bunker.health, BWAPI::UnitTypes::Terran_Bunker.maxHitPoints() << 8);
  EXPECT_EQ(bunker.maxHealth, BWAPI::UnitTypes::Terran_Bunker.maxHitPoints() << 8);

  EXPECT_EQ(bunker.shields, BWAPI::UnitTypes::Terran_Bunker.maxShields() << 8);
  EXPECT_EQ(bunker.maxShields, BWAPI::UnitTypes::Terran_Bunker.maxShields() << 8);

  EXPECT_EQ(bunker.groundDamage, BWAPI::UnitTypes::Terran_Marine.groundWeapon().damageAmount());
  EXPECT_EQ(bunker.airDamage, BWAPI::UnitTypes::Terran_Marine.airWeapon().damageAmount());

  EXPECT_EQ(bunker.groundMaxRangeSquared,
    (BWAPI::UnitTypes::Terran_Marine.groundWeapon().maxRange() + 32) * (BWAPI::UnitTypes::Terran_Marine.groundWeapon().maxRange() + 32));
  EXPECT_EQ(bunker.airMaxRangeSquared,
    (BWAPI::UnitTypes::Terran_Marine.airWeapon().maxRange() + 32) * (BWAPI::UnitTypes::Terran_Marine.airWeapon().maxRange() + 32));

  EXPECT_EQ(bunker.groundCooldown, BWAPI::UnitTypes::Terran_Marine.groundWeapon().damageCooldown());
  EXPECT_EQ(bunker.airCooldown, BWAPI::UnitTypes::Terran_Marine.airWeapon().damageCooldown());

  EXPECT_EQ(bunker.speed, 0.0f);
  EXPECT_EQ(bunker.speedSquared, 0.0f);

  EXPECT_EQ(bunker.armor, 1);
}

TEST(Data, EmptyBunker) {
  FAP::FastAPproximation fap;

  fap.addUnitPlayer1(
    FAP::makeUnit()
    .setUnitType(BWAPI::UnitTypes::Terran_Bunker)
    .setPosition({ 0, 0 })
    .setHealth(BWAPI::UnitTypes::Terran_Bunker.maxHitPoints())
    .setShields(BWAPI::UnitTypes::Terran_Bunker.maxShields())
    .setFlying(false)
    .setElevation(-1)
    .setScore(5)
    .setAttackerCount(0)
    .setArmorUpgrades(0)
    .setAttackUpgrades(0)
    .setShieldUpgrades(0)
    .setSpeedUpgrade(false)
    .setAttackSpeedUpgrade(false)
    .setAttackCooldownRemaining(0)
    .setStimmed(false)
    .setRangeUpgrade(false)
  );

  auto bunker = fap.getState().first->front();

  EXPECT_EQ(bunker.unitType, BWAPI::UnitTypes::Terran_Bunker);

  EXPECT_EQ(bunker.health, BWAPI::UnitTypes::Terran_Bunker.maxHitPoints() << 8);
  EXPECT_EQ(bunker.maxHealth, BWAPI::UnitTypes::Terran_Bunker.maxHitPoints() << 8);

  EXPECT_EQ(bunker.shields, BWAPI::UnitTypes::Terran_Bunker.maxShields() << 8);
  EXPECT_EQ(bunker.maxShields, BWAPI::UnitTypes::Terran_Bunker.maxShields() << 8);

  EXPECT_EQ(bunker.groundDamage, 0);
  EXPECT_EQ(bunker.airDamage, 0);

  EXPECT_EQ(bunker.speed, 0.0f);
  EXPECT_EQ(bunker.speedSquared, 0.0f);

  EXPECT_EQ(bunker.armor, 1);
}
