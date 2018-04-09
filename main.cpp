// main.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream> // für die textprints
#include "MemMan.h" //Zum nutzen der Memory Manager klasse
#include "csgo.hpp" //offsets vom hazedumper
#include <cstddef>


MemMan* Mem; //globale deklarierung, muss aber in der main ausgeführt werden

//offsets zum ändern
//offsets im csgo hpp header!
using namespace hazedumper::netvars;
using namespace hazedumper::signatures;




//statische offsets

#define m_bDormant 0xE9
#define m_iTeamNum 0xF0

//ende von offsets

bool triggerstate;

void Trigger()
{
	while (true)
	{
		//schauen ob an oder aus
		if (GetAsyncKeyState(VK_F1)) //togglekey bearbeitungsfähig
		{
			triggerstate = !triggerstate;
			if (triggerstate) std::cout << "trigger an" << std::endl;
			else std::cout << "trigger aus" << std::endl;
			Sleep(200);
		}
		//überspringt, falls trigger test aus ist
		if (!triggerstate) continue;

		//holt die spielerdaten
		DWORD LocalPlayer_Base = Mem->Read<DWORD>(Mem->ClientDLL_Base + dwLocalPlayer);
		int LocalPlayer_inCross = Mem->Read<int>(LocalPlayer_Base + m_iCrosshairId);
		int LocalPlayer_Team = Mem->Read<int>(LocalPlayer_Base + m_iTeamNum);

		//holt die EntityBase, mithilfe von dwEntityList
		DWORD Trigger_EntityBase = Mem->Read<DWORD>(Mem->ClientDLL_Base + dwEntityList + ((LocalPlayer_inCross - 1) * 0x10));
		int Trigger_EntityTeam = Mem->Read<int>(Trigger_EntityBase + m_iTeamNum);

		//bDormant ist eine bool wert zum prüfen ob der gegner lebt
		bool Trigger_EntityDormant = Mem->Read<bool>(Trigger_EntityBase + m_bDormant);


		if (GetKeyState(VK_MENU) & 0x8000)
		{
			if ((LocalPlayer_inCross > 0 && LocalPlayer_inCross <= 64) && (Trigger_EntityBase != NULL) && (Trigger_EntityTeam != LocalPlayer_Team) && (!Trigger_EntityDormant))
			{
				//schussmethode, verzögerungen in millisekunden
				Sleep(0); //verzögerung vorm schießen
				mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL);
				Sleep(50); //verzögerung zwischen den schüssen
				mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
				Sleep(50); //verzögerung nach dem schießen	
			}
		}


	}
}




int main()
{
		Mem = new MemMan(); //Konstruktor ausführen
	system("cls");
	std::cout << "aznhook triggertest #1" << std::endl;
	Trigger();
	delete Mem; //zum löschen des Memory Manager pointer, damit der destructor ausgeführt wird und den handle richtig beendet.
	return 0;
}

