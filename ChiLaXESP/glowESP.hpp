#pragma once

//
//  glow.hpp
//
//  Created by ChiLaX on 23/5/17.
//  Copyright © 2017 ChiLaXSoft. All rights reserved.
//

#include "stdafx.h"
#include "process.hpp"
#include "module.hpp"
#include "playerList.hpp"

class GlowESP
{
public:
	GlowESP(Process* process, Module* module, PlayerList* playerList);

	boolean AcquireBaseAddress();
	boolean AppliedGlow();
private:
	Process* process;
	Module* module;
	PlayerList* playerList;
	Player* localPlayer;

	DWORD glowObjectBaseAddress;

	/*
	* CE: search for the base address of one player entity
	* next to the value there have to be at least 4 zeroes
	* 04FA7660
	* 04FA7670
	*/
	DWORD glowObjectOffset = 0x04FA7660;
	DWORD rOffset = 0x4;
	DWORD gOffset = 0x8;
	DWORD bOffset = 0xC;
	DWORD alphaOffset = 0x10;
	DWORD shouldGlowOffset = 0x24;
	DWORD otherBoolOffset = 0x25;

	DWORD glowEntitySize = 0x38;

	float red_r = 0.4f;
	float red_g = 0.0f;
	float red_b = 0.0f;
	float alpha = 1.0f;
};