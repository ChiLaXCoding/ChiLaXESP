#pragma once

//
//  process.hpp
//
//  Created by ChiLaX on 23/5/17.
//  Copyright © 2017 ChiLaXSoft. All rights reserved.
//

#include "stdafx.h"

class Process
{
public:
	Process(WCHAR* processName);

	boolean AcquiredHandle();
	boolean Alive();

	template<class c>
	c ValueAtAddress(DWORD dwAddress)
	{
		c val;
		ReadProcessMemory(this->handle, (LPVOID)dwAddress, &val, sizeof(c), NULL);
		return val;
	}

	template<class c>
	BOOL WriteSuccessful(DWORD dwAddress, c valueToWrite)
	{
		return WriteProcessMemory(this->handle, (LPVOID)dwAddress, &valueToWrite, sizeof(c), NULL);
	}

	MODULEENTRY32 ModuleEntryByName(WCHAR* moduleName);
private:
	WCHAR* processName;
	DWORD pid;
	HANDLE handle;
};