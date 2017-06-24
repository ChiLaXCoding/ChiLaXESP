#pragma once

//
//  player.hpp
//
//  Created by ChiLaX on 23/5/17.
//  Copyright © 2017 ChiLaXSoft. All rights reserved.
//

#include "process.hpp"
#include "module.hpp"

class Player
{
public:
	Player(Process* process, Module* module, DWORD playerBaseOffset);

	boolean Alive();
	int PlayerBaseAddress();
	int EntityId();
	int TeamNumber();
	int GlowIndex();
	float* Position();
	void ToConsole();
private:
	Process* process;
	Module* module;
	int entityId, teamNumber, health, glowIndex;
	float* viewAngle;
	float* position;
	DWORD playerBaseAddress;

	DWORD playerBaseOffset;
	DWORD entityIdOffset = 0x64;
	DWORD teamNumberOffset = 0xF0;
	DWORD healthOffset = 0xFC;
	DWORD viewAngleXOffset = 0x128;
	DWORD viewAngleYOffset = viewAngleXOffset + 0x4;
	DWORD viewAngleZOffset = viewAngleYOffset + 0x4;
	DWORD positionXOffset = 0x134;
	DWORD positionYOffset = positionXOffset + 0x4;
	DWORD positionZOffset = positionYOffset + 0x4;
	DWORD glowIndexOffset = 0xA320;
};