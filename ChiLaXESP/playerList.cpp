//
//  localPlayer.cpp
//
//  Created by ChiLaX on 23/5/17.
//  Copyright © 2017 ChiLaXSoft. All rights reserved.
//

#include "stdafx.h"
#include "playerList.hpp"

PlayerList::PlayerList(Process* process, Module* module, int size) {
	this->process = process;
	this->module = module;
	this->size = size;
}

boolean PlayerList::PlayersInitialized() {
	this->list = new Player*[size];

	this->playerListOffset = module->GetOffsetAtSignature(this->playerListOffsetAoB, this->playerListOffsetMask, playerListOffsetOffset);

	if ((this->playerListOffset < 0) || (this->playerListOffset > 0x10000000)) {
		return false;
	}

	for (int i = 0; i < this->size; i++) {
		this->list[i] = new Player(process, module, playerListOffset + (16 * (i + 1)));

		this->list[i]->Alive();
	}

	return true;
}

int PlayerList::Size() {
	return this->size;
}

Player* PlayerList::LocalPlayer() {
	
	return this->list[0];
}

void PlayerList::ActivePlayersToConsole() {
	int count = 1;
	for (int i = 0; i < this->size; i++) {
		if (this->list[i]->Alive()) {
			this->list[i]->ToConsole();
			count++;
		}
	}
}

boolean PlayerList::PlayerAliveAndEnemy(int index, int myTeamNumber) {
	return (this->list[index]->Alive() && (myTeamNumber != this->list[index]->TeamNumber()));
}

boolean PlayerList::EntityIdAliveAndEnemy(int id, int myTeamNumber) {
	for (int i = 0; i < size; i++) {
		if (!this->list[i]->EntityId())
			return false;
		if (this->list[i]->EntityId() == id) {
			if (this->list[i]->TeamNumber() != myTeamNumber) {
				return true;
			}
			break;
		}
	}

	return false;
}

int PlayerList::PlayerGlowIndex(int index) {
	return this->list[index]->GlowIndex();
}