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
