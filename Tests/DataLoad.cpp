#include "TestUnit.hpp"

#include "gtest/gtest.h"

TEST(Data, MarineLoad) {
  FAP::FastAPproximation fap;

  fap.addUnitPlayer1(
    testUnit(BWAPI::UnitTypes::Terran_Marine)
    .setPosition({0, 0})
  );

  auto marine = fap.getState().first->front();

  EXPECT_EQ(marine.unitType, BWAPI::UnitTypes::Terran_Marine);

  EXPECT_EQ(marine.health, BWAPI::UnitTypes::Terran_Marine.maxHitPoints() << 8);
  EXPECT_EQ(marine.maxHealth, BWAPI::UnitTypes::Terran_Marine.maxHitPoints() << 8);

  EXPECT_EQ(marine.shields, BWAPI::UnitTypes::Terran_Marine.maxShields() << 8);
  EXPECT_EQ(marine.maxShields, BWAPI::UnitTypes::Terran_Marine.maxShields() << 8);

  EXPECT_EQ(marine.groundDamage, BWAPI::UnitTypes::Terran_Marine.groundWeapon().damageAmount());
  EXPECT_EQ(marine.airDamage, BWAPI::UnitTypes::Terran_Marine.airWeapon().damageAmount());

  EXPECT_EQ(marine.groundDamageType, BWAPI::DamageTypes::Normal);
  EXPECT_EQ(marine.airDamageType, BWAPI::DamageTypes::Normal);

  EXPECT_EQ(marine.unitSize, BWAPI::UnitTypes::Terran_Marine.size());

  EXPECT_EQ(marine.speed, static_cast<float>(BWAPI::UnitTypes::Terran_Marine.topSpeed()));
  EXPECT_EQ(marine.speedSquared, marine.speed*marine.speed);

  EXPECT_EQ(marine.groundCooldown, BWAPI::UnitTypes::Terran_Marine.groundWeapon().damageCooldown());
  EXPECT_EQ(marine.airCooldown, BWAPI::UnitTypes::Terran_Marine.airWeapon().damageCooldown());

  EXPECT_EQ(marine.armor, 0);
}

TEST(Data, StimmedMarine) {
  FAP::FastAPproximation fap;

  fap.addUnitPlayer1(
    FAP::makeUnit()
    .setUnitType(BWAPI::UnitTypes::Terran_Marine)
    .setPosition({ 0, 0 })
    .setHealth(BWAPI::UnitTypes::Terran_Marine.maxHitPoints())
    .setShields(BWAPI::UnitTypes::Terran_Marine.maxShields())
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
    .setStimmed(true)
    .setRangeUpgrade(false)
  );

  auto marine = fap.getState().first->front();

  EXPECT_EQ(marine.speed, static_cast<float>(BWAPI::UnitTypes::Terran_Marine.topSpeed() * 1.5f));
  EXPECT_EQ(marine.speedSquared, marine.speed*marine.speed);

  EXPECT_EQ(marine.groundCooldown, BWAPI::UnitTypes::Terran_Marine.groundWeapon().damageCooldown() / 2);
  EXPECT_EQ(marine.airCooldown, BWAPI::UnitTypes::Terran_Marine.airWeapon().damageCooldown() / 2);
}

TEST(Data, SpeedUpgradedZergling) {
  FAP::FastAPproximation fap;

  fap.addUnitPlayer1(
    FAP::makeUnit()
    .setUnitType(BWAPI::UnitTypes::Zerg_Zergling)
    .setPosition({ 0, 0 })
    .setHealth(BWAPI::UnitTypes::Zerg_Zergling.maxHitPoints())
    .setShields(BWAPI::UnitTypes::Zerg_Zergling.maxShields())
    .setFlying(false)
    .setElevation(-1)
    .setScore(5)
    .setAttackerCount(0)
    .setArmorUpgrades(0)
    .setAttackUpgrades(0)
    .setShieldUpgrades(0)
    .setSpeedUpgrade(true)
    .setAttackSpeedUpgrade(false)
    .setAttackCooldownRemaining(0)
    .setStimmed(false)
    .setRangeUpgrade(false)
  );

  auto ling = fap.getState().first->front();

  EXPECT_EQ(ling.speed, static_cast<float>(BWAPI::UnitTypes::Zerg_Zergling.topSpeed() * 1.5f));
  EXPECT_EQ(ling.speedSquared, ling.speed*ling.speed);
}

TEST(Data, SpeedUpgradedOverlord) {
  FAP::FastAPproximation fap;

  fap.addUnitPlayer1(
    FAP::makeUnit()
    .setUnitType(BWAPI::UnitTypes::Zerg_Overlord)
    .setPosition({ 0, 0 })
    .setHealth(BWAPI::UnitTypes::Zerg_Overlord.maxHitPoints())
    .setShields(BWAPI::UnitTypes::Zerg_Overlord.maxShields())
    .setFlying(false)
    .setElevation(-1)
    .setScore(5)
    .setAttackerCount(0)
    .setArmorUpgrades(0)
    .setAttackUpgrades(0)
    .setShieldUpgrades(0)
    .setSpeedUpgrade(true)
    .setAttackSpeedUpgrade(false)
    .setAttackCooldownRemaining(0)
    .setStimmed(false)
    .setRangeUpgrade(false)
  );

  auto ling = fap.getState().first->front();

  EXPECT_EQ(ling.speed, static_cast<float>(BWAPI::UnitTypes::Zerg_Overlord.topSpeed() * 4.0f));
  EXPECT_EQ(ling.speedSquared, ling.speed*ling.speed);
}

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

