#include "stdafx.h"
#include "supercraft360_glow_esp.h" 

CHackProcess lmao;

bool lol;
int myteam;
DWORD GlowPointer;

struct GlowStruct
{
	float r;
	float g;
	float b;
	float a;
	bool rwo;
	bool rwuo;
};

GlowStruct CRed = { 0.4f, 0.f, 0.f, 1.f, true, false };
GlowStruct CGreen = { 0.f, 0.4f, 0.f, 1.f, true, false };

struct PlayerList_t
{
	DWORD CBaseEntity;
	int Team;
	float Position[3];
	int Health;
	int Dormant;

	void ReadInformation(int Player)
	{
		ReadProcessMemory(lmao.__HandleProcess, (PBYTE*)(lmao.__dwordClient + 0x04A1D3A4 + (Player * 16)),
			&CBaseEntity, sizeof(DWORD), 0);
		ReadProcessMemory(lmao.__HandleProcess, (PBYTE*)(CBaseEntity + 0xF0), &Team, sizeof(int), 0);
		ReadProcessMemory(lmao.__HandleProcess, (PBYTE*)(CBaseEntity + 0xFC), &Health, sizeof(int), 0);
		ReadProcessMemory(lmao.__HandleProcess, (PBYTE*)(CBaseEntity + 0x134), &Position, sizeof(float[3]), 0);
		ReadProcessMemory(lmao.__HandleProcess, (PBYTE*)(CBaseEntity + 0xE9), &Dormant, sizeof(int), 0);

	}
}PlayerList[32];

void DrawGlow(int GlowIndex, GlowStruct Color)
{
	bool one = true;
	bool two = false;

	WriteProcessMemory(lmao.__HandleProcess, (PBYTE*)((GlowPointer + ((GlowIndex * 0x34) + 0x4))), &Color.r, sizeof(float), 0);
	WriteProcessMemory(lmao.__HandleProcess, (PBYTE*)((GlowPointer + ((GlowIndex * 0x34) + 0x8))), &Color.g, sizeof(float), 0);
	WriteProcessMemory(lmao.__HandleProcess, (PBYTE*)((GlowPointer + ((GlowIndex * 0x34) + 0xC))), &Color.b, sizeof(float), 0);
	WriteProcessMemory(lmao.__HandleProcess, (PBYTE*)((GlowPointer + ((GlowIndex * 0x34) + 0x10))), &Color.a, sizeof(float), 0);
	WriteProcessMemory(lmao.__HandleProcess, (PBYTE*)((GlowPointer + ((GlowIndex * 0x34) + 0x24))), &one, sizeof(bool), 0);
	WriteProcessMemory(lmao.__HandleProcess, (PBYTE*)((GlowPointer + ((GlowIndex * 0x34) + 0x25))), &two, sizeof(bool), 0);
}


void main2()
{

	lmao.RunProcess();

	for (;;) // or for(;;)
	{
		for (int i = 0; i < 32; i++)
		{
			PlayerList[i].ReadInformation(i);
			DWORD myplayer;
			ReadProcessMemory(lmao.__HandleProcess, (PBYTE*)(lmao.__dwordClient + 0xA7AFBC), &myplayer, sizeof(DWORD), 0);
			ReadProcessMemory(lmao.__HandleProcess, (PBYTE*)(myplayer + 0xF0), &myteam, sizeof(int), 0);


			if (GetAsyncKeyState(VK_INSERT))
			{
				lol = !lol;
				Sleep(250);
			}

			if (lol)
			{
				DWORD g_currentPlayer;
				int g_currentPlayerTeam;
				int g_currentPlayer_GlowIndex;


				ReadProcessMemory(lmao.__HandleProcess, (PBYTE*)(lmao.__dwordClient + 0x04B303A4), &GlowPointer, sizeof(DWORD), 0);
				ReadProcessMemory(lmao.__HandleProcess, (PBYTE*)(lmao.__dwordClient + 0x04A1D3A4 + ((i) * 16)), &g_currentPlayer, sizeof(DWORD), 0);
				ReadProcessMemory(lmao.__HandleProcess, (PBYTE*)(g_currentPlayer + 0x1DCC), &g_currentPlayer_GlowIndex, sizeof(int), 0);
				ReadProcessMemory(lmao.__HandleProcess, (PBYTE*)(g_currentPlayer + 0xF0), &g_currentPlayerTeam, sizeof(int), 0);

				if (!PlayerList[i].Dormant != 1)
					continue;

				if (PlayerList[i].Team == myteam)
				{
				}
				else
				{
					DrawGlow(g_currentPlayer_GlowIndex, CRed);
				}
			}
		}
		Sleep(1);

	}
}