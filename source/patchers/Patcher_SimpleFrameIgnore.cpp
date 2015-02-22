#include "Patcher_SimpleFrameIgnore.h"
#include "../Addr.h"
#include "../FileSystem.h"

//-----------------------------------------------------------------------------
// Static variable initialization
LPBYTE CPatcher_SimpleFrameIgnore::addr__time = NULL;

bool CPatcher_SimpleFrameIgnore::PatchEnabled = false;
//-----------------------------------------------------------------------------
// Constructor

CPatcher_SimpleFrameIgnore::CPatcher_SimpleFrameIgnore( void )
{
	patchname = "����ȭ ������ ����";

	addr__time = CAddr::Addr(ESL_ETC_TIME);

	vector<WORD> patch;
	vector<WORD> backup;

	backup +=
		0x8B, 0x08,								// +119: MOV ECX,DWORD PTR DS:[EAX]
		0x8B, 0x01,								// +11B: MOV EAX,DWORD PTR DS:[ECX]
		0xFF, 0x90, -1, -1, -1, -1,				// +11D: CALL DWORD PTR DS:[EAX+178]
		0x03, 0x46, -1,							// +123: ADD EAX,DWORD PTR DS:[ESI+28]
		0x8B, 0x3D, -1, -1, -1, -1,				// +126: MOV EDI,DWORD PTR DS:[xxxxxxxx] (ESL.?__time@etc@esl@@YAKXZ)
		0xD1, 0xE8;								// +12C: SHR EAX, 1


	funcPointer = (LPBYTE)patchSimpleFrameIgnore;

	patch +=
		-1, -1,
		-1, -1,
		0xFF, 0x90, -1, -1, -1, -1,
		0x03, 0x46, -1,
		0xFF, 0x15, 
		((int)(&funcPointer) & 0xFF),
		(((int)(&funcPointer) & 0xFF00) >> 8),
		(((int)(&funcPointer) & 0xFF0000) >> 16),
		(((int)(&funcPointer) & 0xFF000000) >> 24),
		0xD1, 0xE8;

	MemoryPatch mp( NULL, patch, backup );
	mp.Search( L"Pleione.dll" );
	//mp.PatchExactAddress( 0x01, (LPBYTE)patchNameOfMod );
	//mp.PatchRelativeAddress( 0x01, (LPBYTE)patchNameOfMod );
	
	patches += mp;
	if (CheckPatches())
		WriteLog("��ġ �ʱ�ȭ �Ϸ�: %s.\n", patchname.c_str());
	else
		WriteLog("��ġ �ʱ�ȭ ����: %s.\n", patchname.c_str());
}

//-----------------------------------------------------------------------------
// Hook functions

NAKED void CPatcher_SimpleFrameIgnore::patchSimpleFrameIgnore(void)
{
	__asm {
		MOV		EDI, addr__time
		PUSH	EAX
	}

	// ����ȭ ������ ���� �۵����϶�
	if (IsPatchEnabled())
	{
		__asm {
			POP		EAX
			MOV		EAX, 0
			RETN
		}
	}
	// ����ȭ ������ ���� �۵����� �ƴҶ�
	else
	{
		__asm {
			POP		EAX
			RETN
		}
	}
}
//-----------------------------------------------------------------------------
// �������̵� �Լ�

bool CPatcher_SimpleFrameIgnore::Uninstall( void ) {
	// �� ���� �ѹ� ��ġ�ϸ� ������ �� �����ϴ�
	return false;
}

bool CPatcher_SimpleFrameIgnore::Toggle( void ) {
	// �� ���� �ѹ� ��ġ�ϸ� ������ �� �����ϴ�
	return false;
}

//-----------------------------------------------------------------------------
// ��ġ ��� �Լ�

bool CPatcher_SimpleFrameIgnore::IsPatchEnabled(void)
{
	if (PatchEnabled == true)
		return true;
	else return false;
}

bool CPatcher_SimpleFrameIgnore::PatchEnable(void)
{
	PatchEnabled = true;
	return true;
}

bool CPatcher_SimpleFrameIgnore::PatchDisable(void)
{
	PatchEnabled = false;
	return true;
}

bool CPatcher_SimpleFrameIgnore::PatchToggle(void)
{
	if (IsPatchEnabled())
		PatchDisable();
	else PatchEnable();
	return true;
}
//-----------------------------------------------------------------------------
// INI Functions

bool CPatcher_SimpleFrameIgnore::ReadINI( void )
{
	if ( ReadINI_Bool( L"SimpleFrameIgnore" ))
		return PatchEnable();
	return true;
}

bool CPatcher_SimpleFrameIgnore::WriteINI( void )
{
	WriteINI_Bool( L"SimpleFrameIgnore", IsPatchEnabled() );
	return true;
}