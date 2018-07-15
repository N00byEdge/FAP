#pragma once

#include "BWAPI.h"

#include "FAP.hpp"

struct Upgrades {
  int armorUpgrades = 0;
  int attackUpgrades = 0;
  int shieldUpgrades = 0;
  bool attackSpeedUpgrade = false;
  bool speedUpgrade = false;
  bool stimmed = false;
  bool rangeUpgrade = false;
};

auto inline testUnit(BWAPI::UnitType ut, Upgrades const &upgrades = {}) {
  return FAP::makeUnit()
    .setUnitType(ut)
    .setHealth(ut.maxHitPoints())
    .setShields(ut.maxShields())
    .setFlying(ut.isFlyer())
    .setScore(ut.buildScore())
    .setElevation()
    .setAttackerCount(ut == BWAPI::UnitTypes::Terran_Bunker ? 4 : 8)
    .setAttackCooldownRemaining()
    .setArmorUpgrades(upgrades.armorUpgrades)
    .setAttackUpgrades(upgrades.attackUpgrades)
    .setShieldUpgrades(upgrades.shieldUpgrades)
    .setSpeedUpgrade(upgrades.speedUpgrade)
    .setAttackSpeedUpgrade(upgrades.attackSpeedUpgrade)
    .setRangeUpgrade(upgrades.rangeUpgrade)
    .setStimmed(upgrades.stimmed)
  ;
}
