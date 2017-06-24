//
//  main.cpp
//
//  Created by ChiLaX on 23/5/17.
//  Copyright © 2017 ChiLaXSoft. All rights reserved.
//

#include "stdafx.h"
#include "glowESP.hpp"
#include "crosshairESP.hpp"

boolean glowESPActive = false;
boolean crosshairESPActive = false;
boolean triggerActive = false;

int main() {

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

			GlowESP* glowESP = new GlowESP(csgoProcess, clientDllModule, playerList);
			
			if (!glowESP->AcquireBaseAddress()) {
				printf("ERROR: Couldnt find glow object's base address.\n");
			}
			else {
				CrosshairESP* crosshairESP = new CrosshairESP(csgoProcess, clientDllModule, playerList);

				if (!crosshairESP->AcquireBaseAddress()) {
					printf("ERROR: Couldnt find crosshair object's base address.\n");
				}
				else {
					printf("Press F7 to activate or deactivate Glow ESP.\n");
					printf("Press F8 to activate or deactivate Crosshair ESP.\n");
					printf("Press F9 to activate or deactivate Trigger Bot.\n");
					printf("\n");

					while (csgoProcess->Alive()) {
						/*
						playerList->ActivePlayersToConsole();
						std::cout << std::flush;
						Sleep(200);
						system("CLS");
						*/

						if (GetKeyState(VK_F7) & 0x8000) {
							if (!glowESPActive) {
								glowESPActive = true;
								printf("INFO: Glow ESP activated.\n");

								Sleep(200);
							}
							else {
								glowESPActive = false;
								printf("INFO: Glow ESP deactivated.\n");

								Sleep(200);
							}
						}

						if (GetKeyState(VK_F8) & 0x8000) {
							if (!crosshairESPActive) {
								crosshairESPActive = true;
								printf("INFO: Crosshair ESP activated.\n");

								Sleep(200);
							}
							else {
								crosshairESPActive = false;
								printf("INFO: Crosshair ESP deactivated.\n");

								Sleep(200);
							}
						}

						if (GetKeyState(VK_F9) & 0x8000) {
							if (!triggerActive) {
								triggerActive = true;
								printf("INFO: Trigger Bot activated.\n");

								Sleep(200);
							}
							else {
								triggerActive = false;
								printf("INFO: Trigger Bot deactivated.\n");

								Sleep(200);
							}
						}

						if (glowESPActive) {
							if (!glowESP->AppliedGlow()) {
								printf("ERROR: Couldnt apply glow effect to enemy players.\n");
								break;
							}
						}

						if (!crosshairESP->AppliedCrosshairESP(crosshairESPActive, triggerActive)) {
							printf("ERROR: Couldnt apply Crosshair ESP.\n");
							break;
						}

						Sleep(10); //for performance
					}
				}
			}
		}
	}

	printf("\nINFO: End of execution --- press any button on the keyboard to exit.\n");
	
	getchar();

    return 0;
}

