/*
 * Copyright 2010-2013 OpenXcom Developers.
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OPENXCOM_SOLDIERMEDALS_H
#define OPENXCOM_SOLDIERMEDALS_H

#include "Soldier.h"
#include <string>
#include "../Ruleset/Unit.h"

namespace OpenXcom
{

enum SoldierMedal { NO_MEDAL_NAME, MEDAL_MERIT_STAR, MEDAL_MILITARY_CROSS, MEDAL_SERVICE_MEDAL, MEDAL_HONOR_CROSS, MEDAL_XENOCIDE_MEDAL, MEDAL_DEFENDER_MEDAL, MEDAL_CAMPAIGN_MEDAL, LAST_SOLDIER_MEDAL };
enum MedalLevel { NO_MEDAL_LEVEL, MEDAL_FIRST_AWARD, MEDAL_SECOND_AWARD, MEDAL_THIRD_AWARD, MEDAL_FOURTH_AWARD, MEDAL_FIFTH_AWARD,
		MEDAL_SIXTH_AWARD, MEDAL_SEVENTH_AWARD, MEDAL_EIGHTH_AWARD, MEDAL_NINTH_AWARD, MEDAL_TENTH_AWARD, LAST_AWARD_LEVEL};
enum SoldierStats { STAT_NONE, STAT_KILLS, STAT_MISSIONS, LAST_STAT};
//enum SoldierRank { RANK_ROOKIE, RANK_SQUADDIE, RANK_SERGEANT, RANK_CAPTAIN, RANK_COLONEL, RANK_COMMANDER};

class UnitStats;
class GameTime;
class Ruleset;
class RuleSoldier;

class SoldierMedals
{
private:
	static int killCheck[LAST_AWARD_LEVEL];
	static int missionCheck[LAST_AWARD_LEVEL];
	static int raceKillCheck;
	static int missionsByRegionCheck;
	static int missionsByTypeCheck[LAST_AWARD_LEVEL];
protected:
	std::map<int, std::pair<int, bool> > _medals; // Medal Name, Medal Level, New? T/F
	UnitStats _currentStats;
	int _missions, _recovery, _monthsService;
    int _killsTotal;
	std::map<std::string, int> _killsByRace, _killsByRank, _killsWithWeapon, _stunsWithWeapon;
	std::map<std::string, int> _missionsByRegion, _missionsByType, _missionsByUFO;
	std::pair<int, int> _birthMonthYear;
	GameTime *_date;
	RuleSoldier *_rules;
	SoldierRank _rank;

public:
	/// Puts togther the medals
	SoldierMedals();
	~SoldierMedals();
	/// Gets a specific medal.
	std::map<int, std::pair<int, bool> >  & getMedal();
	/// Gets a string version of the soldier's medal's name.
	static std::string getMedalNameString(int);
	/// Gets a string version of the soldier's medal's description.
	static std::string getMedalDescriptionString(int);
	/// Gets a string version of the soldier's medal's award level.
	static std::string getMedalAwardLevelString(int);
	/// Gets a string version of the soldier's medal's decoration level.
	static std::string getMedalDecorationLevelString(int);
	/// Award medals that are month related if the soldier is eligible.
	bool awardMedalMonthly();
	/// Award medals if the soldier is eligible.
	bool awardMedal();
};

}

#endif
