// Mabinogi NogiParty Patch
// Created by Jinsu
// based by FANTASIA PATCH by spr33

// This source requires the Boost C++ libraries.
// http://www.boost.org/
// The default project configuration includes from
// the directory C:\Program Files\boost\boost_1_40_0\
// To change this, go to Project -> ijl15 Properties... ->
// Configuration Properties -> C/C++ -> General, and
// modify "Additional Include Directories".
#include "Main.h"

#include "Addr.h"
#include "FileSystem.h"
#include "DBGHook.h"
#include "patchers\MasterPatcher.h"

#define NOGI_VERSION "lv234"

//-------------------------------------------------------------------
// Global variables

HHOOK hHook;
bool g_isRunning;
HINSTANCE g_hInstance;

//-------------------------------------------------------------------
// Functions
void HSFuckInit();

bool WINAPI DllMain( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved )
{
	try
	{
		switch (fdwReason)
		{
		case DLL_PROCESS_ATTACH:
			{
				//time_t start, stop;
				//start = time(NULL);

				//HSFuckInit();

				g_hInstance = hinstDLL;
				g_isRunning = true;

				g_iniFile = GetCurPath();
				g_iniFile += L"\\nogiparty.ini";

				DeleteFile(L".\\nogi_partylog.txt");
				WriteLog("������ ����� ��Ƽ %s\n", NOGI_VERSION);
				WriteLog("Compile at %s %s\n", __DATE__, __TIME__);
				WriteLog("�ʱ�ȭ�� �Ϸ��߽��ϴ�. �۾��� �����մϴ�.\n");
				
				// dbgHelp ��ŷ�ؼ� GetAddress�ϱ�
				if(!SngDBGHook::Instance()->Hook()) return false;

				// ���� �ּ� ���
				CAddr::PreCacheAddresses();

				// ��ü �ν����ϱ�
				CMasterPatcher::PatchInstall();

				// INI���� ��ġ�ϱ�
				CMasterPatcher::PatchFromINI();

				WriteLog("����� ��Ƽ �۾��� �����߽��ϴ�.\n");
				break;
			}

		case DLL_THREAD_ATTACH:break;
		case DLL_THREAD_DETACH:break;
		case DLL_PROCESS_DETACH:
			{
				// ���� �����Ѵ�
				UnhookWindowsHookEx(hHook);

				WriteLog("����� ��Ƽ�� ��ε� �Ǿ����ϴ�.\n");
				break;
			}
		}
		return true;
	}
	catch(...)
	{
		WriteLog("����� ��Ƽ �ʱ�ȭ�� �����߽��ϴ�.");
	}
}