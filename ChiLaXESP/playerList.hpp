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

	int Size();
	Player* LocalPlayer();
	void ActivePlayersToConsole();
	boolean PlayerAliveAndEnemy(int index, int myTeamNumber);
	boolean EntityIdAliveAndEnemy(int id, int myTeamNumber);
	int PlayerGlowIndex(int index);
private:
	Process* process;
	Module* module;
	int size;
	Player** list;

	/*
	* CE: search for own health value and use "hurtme x" command in developer console
	* next to value is a position value which is 257 normally, and changes when you duck
	* before the health value is 2x team number
	* This address -FC must be the player base, pointer scan for the base address must deliver 4 pointers from client.dll
	* 00AADFFC
	* 04A8A654
	* 04ED51FC
	* 04F1FDB4
	*/
	DWORD playerBaseOffset = 0x04A8A654;
};