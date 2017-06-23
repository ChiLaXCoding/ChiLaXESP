#pragma once

//
//  glow.hpp
//
//  Created by ChiLaX on 23/5/17.
//  Copyright © 2017 ChiLaXSoft. All rights reserved.
//

#include "stdafx.h"
#include "process.hpp"
#include "module.hpp"

class Glow
{
public:
	Glow(Process* process, Module* module);

	
private:
	Process* process;
	Module* module;
};