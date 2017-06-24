//
//  glow.cpp
//
//  Created by ChiLaX on 23/5/17.
//  Copyright � 2017 ChiLaXSoft. All rights reserved.
//

#include "stdafx.h"
#include "glow.hpp"

Glow::Glow(Process* process, Module* module, PlayerList* playerList) {
	this->process = process;
	this->module = module;
	this->playerList = playerList;
	this->localPlayer = this->playerList->LocalPlayer();
}

boolean Glow::AcquireBaseAddress() {
	this->glowObjectBaseAddress = this->process->ValueAtAddress<DWORD>(this->module->BaseAddress() + glowObjectOffset);
	
	DWORD localPlayerPointerAddress = this->glowObjectBaseAddress + (this->glowEntitySize * this->playerList->PlayerGlowIndex(0));
	DWORD localPlayerBaseAddress = this->process->ValueAtAddress<DWORD>(localPlayerPointerAddress);

	if (localPlayerBaseAddress != this->localPlayer->PlayerBaseAddress()) {
		return false;
	}
	
	return true;
}

boolean Glow::AppliedGlow() {
	if (this->process->Alive()) {
		for (int i = 0; i < this->playerList->Size(); i++) {
			if (this->playerList->PlayerAliveAndEnemy(i, this->localPlayer->TeamNumber())) {
				DWORD glowEntityBaseAddress = this->glowObjectBaseAddress + (this->glowEntitySize * this->playerList->PlayerGlowIndex(i));
				if (!this->process->WriteSuccessful<float>(glowEntityBaseAddress + rOffset, red_r)) {
					return false;
				}
				if (!this->process->WriteSuccessful<float>(glowEntityBaseAddress + gOffset, red_g)) {
					return false;
				}
				if (!this->process->WriteSuccessful<float>(glowEntityBaseAddress + bOffset, red_b)) {
					return false;
				}
				if (!this->process->WriteSuccessful<float>(glowEntityBaseAddress + alphaOffset, alpha)) {
					return false;
				}
				if (!this->process->WriteSuccessful<bool>(glowEntityBaseAddress + shouldGlowOffset, true)) {
					return false;
				}
			}
		}
	}

	return true;
}