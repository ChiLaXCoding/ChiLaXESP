#pragma once

//
//  module.hpp
//
//  Created by ChiLaX on 23/5/17.
//  Copyright © 2017 ChiLaXSoft. All rights reserved.
//

#include "process.hpp"

class Module
{
public:
	Module(Process* process, WCHAR* moduleName);

	boolean AcquiredBytes();
	DWORD GetOffsetAtSignature(unsigned char* signature, char* mask, DWORD start);
	DWORD BaseAddress();
private:
	Process* process;
	WCHAR* moduleName;
	DWORD baseAddress;
	DWORD size;
	BYTE* bytes;
	const unsigned char * boyermoore_horspool_memmem(const unsigned char* haystack, size_t hlen,
			const unsigned char* needle, size_t nlen,
			const unsigned char wildcard = '?');

	boolean MaskCheck(int nOffset, BYTE* btPattern, const char * strMask, int sigLength);
	DWORD FirstOffsetOfSignature(BYTE* pSignature, const char * pMask, int sigLength);
};