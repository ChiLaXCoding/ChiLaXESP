//
//  process.cpp
//
//  Created by ChiLaX on 23/5/17.
//  Copyright © 2017 ChiLaXSoft. All rights reserved.
//

#include "stdafx.h"
#include "process.hpp"

Process::Process(WCHAR* processName) {
	this->processName = processName;
}

boolean Process::AcquiredHandle() {
		HANDLE hSnapProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		PROCESSENTRY32 processEntry;
		processEntry.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(hSnapProcess, &processEntry))
		{
			do
			{
				if (!wcscmp(processEntry.szExeFile, processName))
				{
					this->pid = processEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnapProcess, &processEntry));
		}

		CloseHandle(hSnapProcess);

		if (this->pid != 0)
		{
			this->handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->pid);
			return true;
		}

		return false;
}

boolean Process::Alive() {
	DWORD exitCode;
	GetExitCodeProcess(this->handle, &exitCode);
	return (exitCode == STILL_ACTIVE);
}

MODULEENTRY32 Process::ModuleEntryByName(WCHAR* moduleName) {
	HANDLE hSnapModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	MODULEENTRY32 moduleEntry;
	moduleEntry.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(hSnapModule, &moduleEntry))
	{
		do
		{
			if (!wcscmp(moduleEntry.szModule, moduleName))
			{
				CloseHandle(hSnapModule);
				return moduleEntry;
			}
		} while (Module32Next(hSnapModule, &moduleEntry));
	}

	CloseHandle(hSnapModule);
	moduleEntry.modBaseAddr = 0x0;
	return moduleEntry;
}