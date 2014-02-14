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

#include "ExtraMusic.h"

namespace OpenXcom
{

/**
 * Creates a blank set of extra music data.
 */
ExtraMusic::ExtraMusic() : _modIndex(0)
{
}

/**
 * Cleans up the extra music set.
 */
ExtraMusic::~ExtraMusic()
{
}

/**
 * Loads the extra music set from YAML.
 * @param node YAML node.
 * @param modIndex The internal index of the associated mod.
 */
void ExtraMusic::load(const YAML::Node &node, int modIndex)
{
	_media = node["media"].as<std::string>(_media);
	if (node["overrides"])
	  _overrides = node["overrides"].as<std::string>(_overrides);
	if (node["extends"])
	  _extends = node["extends"].as<std::string>(_extends);  
	_terrains = node["terrain"].as< std::map<int, std::string> >(_terrains);
	_modIndex = modIndex;
}

/**
 * Gets the list of tracks defined by this mod.
 * @return The list of tracks defined by this mod.
 */
std::map<int, std::string> *ExtraMusic::getMusic()
{
	return &_terrains;
}

/**
 * Gets the mod index for this external music set.
 * @return The mod index for this external music set.
 */
int ExtraMusic::getModIndex()
{
	return _modIndex;
}
}
