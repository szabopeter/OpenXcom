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
#include "SoldierMedals.h"
#include "Soldier.h"
#include "../Engine/Language.h" // Maybe?
#include "GameTime.h"
#include "../Ruleset/RuleSoldier.h"
#include "../Ruleset/Ruleset.h"

namespace OpenXcom
{

/**
 * Medal achievements. If a medal matches this criteria, it is awarded.
 */
int SoldierMedals::killCheck[LAST_AWARD_LEVEL] = {1, 2, 3, 8, 12, 16, 20, 25, 30, 35, -1};
int SoldierMedals::missionCheck[LAST_AWARD_LEVEL] = {1, 3, 4, 5, 12, 16, 20, 25, 30, 35, -1};
int SoldierMedals::raceKillCheck = 1;
int SoldierMedals::missionsByRegionCheck = 1;
int SoldierMedals::missionsByTypeCheck[LAST_AWARD_LEVEL] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -1};

SoldierMedals::SoldierMedals()
{
	// Empty by design
}

SoldierMedals::~SoldierMedals()
{
	// Empty by design
}

/**
 * Return _medals.
 */
std::map<int, std::pair<int, bool> >  & SoldierMedals::getMedal()
{
	return _medals;
}

/**
 * Returns a localizable-string representation of
 * the soldier's medal name.
 * @return String ID for medal name.
 */
std::string SoldierMedals::getMedalNameString(int medalName)
{
	switch (medalName)
	{
	case MEDAL_MERIT_STAR:		return "STR_MEDAL_MERIT_STAR_NAME";
	case MEDAL_MILITARY_CROSS:	return "STR_MEDAL_MILITARY_CROSS_NAME";
	case MEDAL_SERVICE_MEDAL:	return "STR_MEDAL_SERVICE_MEDAL_NAME";
	case MEDAL_HONOR_CROSS:		return "STR_MEDAL_HONOR_CROSS_NAME";
	case MEDAL_XENOCIDE_MEDAL:	return "STR_MEDAL_XENOCIDE_MEDAL_NAME";
	case MEDAL_DEFENDER_MEDAL:	return "STR_MEDAL_DEFENDER_MEDAL_NAME";
	case MEDAL_CAMPAIGN_MEDAL:	return "STR_MEDAL_CAMPAIGN_MEDAL_NAME";

	case NO_MEDAL_NAME:			return "???";
	default: return "NAME ERROR";
	}
	return "";
}

/**
 * Returns a localizable-string representation of
 * the soldier's medal description.
 * @return String ID for medal description.
 */
std::string SoldierMedals::getMedalDescriptionString(int medalName)
{
	switch (medalName)
	{
	case MEDAL_MERIT_STAR:		return "STR_MEDAL_MERIT_STAR_DESCRIPTION";
	case MEDAL_MILITARY_CROSS:	return "STR_MEDAL_MILITARY_CROSS_DESCRIPTION";
	case MEDAL_SERVICE_MEDAL:	return "STR_MEDAL_SERVICE_MEDAL_DESCRIPTION";
	case MEDAL_HONOR_CROSS:		return "STR_MEDAL_HONOR_CROSS_DESCRIPTION";
	case MEDAL_XENOCIDE_MEDAL:	return "STR_MEDAL_XENOCIDE_MEDAL_DESCRIPTION";
	case MEDAL_DEFENDER_MEDAL:	return "STR_MEDAL_DEFENDER_MEDAL_DESCRIPTION";
	case MEDAL_CAMPAIGN_MEDAL:	return "STR_MEDAL_CAMPAIGN_MEDAL_DESCRIPTION";

	case NO_MEDAL_NAME:			return "???";
	default: return "DESCRIPTION ERROR";
	}
	return "";
}

/**
 * Returns a localizable-string representation of
 * the soldier's medal award level.
 * @return String ID for medal pin award.
 */
std::string SoldierMedals::getMedalAwardLevelString(int medalLevel)
{
	switch (medalLevel)
	{
		case NO_MEDAL_LEVEL:		return "???"		   ;
		case MEDAL_FIRST_AWARD:		return "STR_1ST_AWARD" ;
		case MEDAL_SECOND_AWARD:	return "STR_2ND_AWARD" ;
		case MEDAL_THIRD_AWARD:		return "STR_3RD_AWARD" ;
		case MEDAL_FOURTH_AWARD:	return "STR_4TH_AWARD" ;
		case MEDAL_FIFTH_AWARD:		return "STR_5TH_AWARD" ;
		case MEDAL_SIXTH_AWARD:		return "STR_6TH_AWARD" ;
		case MEDAL_SEVENTH_AWARD:	return "STR_7TH_AWARD" ;
		case MEDAL_EIGHTH_AWARD:	return "STR_8TH_AWARD" ;
		case MEDAL_NINTH_AWARD:		return "STR_9TH_AWARD" ;
		case MEDAL_TENTH_AWARD:		return "STR_10TH_AWARD";

		default: return "AWARD LEVEL ERROR";
	}
	return "";
}

/**
 * Returns a localizable-string representation of
 * the soldier's medal award level.
 * @return String ID for medal decoration level.
 */
