/**
 * @file ModeGameover.cpp
 * @brief ˆ—
 * @author ã’J‹±j
 * @date 2020 / 08 / 25
 */

#pragma once

#include "appframe.h"


class ModeGameover : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:

	int _bg;
	int _start;		// ¦‚P
	int _startpad;	// ¦‚P
};
