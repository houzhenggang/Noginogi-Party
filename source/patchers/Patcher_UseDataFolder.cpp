#include "Patcher_UseDataFolder.h"
#include "../Addr.h"

//-----------------------------------------------------------------------------
// Constructor

CPatcher_UseDataFolder::CPatcher_UseDataFolder( void )
{
	patchname = "������ ���� �켱��";

	LPBYTE addrSetLookUpOrder = CAddr::Addr(CFileSystem_SetLookUpOrder);
	if (!addrSetLookUpOrder) {
		WriteLog("��ġ �ʱ�ȭ ����: %s.\n", patchname.c_str());
		WriteLog("   ���� ��Ұ� �����ϴ�.\n");
		return;
	}

	vector<WORD> patch;
	vector<WORD> backup;

	backup +=
		0x8B, 0x45, 0xEC,	// MOV EAX, [EBP-14h]
		0x8B, 0x40, 0x04,	// MOV EAX, [EAX+04h]
		0x8B, 0x40, 0x18,	// MOV EAX, [EAX+18h]
		0x83, 0xE8, 0x00;	// SUB EAX, 0  (wat?)

	patch +=
		0x8B, 0x45, 0xEC,
		-1, -1, -1,
		-1, -1, -1,
		-1, -1, 0x01;		// SUB EAX, 0 => SUB EAX, 1

	MemoryPatch mp( NULL, patch, backup );
	if (!mp.Search( L"ESL.dll" )) {
		WriteLog("��ġ �ʱ�ȭ ����: %s.\n", patchname.c_str());
		return;
	}
	patches += mp;
	if (CheckPatches())
		WriteLog("��ġ �ʱ�ȭ �Ϸ�: %s.\n", patchname.c_str());
	else
		WriteLog("��ġ �ʱ�ȭ ����: %s.\n", patchname.c_str());
}

//-----------------------------------------------------------------------------
// �������̵� �Լ�

bool CPatcher_UseDataFolder::Install( void ) {
	if ( ReadINI_Bool( L"UseDataFolder" ))
		return Install2();
	return false;
}

bool CPatcher_UseDataFolder::Uninstall( void ) {
	// �� ���� �ѹ� ��ġ�ϸ� ������ �� �����ϴ�
	return false;
}

bool CPatcher_UseDataFolder::Toggle( void ) {
	// �� ���� �ѹ� ��ġ�ϸ� ������ �� �����ϴ�
	return false;
}

//-----------------------------------------------------------------------------
// INI Functions

bool CPatcher_UseDataFolder::ReadINI( void )
{
	return true;
}

bool CPatcher_UseDataFolder::WriteINI( void )
{
	WriteINI_Bool( L"UseDataFolder", IsInstalled() );
	return true;
}