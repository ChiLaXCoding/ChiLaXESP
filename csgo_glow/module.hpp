#pragma once

//
//  module.hpp
//
//  Created by ChiLaX on 23/5/17.
//  Copyright © 2017 ChiLaXSoft. All rights reserved.
//

#include "stdafx.h"
#include "process.hpp"

class Module
{
public:
	Module(Process* process, WCHAR* moduleName);

	boolean AcquiredBytes();
	UINT64 PointerValueBySignature(BYTE* signature, char* mask, UINT32 start);
	DWORD BaseAddress();
private:
	Process* process;
	WCHAR* moduleName;
	DWORD baseAddress;
	DWORD size;
	BYTE* bytes;

	boolean MaskCheck(int nOffset, BYTE* btPattern, const char * strMask, int sigLength);
	UINT64 FirstOffsetOfSignature(BYTE* pSignature, const char * pMask, int sigLength);
};