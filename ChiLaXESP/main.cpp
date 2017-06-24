//
//  main.cpp
//
//  Created by ChiLaX on 23/5/17.
//  Copyright © 2017 ChiLaXSoft. All rights reserved.
//

#include "stdafx.h"
#include "process.hpp"
#include "module.hpp"
#include "playerList.hpp"
#include "glow.hpp"

int main() {
	boolean doHack = false;

	printf("Welcome to ChiLaXESP, an open source counter strike hack based on the public glow ESP method.\n\n");

	Process* csgoProcess = new Process(L"csgo.exe");

	if(!csgoProcess->AcquiredHandle() || !csgoProcess->Alive()) {
		printf("ERROR: Counter-Strike: Global Offensive is not running.\n");
	} 
	else {
		Module* clientDllModule = new Module(csgoProcess, L"client.dll");

		if (!clientDllModule->AcquiredBytes()) {
			printf("ERROR: Couldnt find the client.dll module's base address.\n");
		}
		else {
			PlayerList* playerList = new PlayerList(csgoProcess, clientDllModule, 64);

			Glow* glow = new Glow(csgoProcess, clientDllModule, playerList);
			
			if (!glow->AcquireBaseAddress()) {
				printf("ERROR: Couldnt find glow object's base address.\n");
			}
			else {
				printf("Press F9 to activate or deactive glow ESP.\n");

				while (csgoProcess->Alive()) {
					playerList->ActivePlayersToConsole();
					std::cout << std::flush;
					Sleep(200);
					system("CLS");

					if (GetKeyState(VK_F9) & 0x8000) {
						if (!doHack) {
							doHack = true;
							printf("INFO: Glow ESP activated.\n");

							Sleep(200);
						}
						else {
							doHack = false;
							printf("INFO: Glow ESP deactivated.\n");

							Sleep(200);
						}
					}

					if (doHack) {
						if (!glow->AppliedGlow()) {
							printf("ERROR: Couldnt apply glow effect to enemy players.\n");
							break;
						}
					}

					Sleep(10); //for performance
				}
			}
		}
	}

	printf("\nINFO: End of execution --- press any button on the keyboard to exit.\n");
	
	getchar();

    return 0;
}

