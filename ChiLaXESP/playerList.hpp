#pragma once

//
//  localPlayer.hpp
//
//  Created by ChiLaX on 23/5/17.
//  Copyright © 2017 ChiLaXSoft. All rights reserved.
//

#include "player.hpp"

class PlayerList
{
public:
	PlayerList(Process* process, Module* module, int size);

	boolean PlayersInitialized();
	int Size();
	Player* LocalPlayer();
	void ActivePlayersToConsole();
	boolean PlayerAliveAndEnemy(int index, int myTeamNumber);
	boolean EntityIdAliveAndEnemy(int id, int myTeamNumber);
	int PlayerGlowIndex(int index);
private:
	Process* process;
	Module* module;
	DWORD playerListOffset;
	int size;
	Player** list;

	/*
	* CE: Search for own health value and use "hurtme x" command in developer console.
	* Next to value is a position value which is 257 normally, and changes when you duck.
	* Before the health value is 2x team number.
	* The address -FC must be the player base, pointer scan for the base address must deliver 4 pointers from client.dll.
	*
	* example for local player offsets:
	* 00AADFFC
	* 04A8A654
	* 04ED51FC
	* 04F1FDB4
	*
	* Player List Offset = Local Player Offset - 0x10
	* Finding out what accesses one of these offsets delivers AoB source for the player list offset.
	*/
	//56 8B 89 ? ? ? ? 85 C9 74 ? 8B 01 FF 50 ? 8B F0 85 F6
	//alt1: 8B 88 ? ? ? ? 85 C9 74 ? 8B 01 8B 40 ? FF D0 8B C8
	//alt2: 8B 8A ? ? ? ? 85 C9 0F 84 ? ? ? ? 8B 01 FF 50 ? 89
	BYTE* playerListOffsetAoB = (BYTE*)"\x56\x8B\x89\x00\x00\x00\x00\x85\xC9\x74\x00\x8B\x01\xFF\x50\x00\x8B\xF0\x85\xF6";
	char* playerListOffsetMask = "xxx????xxx?xxxx?xxxx";
	DWORD playerListOffsetOffset = 0x3;
};