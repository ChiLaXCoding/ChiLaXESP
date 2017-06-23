//
//  module.cpp
//
//  Created by ChiLaX on 23/5/17.
//  Copyright � 2017 ChiLaXSoft. All rights reserved.
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
	this->size = moduleEntry.dwSize;
	this->bytes = new BYTE[this->size];

	for (DWORD i = 0; i < this->size; i++) {
		this->bytes[i] = process->ValueAtAddress<BYTE>(this->baseAddress + i);
	}

	return true;
}

UINT64 Module::PointerValueBySignature(BYTE* signature, char* mask, UINT32 offset) {
	UINT64 fileOffset = this->FirstOffsetOfSignature(signature, mask, (int)strlen(mask)) + offset;
	UINT64 signatureAddress = fileOffset + this->baseAddress;
	UINT32 foundOffset = this->process->ValueAtAddress<UINT32>(signatureAddress) + (UINT32)fileOffset;

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

UINT64 Module::FirstOffsetOfSignature(BYTE* pSignature, const char * pMask, int sigLength)
{
	for (int i = 0; i < this->size; i++)
	{
		if (MaskCheck(i, pSignature, pMask, sigLength))
		{
			printf("signature found at client.dll + 0x%x", i);
			return i;
		}
	}

	return NULL;
}