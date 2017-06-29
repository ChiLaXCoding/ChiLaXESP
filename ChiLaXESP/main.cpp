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

void EnableHack(boolean* bPointer, char keyCode, char* hackName) {
	if (GetKeyState(keyCode) & 0x8000) {
		if (!*bPointer) {
			*bPointer = true;
			printf("INFO: %s activated.\n", hackName);

			Sleep(200);
		}
		else {
			*bPointer = false;
			printf("INFO: %s deactivated.\n", hackName);

			Sleep(200);
		}
	}
}

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

			if (!playerList->PlayersInitialized()) {
				printf("ERROR: Couldn't find player list base address.\n");
			}
			else {
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
							EnableHack(&glowESPActive, VK_F7, "Glow ESP");
							EnableHack(&crosshairESPActive, VK_F8, "Crosshair ESP");
							EnableHack(&triggerActive, VK_F9, "Trigger Bot");


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

							/*
							playerList->ActivePlayersToConsole();
							Sleep(200);
							std::cout << "" << std::flush;
							system("cls");
							*/

							Sleep(10); //for performance
						}
					}
				}
			}
		}
	}

	printf("\nINFO: End of execution --- press any button on the keyboard to exit.\n");
	
	getchar();

    return 0;
}

