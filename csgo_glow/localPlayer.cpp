//
//  localPlayer.cpp
//
//  Created by ChiLaX on 23/5/17.
//  Copyright © 2017 ChiLaXSoft. All rights reserved.
//

#include "stdafx.h"
#include "localPlayer.hpp"

LocalPlayer::LocalPlayer(Process* process, Module* module) {
	this->process = process;
	this->module = module;
}

boolean LocalPlayer::AcquiredInfos() {
	/*
	UINT64 localPlayerOffset = this->module->PointerValueBySignature(
		(BYTE*)"\x89\xD6\x41\x89\x00\x49\x89\x00\x48\x8B\x1D\x00\x00\x00\x00\x48\x85\xDB\x74\x00",
		"xxxx?xx?xxx????xxxx?",
		0xB
	) + 0x4;
	*/

	UINT64 localPlayerBaseAddy = this->process->ValueAtAddress<UINT64>(this->module->BaseAddress() + localPlayerOffset);

	this->teamNumber = this->process->ValueAtAddress<int>((DWORD)(localPlayerBaseAddy + 0xF4));

	if ((this->teamNumber != 2) && (this->teamNumber != 3)) {
		return false;
	}

	return true;
}

DWORD LocalPlayer::TeamNumber() {
	return this->teamNumber;
}