TEST(Data, BunkerWithAttackUpgrade) {
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
    .setAttackerCount(1)
    .setArmorUpgrades(0)
    .setAttackUpgrades(1)
    .setShieldUpgrades(0)
    .setSpeedUpgrade(false)
    .setAttackSpeedUpgrade(false)
    .setAttackCooldownRemaining(0)
    .setStimmed(false)
    .setRangeUpgrade(false)
  );

  auto bunker = fap.getState().first->front();
  EXPECT_EQ(bunker.groundDamage, BWAPI::UnitTypes::Terran_Marine.groundWeapon().damageAmount() + 1);
  EXPECT_EQ(bunker.airDamage, BWAPI::UnitTypes::Terran_Marine.airWeapon().damageAmount() + 1);
}

TEST(Data, BunkerWithRangeUpgrade) {
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
    .setAttackerCount(1)
    .setArmorUpgrades(0)
    .setAttackUpgrades(0)
    .setShieldUpgrades(0)
    .setSpeedUpgrade(false)
    .setAttackSpeedUpgrade(false)
    .setAttackCooldownRemaining(0)
    .setStimmed(false)
    .setRangeUpgrade(true)
  );

  auto bunker = fap.getState().first->front();

  EXPECT_EQ(bunker.groundMaxRangeSquared,
    (BWAPI::UnitTypes::Terran_Marine.groundWeapon().maxRange() + 64) * (BWAPI::UnitTypes::Terran_Marine.groundWeapon().maxRange() + 64));
  EXPECT_EQ(bunker.airMaxRangeSquared,
    (BWAPI::UnitTypes::Terran_Marine.airWeapon().maxRange() + 64) * (BWAPI::UnitTypes::Terran_Marine.airWeapon().maxRange() + 64));
}

TEST(Data, FullCarrier) {
  FAP::FastAPproximation fap;

  fap.addUnitPlayer1(
    FAP::makeUnit()
    .setUnitType(BWAPI::UnitTypes::Protoss_Carrier)
    .setPosition({ 0, 0 })
    .setHealth(BWAPI::UnitTypes::Protoss_Carrier.maxHitPoints())
    .setShields(BWAPI::UnitTypes::Protoss_Carrier.maxShields())
    .setFlying(true)
    .setElevation(-1)
    .setScore(5)
    .setAttackerCount(8)
    .setArmorUpgrades(0)
    .setAttackUpgrades(0)
    .setShieldUpgrades(0)
    .setSpeedUpgrade(false)
    .setAttackSpeedUpgrade(false)
    .setAttackCooldownRemaining(0)
    .setStimmed(false)
    .setRangeUpgrade(true)
  );

  auto carrier = fap.getState().first->front();

  EXPECT_EQ(carrier.unitType, BWAPI::UnitTypes::Protoss_Carrier);

  EXPECT_EQ(carrier.groundDamage, BWAPI::UnitTypes::Protoss_Interceptor.groundWeapon().damageAmount());
  EXPECT_EQ(carrier.airDamage, BWAPI::UnitTypes::Protoss_Interceptor.airWeapon().damageAmount());

  EXPECT_EQ(carrier.groundMaxRangeSquared, (8*32)*(8*32));
  EXPECT_EQ(carrier.airMaxRangeSquared, (8*32)*(8*32));

  EXPECT_EQ(carrier.groundCooldown, 4);
  EXPECT_EQ(carrier.airCooldown, 4);
}

TEST(Data, SingleInterceptorCarrier) {
  FAP::FastAPproximation fap;

  fap.addUnitPlayer1(
    FAP::makeUnit()
    .setUnitType(BWAPI::UnitTypes::Protoss_Carrier)
    .setPosition({ 0, 0 })
    .setHealth(BWAPI::UnitTypes::Protoss_Carrier.maxHitPoints())
    .setShields(BWAPI::UnitTypes::Protoss_Carrier.maxShields())
    .setFlying(true)
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
    .setRangeUpgrade(true)
  );

  auto carrier = fap.getState().first->front();

  EXPECT_EQ(carrier.unitType, BWAPI::UnitTypes::Protoss_Carrier);

  EXPECT_EQ(carrier.groundDamage, BWAPI::UnitTypes::Protoss_Interceptor.groundWeapon().damageAmount());
  EXPECT_EQ(carrier.airDamage, BWAPI::UnitTypes::Protoss_Interceptor.airWeapon().damageAmount());

  EXPECT_EQ(carrier.groundMaxRangeSquared, (8 * 32)*(8 * 32));
  EXPECT_EQ(carrier.airMaxRangeSquared, (8 * 32)*(8 * 32));

  EXPECT_EQ(carrier.groundCooldown, 37);
  EXPECT_EQ(carrier.airCooldown, 37);
}