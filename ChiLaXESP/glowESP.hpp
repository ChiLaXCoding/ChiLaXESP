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

	DWORD glowObjectOffset;
	DWORD glowObjectBaseAddress;

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

	/*
	* CE: search for the base address of one player entity
	* next to the value there have to be at least 4 zeroes
	* 04FA7660
	* 04FA7670
	* Find out what accesses this pointer and use the opcodes that have less frequent calls. 
	* Go to the first one and look at the call above. 
	* The base offset will can be found a bit further down, and this memory region is usable as an AoB.
	*/
	//0F 11 05 ? ? ? ? 83 C8 01 C7 05 ? ? ? ? 00 00 00 00 0F 28 05
	BYTE* playerListOffsetAoB = (BYTE*)"\x0F\x11\x05\x00\x00\x00\x00\x83\xC8\x01\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\x0F\x28\x05";
	char* playerListOffsetMask = "xxx????xxxxx????xxxxxxx";
	DWORD playerListOffsetOffset = 0x3;
};