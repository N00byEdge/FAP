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

    EXPECT_FALSE(fap.getState().first->empty());
    EXPECT_TRUE(fap.getState().second->empty());
  }

  {
    FAP::FastAPproximation fap;

    
    fap.addUnitPlayer1(
      testUnit(BWAPI::UnitTypes::Terran_Marine)
      .setPosition({ 0, 0 })
    );

    for (int i = 0; i < 2; ++i)
      fap.addUnitPlayer2(
        testUnit(BWAPI::UnitTypes::Terran_Marine)
        .setPosition({ 0, 0 })
      );

    fap.simulate(-1);

    EXPECT_TRUE(fap.getState().first->empty());
    EXPECT_FALSE(fap.getState().second->empty());
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

  EXPECT_FALSE(fap.getState().first->empty());
  EXPECT_TRUE(fap.getState().second->empty());
}
