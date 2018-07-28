#include "TestUnit.hpp"

#include "gtest/gtest.h"

TEST(NoLockup, SunkenVSDA) {
  FAP::FastAPproximation<> fap;

  fap.addUnitPlayer1(
    testUnit(BWAPI::UnitTypes::Zerg_Sunken_Colony)
    .setPosition({0, 0})
  );

  fap.addUnitPlayer2(
    testUnit(BWAPI::UnitTypes::Protoss_Dark_Archon)
    .setPosition({1000, 0})
  );

  fap.simulate(-1);
}

TEST(NoLockup, SunkenVSCorsair) {
  FAP::FastAPproximation<> fap;

  fap.addUnitPlayer1(
    testUnit(BWAPI::UnitTypes::Zerg_Sunken_Colony)
    .setPosition({ 0, 0 })
  );

  fap.addUnitPlayer2(
    testUnit(BWAPI::UnitTypes::Protoss_Corsair)
    .setPosition({ 0, 0 })
  );

  fap.simulate(-1);
}

TEST(NoLockup, RaxMirror) {
  FAP::FastAPproximation<> fap;

  fap.addUnitPlayer1(
    testUnit(BWAPI::UnitTypes::Terran_Barracks)
    .setPosition({ 0, 0 })
  );

  fap.addUnitPlayer2(
    testUnit(BWAPI::UnitTypes::Terran_Barracks)
    .setPosition({ 0, 0 })
  );

  fap.simulate(-1);
}

TEST(NoLockup, ScoutVSLarva) {
  FAP::FastAPproximation<> fap;

  fap.addUnitPlayer1(
    testUnit(BWAPI::UnitTypes::Protoss_Scout)
    .setPosition({ 0, 0 })
  );

  fap.addUnitPlayer2(
    testUnit(BWAPI::UnitTypes::Zerg_Larva)
    .setPosition({ 0, 0 })
  );

  fap.simulate(-1);
}

TEST(NoLockup, ScoutVSEgg) {
  FAP::FastAPproximation<> fap;

  fap.addUnitPlayer1(
    testUnit(BWAPI::UnitTypes::Protoss_Scout)
    .setPosition({ 0, 0 })
  );

  fap.addUnitPlayer2(
    testUnit(BWAPI::UnitTypes::Zerg_Egg)
    .setPosition({ 0, 0 })
  );

  fap.simulate(-1);
}

TEST(NoLockup, ScoutVSEggWithArmorUpgrades) {
  FAP::FastAPproximation<> fap;

  fap.addUnitPlayer1(
    testUnit(BWAPI::UnitTypes::Protoss_Scout)
    .setPosition({ 0, 0 })
  );

  Upgrades armorUps;
  armorUps.armorUpgrades = 3;

  fap.addUnitPlayer2(
    testUnit(BWAPI::UnitTypes::Zerg_Egg, armorUps)
    .setPosition({ 0, 0 })
  );

  fap.simulate(-1);
}
