// main.cpp : Definiert den Einstiegspunkt f�r die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream> // f�r die textprints
#include "MemMan.h" //Zum nutzen der Memory Manager klasse
#include <Windows.h> //behinhaltet funktionen zum schreiben und lesen des arbeitsspeichers
#include <TlHelp32.h> // behinhaltet n�tzliche funktionen um dlls zu le

MemMan* Mem; //globale deklarierung, muss aber in der main ausgef�hrt werden

//offsets zum �ndern

// 2018-04-06 02:42:19.720583700 UTC

namespace hazedumper {
	namespace netvars {
		constexpr ::std::ptrdiff_t m_ArmorValue = 0xB238;
		constexpr ::std::ptrdiff_t m_Collision = 0x318;
		constexpr ::std::ptrdiff_t m_CollisionGroup = 0x470;
		constexpr ::std::ptrdiff_t m_Local = 0x2FAC;
		constexpr ::std::ptrdiff_t m_MoveType = 0x258;
		constexpr ::std::ptrdiff_t m_OriginalOwnerXuidHigh = 0x316C;
		constexpr ::std::ptrdiff_t m_OriginalOwnerXuidLow = 0x3168;
		constexpr ::std::ptrdiff_t m_aimPunchAngle = 0x301C;
		constexpr ::std::ptrdiff_t m_aimPunchAngleVel = 0x3028;
		constexpr ::std::ptrdiff_t m_bGunGameImmunity = 0x3894;
		constexpr ::std::ptrdiff_t m_bHasDefuser = 0xB248;
		constexpr ::std::ptrdiff_t m_bHasHelmet = 0xB22C;
		constexpr ::std::ptrdiff_t m_bInReload = 0x3245;
		constexpr ::std::ptrdiff_t m_bIsDefusing = 0x3888;
		constexpr ::std::ptrdiff_t m_bIsScoped = 0x387E;
		constexpr ::std::ptrdiff_t m_bSpotted = 0x939;
		constexpr ::std::ptrdiff_t m_bSpottedByMask = 0x97C;
		constexpr ::std::ptrdiff_t m_clrRender = 0x70;
		constexpr ::std::ptrdiff_t m_dwBoneMatrix = 0x2698;
		constexpr ::std::ptrdiff_t m_fAccuracyPenalty = 0x32B0;
		constexpr ::std::ptrdiff_t m_fFlags = 0x100;
		constexpr ::std::ptrdiff_t m_flFallbackWear = 0x3178;
		constexpr ::std::ptrdiff_t m_flFlashDuration = 0xA2F8;
		constexpr ::std::ptrdiff_t m_flFlashMaxAlpha = 0xA2F4;
		constexpr ::std::ptrdiff_t m_flNextPrimaryAttack = 0x31D8;
		constexpr ::std::ptrdiff_t m_hActiveWeapon = 0x2EE8;
		constexpr ::std::ptrdiff_t m_hMyWeapons = 0x2DE8;
		constexpr ::std::ptrdiff_t m_hObserverTarget = 0x3360;
		constexpr ::std::ptrdiff_t m_hOwner = 0x29BC;
		constexpr ::std::ptrdiff_t m_hOwnerEntity = 0x148;
		constexpr ::std::ptrdiff_t m_iAccountID = 0x2FA8;
		constexpr ::std::ptrdiff_t m_iClip1 = 0x3204;
		constexpr ::std::ptrdiff_t m_iCompetitiveRanking = 0x1A44;
		constexpr ::std::ptrdiff_t m_iCompetitiveWins = 0x1B48;
		constexpr ::std::ptrdiff_t m_iCrosshairId = 0xB2A4;
		constexpr ::std::ptrdiff_t m_iEntityQuality = 0x2F8C;
		constexpr ::std::ptrdiff_t m_iFOVStart = 0x31D8;
		constexpr ::std::ptrdiff_t m_iGlowIndex = 0xA310;
		constexpr ::std::ptrdiff_t m_iHealth = 0xFC;
		constexpr ::std::ptrdiff_t m_iItemDefinitionIndex = 0x2F88;
		constexpr ::std::ptrdiff_t m_iItemIDHigh = 0x2FA0;
		constexpr ::std::ptrdiff_t m_iObserverMode = 0x334C;
		constexpr ::std::ptrdiff_t m_iShotsFired = 0xA2B0;
		constexpr ::std::ptrdiff_t m_iState = 0x31F8;
		constexpr ::std::ptrdiff_t m_iTeamNum = 0xF0;
		constexpr ::std::ptrdiff_t m_lifeState = 0x25B;
		constexpr ::std::ptrdiff_t m_nFallbackPaintKit = 0x3170;
		constexpr ::std::ptrdiff_t m_nFallbackSeed = 0x3174;
		constexpr ::std::ptrdiff_t m_nFallbackStatTrak = 0x317C;
		constexpr ::std::ptrdiff_t m_nForceBone = 0x267C;
		constexpr ::std::ptrdiff_t m_nTickBase = 0x3404;
		constexpr ::std::ptrdiff_t m_rgflCoordinateFrame = 0x440;
		constexpr ::std::ptrdiff_t m_szCustomName = 0x301C;
		constexpr ::std::ptrdiff_t m_szLastPlaceName = 0x3588;
		constexpr ::std::ptrdiff_t m_thirdPersonViewAngles = 0x31C8;
		constexpr ::std::ptrdiff_t m_vecOrigin = 0x134;
		constexpr ::std::ptrdiff_t m_vecVelocity = 0x110;
		constexpr ::std::ptrdiff_t m_vecViewOffset = 0x104;
		constexpr ::std::ptrdiff_t m_viewPunchAngle = 0x3010;
	} // namespace netvars
	namespace signatures {
		constexpr ::std::ptrdiff_t dwClientState = 0x57D894;
		constexpr ::std::ptrdiff_t dwClientState_GetLocalPlayer = 0x180;
		constexpr ::std::ptrdiff_t dwClientState_IsHLTV = 0x4CC8;
		constexpr ::std::ptrdiff_t dwClientState_Map = 0x28C;
		constexpr ::std::ptrdiff_t dwClientState_MapDirectory = 0x188;
		constexpr ::std::ptrdiff_t dwClientState_MaxPlayer = 0x310;
		constexpr ::std::ptrdiff_t dwClientState_PlayerInfo = 0x5240;
		constexpr ::std::ptrdiff_t dwClientState_State = 0x108;
		constexpr ::std::ptrdiff_t dwClientState_ViewAngles = 0x4D10;
		constexpr ::std::ptrdiff_t dwEntityList = 0x4A8387C;
		constexpr ::std::ptrdiff_t dwForceAttack = 0x2EC5BD8;
		constexpr ::std::ptrdiff_t dwForceAttack2 = 0x2EC5BE4;
		constexpr ::std::ptrdiff_t dwForceBackward = 0x2EC5C5C;
		constexpr ::std::ptrdiff_t dwForceForward = 0x2EC5C50;
		constexpr ::std::ptrdiff_t dwForceJump = 0x4F1AAF4;
		constexpr ::std::ptrdiff_t dwForceLeft = 0x2EC5C38;
		constexpr ::std::ptrdiff_t dwForceRight = 0x2EC5C44;
		constexpr ::std::ptrdiff_t dwGameDir = 0x61B1F0;
		constexpr ::std::ptrdiff_t dwGameRulesProxy = 0x4F84E3C;
		constexpr ::std::ptrdiff_t dwGetAllClasses = 0xAC92FC;
		constexpr ::std::ptrdiff_t dwGlobalVars = 0x57D598;
		constexpr ::std::ptrdiff_t dwGlowObjectManager = 0x4FA08E8;
		constexpr ::std::ptrdiff_t dwInput = 0x4ECE440;
		constexpr ::std::ptrdiff_t dwInterfaceLinkList = 0x6E2B24;
		constexpr ::std::ptrdiff_t dwLocalPlayer = 0xAA6614;
		constexpr ::std::ptrdiff_t dwMouseEnable = 0xAABE78;
		constexpr ::std::ptrdiff_t dwMouseEnablePtr = 0xAABE48;
		constexpr ::std::ptrdiff_t dwPlayerResource = 0x2EC3F5C;
		constexpr ::std::ptrdiff_t dwRadarBase = 0x4EB8564;
		constexpr ::std::ptrdiff_t dwSensitivity = 0xAABD14;
		constexpr ::std::ptrdiff_t dwSensitivityPtr = 0xAABCE8;
		constexpr ::std::ptrdiff_t dwSetClanTag = 0x87120;
		constexpr ::std::ptrdiff_t dwViewMatrix = 0x4A75294;
		constexpr ::std::ptrdiff_t dwWeaponTable = 0x4ECF03C;
		constexpr ::std::ptrdiff_t dwWeaponTableIndex = 0x31FC;
		constexpr ::std::ptrdiff_t dwYawPtr = 0xAABAD8;
		constexpr ::std::ptrdiff_t dwZoomSensitivityRatioPtr = 0xAB0B40;
		constexpr ::std::ptrdiff_t dwbSendPackets = 0xCD5DA;
		constexpr ::std::ptrdiff_t dwppDirect3DDevice9 = 0xA1F40;
		constexpr ::std::ptrdiff_t m_pStudioHdr = 0x293C;
		constexpr ::std::ptrdiff_t m_pitchClassPtr = 0x4EB8810;
		constexpr ::std::ptrdiff_t m_yawClassPtr = 0xAABAD8;
	} // namespace signatures
} // namespace hazedumper


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
		if (GetAsyncKeyState(VK_F1)) //togglekey bearbeitungsf�hig
		{
			triggerstate = !triggerstate;
			if (triggerstate) std::cout << "trigger an" << std::endl;
			else std::cout << "trigger aus" << std::endl;
			Sleep(200);
		}
		//�berspringt, falls trigger test aus ist
		if (!triggerstate) continue;

		//holt die spielerdaten
		DWORD LocalPlayer_Base = Mem->Read<DWORD>(Mem->ClientDLL_Base + m_dwLocalPlayer);
		int LocalPlayer_inCross = Mem->Read<int>(LocalPlayer_Base + m_iCrossHairID);
		int LocalPlayer_Team = Mem->Read<int>(LocalPlayer_Base + m_iTeamNum);

		//holt die EntityBase, mithilfe von dwEntityList
		DWORD Trigger_EntityBase = Mem->Read<DWORD>(Mem->ClientDLL_Base + m_dwEntityList + ((LocalPlayer_inCross - 1) * 0x10));
		int Trigger_EntityTeam = Mem->Read<int>(Trigger_EntityBase + m_iTeamNum);

		//bDormant ist eine bool wert zum pr�fen ob der gegner lebt
		bool Trigger_EntityDormant = Mem->Read<bool>(Trigger_EntityBase + m_bDormant);


		if (GetKeyState(VK_MENU) & 0x8000)
		{
			if ((LocalPlayer_inCross > 0 && LocalPlayer_inCross <= 64) && (Trigger_EntityBase != NULL) && (Trigger_EntityTeam != LocalPlayer_Team) && (!Trigger_EntityDormant))
			{
				//schussmethode, verz�gerungen in millisekunden
				Sleep(0); //verz�gerung vorm schie�en
				mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL);
				Sleep(50); //verz�gerung zwischen den sch�ssen
				mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
				Sleep(50); //verz�gerung nach dem schie�en	
			}
		}


	}
}



void loader()
{
	Mem = new MemMan(); //Konstruktor ausf�hren
	system("cls");
	std::cout << "aznhook triggertest #1" << std::endl;
	Trigger();
	delete Mem; //zum l�schen des Memory Manager pointer, damit der destructor ausgef�hrt wird und den handle richtig beendet.
}


int main()
{
	loader();
	return 0;
}

