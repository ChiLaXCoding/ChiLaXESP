//
//  module.cpp
//
//  Created by ChiLaX on 23/5/17.
//  Copyright © 2017 ChiLaXSoft. All rights reserved.
//

#include "stdafx.h"
#include "module.hpp"

Module::Module(Process* process, WCHAR* moduleName) {
	this->process = process;
	this->moduleName = moduleName;
}

boolean Module::AcquiredBytes() {
	MODULEENTRY32 moduleEntry = this->process->ModuleEntryByName(moduleName);

	this->baseAddress = (DWORD)moduleEntry.modBaseAddr;
	//dwSize is too small and modBaseSize is way too large
	this->size = 0x500000;
	this->bytes = new BYTE[this->size];

	wprintf(L"Module %s base address: 0x%x\n", this->moduleName, this->baseAddress);
	wprintf(L"Module %s size: 0x%x\n", this->moduleName, this->size);
	wprintf(L"Module %s should end at: 0x%x\n\n", this->moduleName, this->baseAddress + this->size);

	for (DWORD i = 0; i < this->size; i++) {
		DWORD dword = process->ValueAtAddress<DWORD>(this->baseAddress + i);
		this->bytes[i] = dword & 0xff; 
		this->bytes[i + 1] = (dword >> 8) & 0xff; 
		this->bytes[i + 2] = (dword >> 16) & 0xff;
		this->bytes[i + 3] = (dword >> 24) & 0xff;(dword >> 24) & 0xff;
		i += 3;
	}

	return true;
}

DWORD Module::GetOffsetAtSignature(BYTE* signature, char* mask, DWORD offset) {
	DWORD fileOffset = this->FirstOffsetOfSignature(signature, mask, (int)strlen(mask));
	DWORD signatureAddress = fileOffset + this->baseAddress + offset;
	DWORD foundOffset = this->process->ValueAtAddress<DWORD>((DWORD)signatureAddress) - this->baseAddress;

	return foundOffset;
}

DWORD Module::BaseAddress() {
	return this->baseAddress;
}

boolean Module::MaskCheck(int nOffset, BYTE* btPattern, const char * strMask, int sigLength)
{
	for (int i = 0; i < sigLength; i++)
	{
		if (strMask[i] == '?')
		{
			continue;
		}

		if ((strMask[i] == 'x') && (btPattern[i] != bytes[nOffset + i]))
		{
			return false;
		}
	}

	return true;
}

DWORD Module::FirstOffsetOfSignature(BYTE* pSignature, const char * pMask, int sigLength)
{
	for (unsigned int i = 0; i < this->size; i++)
	{
		if (MaskCheck(i, pSignature, pMask, sigLength))
		{
			return i;
		}
	}

	return NULL;
}