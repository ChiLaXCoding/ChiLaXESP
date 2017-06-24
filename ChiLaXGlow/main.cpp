// main.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "process.hpp"
#include "module.hpp"
#include "playerList.hpp"
#include "glow.hpp"

int main() {
	boolean doHack = false;

	printf("Welcome to ChiLaXGlow, an open source counter strike hack based on the public glow ESP method.\n");
	printf("Press F9 to activate or deactive glow ESP.\n");

	Process* csgoProcess = new Process(L"csgo.exe");

	if(!csgoProcess->AcquiredHandle() || !csgoProcess->Alive()) {
		printf("csgo not running\n");
	} 
	else {
		Module* clientDllModule = new Module(csgoProcess, L"client.dll");

		if (!clientDllModule->AcquiredBytes()) {
			printf("error: couldnt find client.dll module\n");
		}
		else {
			PlayerList* playerList = new PlayerList(csgoProcess, clientDllModule, 64);

			Glow* glow = new Glow(csgoProcess, clientDllModule, playerList);
			
			if (!glow->AcquireBaseAddress()) {
				printf("error: couldnt find glow object base address\n");
			}
			else {
				while (csgoProcess->Alive()) {
					if (GetKeyState(VK_F9) & 0x8000) {
						if (!doHack) {
							doHack = true;
							printf("Glow ESP activated.\n");

							Sleep(200);
						}
						else {
							doHack = false;
							printf("Glow ESP deactivated.\n");

							Sleep(200);
						}
					}

					if (doHack) {
						if (!glow->AppliedGlow()) {
							printf("error: couldnt apply glow effect to active enemy players\n");
							break;
						}
					}
				}
			}
		}
	}

	printf("--- end of execution (press any button on keyboard) ---\n");
	
	getchar();

    return 0;
}

