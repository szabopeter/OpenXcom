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
#ifndef OPENXCOM_MEDALSINFOSTATE_H
#define OPENXCOM_MEDALSINFOSTATE_H

#include "../Engine/State.h"

namespace OpenXcom
{

class TextButton;
class Window;
class Text;
class TextList;
class Base;

/**
 * Medals screen that lets the player
 * see all the medals a soldier has.
 */
class MedalsInfoState : public State
{
private:
	std::vector<int> _medalListEntry;
	Base *_base;
	std::wstring _medalName;
	size_t _soldier;
	TextButton *_btnOk;
	Window *_window;
	Text *_txtMedalName, *_txtMedalLevel, *_txtMedalInfoTitle, *_txtMedalInfo;
	int _rowEntry;
public:
	/// Creates the Soldiers state.
	MedalsInfoState(Base *base, Game *game, int rowEntry, size_t soldier, std::vector<int> medalListEntry);
	/// Cleans up the Soldiers state.
	~MedalsInfoState();
	/// Handler for clicking the OK button.
	void btnOkClick(Action *action);
};

}

#endif
