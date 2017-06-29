//
//  trigger.cpp
//
//  Created by ChiLaX on 23/5/17.
//  Copyright © 2017 ChiLaXSoft. All rights reserved.
//

#include "stdafx.h"
#include "crosshairESP.hpp"


CrosshairESP::CrosshairESP(Process* process, Module* module, PlayerList* playerList) {
	this->process = process;
	this->module = module;
	this->playerList = playerList;
	this->localPlayer = this->playerList->LocalPlayer();
}

boolean CrosshairESP::AcquireBaseAddress() {
	this->targetId = this->process->ValueAtAddress<DWORD>(this->localPlayer->PlayerBaseAddress() + this->targetIDOffset);

	if ((this->targetId < 0) || (this->targetId > 64)) {
		return false;
	}

	return true;
}

boolean CrosshairESP::AppliedCrosshairESP(boolean beeping, boolean triggering) {
	if (this->process->Alive()) {
		if (beeping || triggering) {
			this->targetId = this->process->ValueAtAddress<DWORD>(this->localPlayer->PlayerBaseAddress() + this->targetIDOffset);

			if (this->playerList->EntityIdAliveAndEnemy(this->targetId, this->localPlayer->TeamNumber())) {
				if (beeping) {
					Beep(1175, 200);
				}

				if (triggering) {
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					Sleep(1);
					mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				}
			}
		}
	}
	
	return true;
}

int CrosshairESP::CurrentTarget() {
	return this->targetId;
}