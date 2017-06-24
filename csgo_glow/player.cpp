//
//  localPlayer.cpp
//
//  Created by ChiLaX on 23/5/17.
//  Copyright © 2017 ChiLaXSoft. All rights reserved.
//

#include "stdafx.h"
#include "player.hpp"

Player::Player(Process* process, Module* module, DWORD playerBaseOffset) {
	this->process = process;
	this->module = module;
	this->playerBaseOffset = playerBaseOffset;
}

boolean Player::Alive() {
	DWORD playerBaseAddress = this->process->ValueAtAddress<DWORD>(this->module->BaseAddress() + this->playerBaseOffset);

	this->teamNumber = this->process->ValueAtAddress<int>((DWORD)(playerBaseAddress + teamNumberOffset));
	this->health = this->process->ValueAtAddress<int>((DWORD)(playerBaseAddress + healthOffset));
	this->dormant = this->process->ValueAtAddress<int>((DWORD)(playerBaseAddress + dormantOffset));
	this->glowIndex = this->process->ValueAtAddress<int>((DWORD)(playerBaseAddress + glowIndexOffset));

	if ((this->teamNumber != 2) && (this->teamNumber != 3)) {
		return false;
	}

	if ((this->health <= 0) || (this->health > 100)) {
		return false;
	}

	return true;
}

void Player::ToConsole() {
	if ((this->teamNumber == 2) || (this->teamNumber == 3)) {
		printf("Team: %d Health: %d Dormant: %d\n", this->teamNumber, this->health, this->dormant);
	}
}

int Player::TeamNumber() {
	return this->teamNumber;
}

int Player::GlowIndex() {
	return this->glowIndex;
}