std::string SoldierMedals::getMedalDecorationLevelString(int medalLevel)
{
	switch (medalLevel)
	{
		case NO_MEDAL_LEVEL:		return "???"				 ;
		case MEDAL_FIRST_AWARD:		return "STR_1ST_AWARD_DECOR" ;
		case MEDAL_SECOND_AWARD:	return "STR_2ND_AWARD_DECOR" ;
		case MEDAL_THIRD_AWARD:		return "STR_3RD_AWARD_DECOR" ;
		case MEDAL_FOURTH_AWARD:	return "STR_4TH_AWARD_DECOR" ;
		case MEDAL_FIFTH_AWARD:		return "STR_5TH_AWARD_DECOR" ;
		case MEDAL_SIXTH_AWARD:		return "STR_6TH_AWARD_DECOR" ;
		case MEDAL_SEVENTH_AWARD:	return "STR_7TH_AWARD_DECOR" ;
		case MEDAL_EIGHTH_AWARD:	return "STR_8TH_AWARD_DECOR" ;
		case MEDAL_NINTH_AWARD:		return "STR_9TH_AWARD_DECOR" ;
		case MEDAL_TENTH_AWARD:		return "STR_10TH_AWARD_DECOR";

		default: return "DECORATION LEVEL ERROR";
	}
	return "";
}

/**
 * Award the soldier one or many medals from a list of possibilities.
 * These medals are not earned in combat.
 * Return True if a medal was recently awarded, False otherwise.
 */
bool SoldierMedals::awardMedalMonthly()
{
	bool _recentlyMedalled = false;
	int m;
	_monthsService++;

	/**
	 * Honor Cross - Given to every soldier once.
	 */
	m = MEDAL_HONOR_CROSS;
	if (_medals.find(m) == _medals.end())
	{
		_medals[m].first++;
		_medals[m].second = true;
		// No bonus
		_recentlyMedalled = true;
	}

	/**
	 * Service Medal - Based on soldier service time.
	 */
	m = MEDAL_SERVICE_MEDAL;
	if (_monthsService % 6 == 0 && _medals[m].first < LAST_AWARD_LEVEL)
	{
		_medals[m].first++;
		_medals[m].second = true;
		_currentStats.bravery += 1; // I am not sure this does what I think it does
		_recentlyMedalled = true;
	}

	return _recentlyMedalled;
		
}

/**
 * Award the soldier one or many medals from a list of possibilities.
 * Return True if a medal was recently awarded, False otherwise.
 */
bool SoldierMedals::awardMedal()
{
	if (_rank == RANK_ROOKIE) return false;

	bool _recentlyMedalled = false;
	int m;
	int balanceCheck;
	
	/**
	 * Merit Star - Based on kill count.
	 */
	m = MEDAL_MERIT_STAR;
	for (int level = NO_MEDAL_LEVEL ; level != LAST_AWARD_LEVEL ; ++level)
		if (_killsTotal >= killCheck[level] && _medals[m].first == level)
		{
			_medals[m].first++;
			_medals[m].second = true;
			// _currentStats.tu += 1;
			if (_currentStats.tu < 100) _currentStats.tu += 1;
			_recentlyMedalled = true;
		}
	
	/**
	 * Xenocide medal - Based on race kills count.
	 */
	m = MEDAL_XENOCIDE_MEDAL;
	balanceCheck = 0;
	for(std::map<std::string, int>::const_iterator i = _killsByRace.begin(); i != _killsByRace.end() ; i++)
		if (i->second > raceKillCheck) balanceCheck++;
	if (_medals[m].first < balanceCheck)
	{
		_medals[m].first++;
		_medals[m].second = true;
		// No bonus yet
		_recentlyMedalled = true;
	}

	/**
	 * Military Cross - Based on mission count.
	 */
	m = MEDAL_MILITARY_CROSS;
	for (int level = NO_MEDAL_LEVEL ; level != LAST_AWARD_LEVEL ; ++level)
		if (_missions >= missionCheck[level] && _medals[m].first == level)
		{
			_medals[m].first++;
			_medals[m].second = true;
			// if (_currentStats.health < _rules->getStatCaps().health) _currentStats.health += 1;
			_recentlyMedalled = true;
		}

	/**
	 * Defender Medal - Given for a successful base defense.
	 */
	m = MEDAL_DEFENDER_MEDAL;
	for (int level = NO_MEDAL_LEVEL ; level != LAST_AWARD_LEVEL ; ++level)
		if (_missionsByType["STR_BASE_DEFENSE"] >= missionsByTypeCheck[level] && _medals[m].first == level)
		{
			_medals[m].first++;
			_medals[m].second = true;
			// No bonus yet
			_recentlyMedalled = true;
		}

	/**
	 * Campaign medal - Based on missions in certain countries.
	 */
	m = MEDAL_CAMPAIGN_MEDAL;
	balanceCheck = 0;
	for(std::map<std::string, int>::const_iterator i = _missionsByRegion.begin(); i != _missionsByRegion.end() ; i++)
		if (i->second >= missionsByRegionCheck) balanceCheck++;
	if (_medals[m].first < balanceCheck)
	{
		_medals[m].first++;
		_medals[m].second = true;
		// No bonus yet
		_recentlyMedalled = true;
	}

	return _recentlyMedalled;	
}

}
