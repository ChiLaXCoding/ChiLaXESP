#pragma once

//
//  localPlayer.hpp
//
//  Created by ChiLaX on 23/5/17.
//  Copyright © 2017 ChiLaXSoft. All rights reserved.
//

#include "stdafx.h"
#include "process.hpp"
#include "module.hpp"

class Player
{
public:
	Player(Process* process, Module* module, DWORD playerBaseOffset);

	boolean Alive();
	int TeamNumber();
	int GlowIndex();
	void ToConsole();
private:
	Process* process;
	Module* module;
	int teamNumber, health, dormant, glowIndex;
	
	DWORD playerBaseOffset;
	DWORD teamNumberOffset = 0xF0;
	DWORD healthOffset = 0xFC;
	DWORD dormantOffset = 0xE9;
	DWORD glowIndexOffset = 0xA320;
};