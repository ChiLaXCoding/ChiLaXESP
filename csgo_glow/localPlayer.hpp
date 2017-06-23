#pragma once

//
//  localPlayer.hpp
//
//  Created by ChiLaX on 23/5/17.
//  Copyright © 2017 ChiLaXSoft. All rights reserved.
//

#include "stdafx.h"
#include "process.hpp"
#include "module.hpp"

class LocalPlayer
{
public:
	LocalPlayer(Process* process, Module* module);

	boolean AcquiredInfos();
	DWORD TeamNumber();
private:
	Process* process;
	Module* module;
	int teamNumber;

	/*
	* 00AADFFC
	* 04A8A684
	* 04ED522C
	* 04F1FDE4
	* Health at Offset 0xFC
	*/
	DWORD localPlayerOffset = 0x00AADFFC;
};