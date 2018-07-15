#include "TestUnit.hpp"

#include "gtest/gtest.h"

TEST(Combat, MarineTwoOnOne) {
  {
    FAP::FastAPproximation fap;

    for (int i = 0; i < 2; ++i)
      fap.addUnitPlayer1(
        testUnit(BWAPI::UnitTypes::Terran_Marine)
        .setPosition({ 0, 0 })
      );

    fap.addUnitPlayer2(
      testUnit(BWAPI::UnitTypes::Terran_Marine)
      .setPosition({ 0, 0 })
    );

    fap.simulate(-1);

    // Two marines beat one
    EXPECT_FALSE(fap.getState().first->empty());
    EXPECT_TRUE(fap.getState().second->empty());
  }
}

TEST(Combat, MarineOnZealot) {
  FAP::FastAPproximation fap;

  fap.addUnitPlayer1(
    testUnit(BWAPI::UnitTypes::Protoss_Zealot)
    .setPosition({ 0, 0 })
  );

  fap.addUnitPlayer2(
    testUnit(BWAPI::UnitTypes::Terran_Marine)
    .setPosition({ 0, 0 })
  );

  fap.simulate(-1);

  // Zealot beats marine
  EXPECT_FALSE(fap.getState().first->empty());
  EXPECT_TRUE(fap.getState().second->empty());
}

TEST(Combat, MarineOnZergling) {
  FAP::FastAPproximation fap;

  fap.addUnitPlayer1(
    testUnit(BWAPI::UnitTypes::Zerg_Zergling)
    .setPosition({ 0, 0 })
  );

  fap.addUnitPlayer2(
    testUnit(BWAPI::UnitTypes::Terran_Marine)
    .setPosition({ 0, 0 })
  );

  fap.simulate(-1);

  // Zerling beats marine
  EXPECT_FALSE(fap.getState().first->empty());
  EXPECT_TRUE(fap.getState().second->empty());
}

TEST(Combat, MarineFiringAtValkyrie) {
  FAP::FastAPproximation fap;

  fap.addUnitPlayer1(
    testUnit(BWAPI::UnitTypes::Terran_Marine)
    .setPosition({ 0, 0 })
  );

  fap.addUnitPlayer2(
    testUnit(BWAPI::UnitTypes::Terran_Valkyrie)
    .setPosition({ 0, 0 })
  );

  fap.simulate(1);

  // Marine does 6-2 damage to valkyrie
  EXPECT_EQ(fap.getState().second->front().health, fap.getState().second->front().maxHealth - (4 << 8));
}
