// main.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "process.hpp"
#include "module.hpp"
#include "localPlayer.hpp"

int main()
{
	printf("Welcome to ChiLaXGlow, an open source counter strike hack based on the public glow method.\n");

	Process* csgoProcess = new Process(L"csgo.exe");

	if(!csgoProcess->AcquiredHandle() || !csgoProcess->Alive())
	{
		printf("csgo not running\n");
	} 
	else
	{
		Module* clientDllModule = new Module(csgoProcess, L"client.dll");

		if (!clientDllModule->AcquiredBytes())
		{
			printf("error: couldnt find client.dll module");
		}

		LocalPlayer* localPlayer = new LocalPlayer(csgoProcess, clientDllModule);

		if (!localPlayer->AcquiredInfos()) {
			printf("error: couldnt find local player infos\n");
		}
	}

	printf("FINI\n");
	
	/*
	UINT64 PlayerBase = engineDllModule->PointerValueBySignature(
		(BYTE*)"\x48\x8D\x1D\x00\x00\x00\x00\x48\x89\xDF\xE8\x00\x00\x00\x00\x48\x8D\x3D\x00\x00\x00\x00\x48\x8D\x15\x00\x00\x00\x00\x48\x89\xDE",
		"xxx????xxxx????xxx????xxx????xxx",
		0x3
	) + 0x2C;

	UINT64 GlowInfoOffset = engineDllModule->PointerValueBySignature(
		(BYTE*)"\x48\x8D\x3D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x85\xC0\x0F\x84\x00\x00\x00\x00\x48\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\x48\x8D\x35\x00\x00\x00\x00",
		"xxx????x????xxxx????xxx????xxxxxxx????",
		0x22
	) + 0x4;
	*/
	//UINT64 glowObjectLoopStartAddress = csgoProcess->ValueAtAddress<UINT64>(clientDllModule. + glowInfoOffset);

	/*
	printf("PlayerBase: %d\n", PlayerBase);
	printf("GlowInfoOffset: %d\n", GlowInfoOffset);
	*/

	getchar();

    return 0;
}

