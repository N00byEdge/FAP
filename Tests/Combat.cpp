#include "TestUnit.hpp"

#include "gtest/gtest.h"

#include <array>
#include <utility>

TEST(Combat, MarineTwoOnOne) {
	{
		FAP::FastAPproximation<> fap;

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
	FAP::FastAPproximation<> fap;

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
	FAP::FastAPproximation<> fap;

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
	FAP::FastAPproximation<> fap;

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

TEST(Combat, StackedTank) {
	FAP::FastAPproximation<> fap;

	fap.addUnitPlayer1(
		testUnit(BWAPI::UnitTypes::Protoss_Dragoon)
		.setPosition({ 0, 0 })
	);

	fap.addUnitPlayer2(
		testUnit(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode)
		.setPosition({ 0, 0 })
	);

	fap.simulate(-1);

	EXPECT_FALSE(fap.getState().first->empty());
	EXPECT_TRUE(fap.getState().second->empty());
}

TEST(Combat, NonStackedTank) {
	FAP::FastAPproximation<> fap;

	fap.addUnitPlayer1(
		testUnit(BWAPI::UnitTypes::Protoss_Dragoon)
		.setPosition({ 0, 0 })
	);

	fap.addUnitPlayer2(
		testUnit(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode)
		.setPosition({ 1000, 0 })
	);

	fap.simulate(-1);

	EXPECT_TRUE(fap.getState().first->empty());
	EXPECT_FALSE(fap.getState().second->empty());
}

template<bool tankSplash, int maxDistanceBetweenUnits>
int testTanks() {
	FAP::FastAPproximation<> fap;

	// Assumes the size of the map is at least 64 x 64
	for (int i = 0; i < 2; ++i)
		fap.addUnitPlayer1(
			testUnit(BWAPI::UnitTypes::Zerg_Zergling)
			.setPosition({ 1392, 992 + maxDistanceBetweenUnits * i })
		);

	fap.addUnitPlayer2(
		testUnit(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode)
		.setPosition({ 992, 992 })
	);
	
	fap.simulate<tankSplash>(-1);
	
	int splashedLingRemainingHealth;
	if constexpr (tankSplash) {
		if constexpr(maxDistanceBetweenUnits <= 20)
			splashedLingRemainingHealth = 0;
		else if constexpr(maxDistanceBetweenUnits <= 50)
			splashedLingRemainingHealth = 23;
		else if constexpr(maxDistanceBetweenUnits <= 80)
			splashedLingRemainingHealth = 32;
		else
			splashedLingRemainingHealth = 35;
	}
	else
		splashedLingRemainingHealth = 35;

	// check which player wins/loses
	EXPECT_EQ(fap.getState().first->empty(), tankSplash && maxDistanceBetweenUnits <= 20);
	EXPECT_EQ(fap.getState().second->empty(), !tankSplash || tankSplash && maxDistanceBetweenUnits > 20);

	// check actual splash damage dealt (a function of maxDistanceBetweenUnits)
	EXPECT_EQ(fap.getState().first->front().health >> 8, splashedLingRemainingHealth);
	return 1;
}

template<bool tankSplash, typename T, T... I>
std::array<T, sizeof...(I)> run_testTanks(std::integer_sequence<T, I...>)
{
	return{ testTanks<tankSplash, I>()... };
}

TEST(Combat, OneTankOnTwoLings) {
	auto radiiSeq = std::integer_sequence<int, 20, 50, 80, 100>();
	
	run_testTanks<true>(radiiSeq);
	run_testTanks<false>(radiiSeq);
}
