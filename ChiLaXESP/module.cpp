//
//  module.cpp
//
//  Created by ChiLaX on 23/5/17.
//  Copyright © 2017 ChiLaXSoft. All rights reserved.
//

#include "stdafx.h"
#include "module.hpp"
#include <emmintrin.h>  
#include <nmmintrin.h>
#include <immintrin.h>

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

	for (DWORD i = 0; i < this->size; i++) {
		DWORD dword = process->ValueAtAddress<DWORD>(this->baseAddress + i);
		this->bytes[i] = dword & 0xff; 
		this->bytes[i + 1] = (dword >> 8) & 0xff; 
		this->bytes[i + 2] = (dword >> 16) & 0xff;
		this->bytes[i + 3] = (dword >> 24) & 0xff;
		i += 3;
	}

	return true;
}

DWORD Module::GetOffsetAtSignature(unsigned char* signature, char* mask, DWORD offset) {
	DWORD fileOffset = (DWORD)boyermoore_horspool_memmem(this->bytes, this->size, signature, strlen(mask), 0x00);
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

bool matches(const unsigned char haystack_ch, const unsigned char needle_ch, const unsigned char wildcard)
{
	return needle_ch == wildcard || haystack_ch == needle_ch;
}

const unsigned char *
Module::boyermoore_horspool_memmem(const unsigned char* haystack, size_t hlen,
	const unsigned char* needle, size_t nlen,
	const unsigned char wildcard)
{
	size_t bad_char_skip[UCHAR_MAX + 1]; /* Officially called: bad character shift */
	
	DWORD base = (DWORD)haystack;
										 /* Sanity checks on the parameters */
	if (nlen <= 0 || !haystack || !needle)
		return NULL;

	/* ---- Preprocess ---- */
	/* Initialize the table to default value */
	/* When a character is encountered that does not occur
	* in the needle, we can safely skip ahead for the whole
	* length of the needle.
	*/
	for (size_t scan = 0; scan <= UCHAR_MAX; scan = scan + 1)
	{
		bad_char_skip[scan] = nlen;
	}

	/* C arrays have the first byte at [0], therefore:
	* [nlen - 1] is the last byte of the array. */
	size_t last = nlen - 1;

	/* Then populate it with the analysis of the needle */
	for (size_t scan = 0; scan < last; scan = scan + 1)
	{
		unsigned char needleByte = needle[scan];
		bad_char_skip[needleByte] = last - scan;
	}

	/* ---- Do the matching ---- */

	/* Search the haystack, while the needle can still be within it. */
	while (hlen >= nlen)
	{
		/* scan from the end of the needle */
		for (size_t scan = last; matches(haystack[scan], needle[scan], wildcard); scan = scan - 1)
		{
			if (scan == 0) /* If the first byte matches, we've found it. */
			{
				return haystack - base;
			}
				
		}

		/* otherwise, we need to skip some bytes and start again.
		Note that here we are getting the skip value based on the last byte
		of needle, no matter where we didn't match. So if needle is: "abcd"
		then we are skipping based on 'd' and that value will be 4, and
		for "abcdd" we again skip on 'd' but the value will be only 1.
		The alternative of pretending that the mismatched character was
		the last character is slower in the normal case (E.g. finding
		"abcd" in "...azcd..." gives 4 by using 'd' but only
		4-2==2 using 'z'. */
		unsigned char lastByte = haystack[last];
		hlen -= bad_char_skip[lastByte];
		haystack += bad_char_skip[lastByte];
	}

	return 0;
}