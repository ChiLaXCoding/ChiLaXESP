#pragma once

//
//  trigger.hpp
//
//  Created by ChiLaX on 23/5/17.
//  Copyright © 2017 ChiLaXSoft. All rights reserved.
//

#include "stdafx.h"
#include "process.hpp"
#include "module.hpp"
#include "playerList.hpp"

class CrosshairESP
{
public:
	CrosshairESP(Process* process, Module* module, PlayerList* playerList);

	boolean AcquireBaseAddress();
	boolean AppliedCrosshairESP(boolean beeping, boolean triggering);
	int CurrentTarget();
private:
	Process* process;
	Module* module;
	PlayerList* playerList;
	Player* localPlayer;
	int targetId;

	/*
	* CE: aim at another player with the crosshair and search for his entity list index (entity base + 0x64)
	* aim somewhere else and search for changed value, repeat
	* base address = player base address
	*/
	DWORD targetIDOffset = 0xB2B4;
};