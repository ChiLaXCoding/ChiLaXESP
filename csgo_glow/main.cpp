// main.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "process.hpp"
#include "module.hpp"
#include "playerList.hpp"

using namespace std;

#define PlayerBaseOffset 0x04A8A684;

int main() {
	printf("Welcome to ChiLaXGlow, an open source counter strike hack based on the public glow method.\n");

	Process* csgoProcess = new Process(L"csgo.exe");

	if(!csgoProcess->AcquiredHandle() || !csgoProcess->Alive()) {
		printf("csgo not running\n");
	} 
	else {
		Module* clientDllModule = new Module(csgoProcess, L"client.dll");

		if (!clientDllModule->AcquiredBytes()) {
			printf("error: couldnt find client.dll module");
		}
		else {
			PlayerList* playerList = new PlayerList(csgoProcess, clientDllModule, 64);

			while (csgoProcess->Alive()) {
				playerList->ActivePlayersToConsole();
				Sleep(200);
				cout << " " << flush; //flush forces the printing to the screen before it clears
				system("CLS");
			}
		}
	}

	printf("--- end of execution (press any button on keyboard) ---\n");
	
	/*
	UINT64 localPlayerOffset = this->module->PointerValueBySignature(
	(BYTE*)"\x89\xD6\x41\x89\x00\x49\x89\x00\x48\x8B\x1D\x00\x00\x00\x00\x48\x85\xDB\x74\x00",
	"xxxx?xx?xxx????xxxx?",
	0xB
	) + 0x4;

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

	UINT64 glowObjectLoopStartAddress = csgoProcess->ValueAtAddress<UINT64>(clientDllModule.BaseAddress() + glowInfoOffset);
	*/
	
	getchar();

    return 0;
}

