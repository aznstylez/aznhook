#pragma once
#include <Windows.h> //behinhaltet funktionen zum schreiben und lesen des arbeitsspeichers
#include <TlHelp32.h> // behinhaltet nützliche funktionen um dlls zu lesen

class MemMan
{
private:
	DWORD dwProcID; //Prozess ID von CSGO
	HANDLE hProc; //CSGO Prozess handle

public:
	MODULEENTRY32 ClientDLL;
	MODULEENTRY32 EngineDLL;
	DWORD ClientDLL_Base, ClientDLL_Size;
	DWORD EngineDLL_Base, EngineDLL_Size;

bool AttachProcess(char* ProcessName)
	{
		HANDLE hPID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		const WCHAR* procNameChar;
		int nChars = MultiByteToWideChar(CP_ACP, 0, ProcessName, -1, NULL, 0);
		procNameChar = new WCHAR[nChars];
		MultiByteToWideChar(CP_ACP, 0, ProcessName, -1, (LPWSTR)procNameChar, nChars);

		do
			if (!wcscmp(procEntry.szExeFile, procNameChar))
			{
				this->dwProcID = procEntry.th32ProcessID;
				CloseHandle(hPID);
				this->hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->dwProcID);
				return true;
			}
		while (Process32Next(hPID, &procEntry));

		CloseHandle(hPID);
		return false;
	}
	MODULEENTRY32 GetModule(char* ModuleName)
	{
		HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcID);
		MODULEENTRY32 mEntry;
		mEntry.dwSize = sizeof(mEntry);

		const WCHAR *modNameChar;
		int nChars = MultiByteToWideChar(CP_ACP, 0, ModuleName, -1, NULL, 0);
		modNameChar = new WCHAR[nChars];
		MultiByteToWideChar(CP_ACP, 0, ModuleName, -1, (LPWSTR)modNameChar, nChars);

		do
			if (!wcscmp(mEntry.szModule, modNameChar))
			{
				CloseHandle(hModule);
				return mEntry;
			}
		while (Module32Next(hModule, &mEntry));

		CloseHandle(hModule);
		mEntry.modBaseAddr = 0x0;
		return mEntry;
	}

	template<class c>
	c Read(DWORD dwAddress)
	{
		c val;
		ReadProcessMemory(hProc, (LPVOID)dwAddress, &val, sizeof(c), NULL);
		return val;
	}

	template<class c>
	BOOL Write(DWORD dwAddress, c ValueToWrite)
	{
		return WriteProcessMemory(hProc, (LPVOID)dwAddress, &ValueToWrite, sizeof(c), NULL);
	}

		

	MemMan()
	{
		    system("cls");
			std::cout << "warte auf csgo..." << std::endl;
		while (!AttachProcess("csgo.exe"))
		{
			Sleep(1000);
		}
		
		
		Sleep(10000);
			this->hProc = NULL;
			this->dwProcID = NULL;
			try {
				if (!AttachProcess("csgo.exe")) throw 1;
				this->ClientDLL = GetModule("client.dll");
				this->EngineDLL = GetModule("engine.dll");
				this->ClientDLL_Base = (DWORD)this->ClientDLL.modBaseAddr;
				this->EngineDLL_Base = (DWORD)this->EngineDLL.modBaseAddr;
				if (this->ClientDLL_Base == 0x0) throw 2;
				if (this->EngineDLL_Base == 0x0) throw 3;
				this->ClientDLL_Size = this->ClientDLL.dwSize;
				this->EngineDLL_Size = this->EngineDLL.dwSize;
			}
			catch (int iEx) {
				switch (iEx)
				{
				case 1: MessageBoxA(NULL, "CS:GO muss an sein", "ERROR", MB_ICONSTOP | MB_OK); exit(0); break;
				case 2: MessageBoxA(NULL, "Client.dll konnte nicht gefunden werden", "ERROR", MB_ICONSTOP | MB_OK); exit(0); break;
				case 3: MessageBoxA(NULL, "Engine.dll konnte nicht gefunden werden", "ERROR", MB_ICONSTOP | MB_OK); exit(0); break;
				default: throw;
				}
			}
			catch (...) {
				MessageBoxA(NULL, "Unhandled exception thrown", "ERROR", MB_ICONSTOP | MB_OK);
				exit(0);
			}
		}
		
	

	~MemMan()
	{
		CloseHandle(this->hProc);
	}

	
};
