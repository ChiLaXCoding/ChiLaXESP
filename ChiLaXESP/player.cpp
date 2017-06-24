//
//  player.cpp
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
	this->viewAngle = new float[3];
	this->position = new float[3];
}

int Player::PlayerBaseAddress() {
	return this->playerBaseAddress;
}

int Player::EntityId() {
	return this->entityId;
}

boolean Player::Alive() {
	this->playerBaseAddress = this->process->ValueAtAddress<DWORD>(this->module->BaseAddress() + this->playerBaseOffset);

	if (!this->playerBaseAddress)
		return false;

	this->entityId = this->process->ValueAtAddress<int>((DWORD)(this->playerBaseAddress + entityIdOffset));
	this->teamNumber = this->process->ValueAtAddress<int>((DWORD)(this->playerBaseAddress + teamNumberOffset));
	this->health = this->process->ValueAtAddress<int>((DWORD)(this->playerBaseAddress + healthOffset));
	this->viewAngle[0] = this->process->ValueAtAddress<float>((DWORD)(this->playerBaseAddress + viewAngleXOffset));
	this->viewAngle[1] = this->process->ValueAtAddress<float>((DWORD)(this->playerBaseAddress + viewAngleYOffset));
	this->viewAngle[2] = this->process->ValueAtAddress<float>((DWORD)(this->playerBaseAddress + viewAngleZOffset));
	this->position[0] = this->process->ValueAtAddress<float>((DWORD)(this->playerBaseAddress + positionXOffset));
	this->position[1] = this->process->ValueAtAddress<float>((DWORD)(this->playerBaseAddress + positionYOffset));
	this->position[2] = this->process->ValueAtAddress<float>((DWORD)(this->playerBaseAddress + positionZOffset));
	this->glowIndex = this->process->ValueAtAddress<int>((DWORD)(this->playerBaseAddress + glowIndexOffset));

	if ((this->teamNumber != 2) && (this->teamNumber != 3))
		return false;

	if ((this->health <= 0) || (this->health > 100))
		return false;

	return true;
}

int Player::TeamNumber() {
	return this->teamNumber;
}

int Player::GlowIndex() {
	return this->glowIndex;
}

float* Player::Position() {
	return this->position;
}

void Player::ToConsole() {
	if ((this->teamNumber == 2) || (this->teamNumber == 3)) {
		printf("Team: %d Health: %d View Angle: %f %f %f Position: %f %f %f\n", this->teamNumber, this->health,
			this->viewAngle[0], this->viewAngle[1], this->viewAngle[2],
			this->position[0], this->position[1], this->position[2]);
	}
}