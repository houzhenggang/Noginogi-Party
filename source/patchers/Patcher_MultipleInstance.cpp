#include "Patcher_MultipleInstance.h"
#include "../Addr.h"
#include "../FileSystem.h"

//-----------------------------------------------------------------------------
// Static variable initialization

LPBYTE CPatcher_MultipleInstance::addrTargetReturn = NULL;
wchar_t CPatcher_MultipleInstance::strMutex[] = L"HxFV`rZxF";

bool CPatcher_MultipleInstance::PatchEnabled = false;
//-----------------------------------------------------------------------------
// Constructor

CPatcher_MultipleInstance::CPatcher_MultipleInstance( void )
{
	patchname = "MultipleInstance";

	LPBYTE addrMutex = CAddr::Addr(kernel32_CreateMutexW);
	if (!addrMutex) {
		WriteLog("��ġ �ʱ�ȭ ����: %s.\n", patchname.c_str());
		WriteLog("   ���� ��Ұ� �����ϴ�.\n");
		return;
	}

	vector<WORD> patch;
	vector<WORD> backup;

	backup +=
		0x8B, 0xFF,
		0x55,
		0x8B, 0xEC,
		0x5D;

	funcPointer = (LPBYTE)patchMultipleInstance;

	patch +=
		0xFF, 0x25,
		((int)(&funcPointer) & 0xFF),
		(((int)(&funcPointer) & 0xFF00) >> 8),
		(((int)(&funcPointer) & 0xFF0000) >> 16),
		(((int)(&funcPointer) & 0xFF000000) >> 24);

	MemoryPatch mp( (LPBYTE)addrMutex, patch, backup );
	//mp.Search( L"kernel32.dll" );
	//mp.PatchExactAddress( 0x01, (LPBYTE)patchMultipleInstance );
	//mp.PatchRelativeAddress( 0x01, (LPBYTE)patchMultipleInstance );

	addrTargetReturn = mp.GetAddr() + 0x06;
	
	patches += mp;
	if (CheckPatches())
		WriteLog("��ġ �ʱ�ȭ �Ϸ�: %s.\n", patchname.c_str());
	else
		WriteLog("��ġ �ʱ�ȭ ����: %s.\n", patchname.c_str());
}

//-----------------------------------------------------------------------------
// Hook functions

NAKED void CPatcher_MultipleInstance::patchMultipleInstance()
{
	__asm {
		PUSH ECX
		PUSH EDI
		PUSH ESI
		MOV ECX, 0x09
		LEA EDI, strMutex
		MOV ESI, DWORD PTR SS:[ESP+0x18]
		REPE CMPSB
		JNE lExit
		MOV DWORD PTR SS:[ESP+0x24], 0x01
//	if(strstr(lpName, "HxFV`rZxF"))
//		WriteLog("HxFV`rZxF �߰�!\n");

lExit:
		POP ESI
		POP EDI
		POP ECX

		MOV EDI,EDI
		PUSH EBP
		MOV EBP,ESP
		POP EBP
		JMP addrTargetReturn
	}
}
//-----------------------------------------------------------------------------
// �������̵� �Լ�

bool CPatcher_MultipleInstance::Uninstall( void ) {
	// �� ���� �ѹ� ��ġ�ϸ� ������ �� �����ϴ�
	return false;
}

bool CPatcher_MultipleInstance::Toggle( void ) {
	// �� ���� �ѹ� ��ġ�ϸ� ������ �� �����ϴ�
	return false;
}

//-----------------------------------------------------------------------------
// ��ġ ��� �Լ�

bool CPatcher_MultipleInstance::IsPatchEnabled(void)
{
	if (PatchEnabled == true)
		return true;
	else return false;
}

bool CPatcher_MultipleInstance::PatchEnable(void)
{
	PatchEnabled = true;
	return true;
}

bool CPatcher_MultipleInstance::PatchDisable(void)
{
	PatchEnabled = false;
	return true;
}

bool CPatcher_MultipleInstance::PatchToggle(void)
{
	if (IsPatchEnabled())
		PatchDisable();
	else PatchEnable();
	return true;
}
//-----------------------------------------------------------------------------
// INI Functions

bool CPatcher_MultipleInstance::ReadINI( void )
{
	if ( ReadINI_Bool( L"MultipleInstance" ))
		return PatchEnable();
	return true;
}

bool CPatcher_MultipleInstance::WriteINI( void )
{
	WriteINI_Bool( L"MultipleInstance", IsPatchEnabled() );
	return true;
}