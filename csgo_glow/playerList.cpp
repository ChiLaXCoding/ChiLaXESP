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
	this->list = new Player*[size];

	for (int i = 0; i < this->size; i++) {
		this->list[i] = new Player(process, module, playerBaseOffset + (16 * i));

		this->list[i]->Alive();
	}
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
			printf("Player #%d:", count);
			this->list[i]->ToConsole();
			count++;
		}
	}
}

boolean PlayerList::PlayerAliveAndEnemy(int index, int myTeamNumber) {
	return (this->list[index]->Alive() && (myTeamNumber != this->list[index]->TeamNumber()));
}

int PlayerList::PlayerGlowIndex(int index) {
	return this->list[index]->GlowIndex();
}