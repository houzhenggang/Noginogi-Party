#include "Patcher_EnableSelfRightClick.h"
#include "../Addr.h"

//-----------------------------------------------------------------------------
// Static variable initialization

bool CPatcher_EnableSelfRightClick::PatchEnabled = false;
//-----------------------------------------------------------------------------
// Constructor

CPatcher_EnableSelfRightClick::CPatcher_EnableSelfRightClick( void )
{
	patchname = "�ڱ� �ŷ� Ȱ��ȭ";

	vector<WORD> patch;
	vector<WORD> backup;

	backup +=
		0x8B, 0x3D, -1, -1, -1, -1,			// +28: MOV EDI,DWORD PTR DS:[xxxxxxxx] ; Mint.?GetObjectId@CObject@mint@@QBE_KXZ
		0xFF, 0xD7,							// +2E: CALL EDI
		0x3B, 0x45, 0x08,					// +30: CMP EAX,DWORD PTR SS:[EBP+8]
		0x0F, 0x85;							// +33: JNZ ~~

	funcPointer = (LPBYTE)&patchSelfRightClick;

	patch +=
		0x8B, 0x3D,
		((int)(&funcPointer) & 0xFF),
		(((int)(&funcPointer) & 0xFF00) >> 8),
		(((int)(&funcPointer) & 0xFF0000) >> 16),
		(((int)(&funcPointer) & 0xFF000000) >> 24),
		0xFF, 0xD7,										// +2E: CALL EDI
		0x3B, 0x45, 0x08,								// +30: CMP EAX,DWORD PTR SS:[EBP+8]
		0x0F, 0x85;										// +33: JNZ ~~

	MemoryPatch mp( NULL, patch, backup );
	mp.Search( L"Pleione.dll" );
	
	patches += mp;
	if (CheckPatches())
		WriteLog("��ġ �ʱ�ȭ �Ϸ�: %s.\n", patchname.c_str());
	else
		WriteLog("��ġ �ʱ�ȭ ����: %s.\n", patchname.c_str());
}

NAKED void CPatcher_EnableSelfRightClick::patchSelfRightClick(void)
{
	if (IsPatchEnabled())
	{
		__asm {
			// DS:[63CEFCF8]=0133E227 (Mint.?GetObjectId@CObject@mint@@QBE_KXZ)
			MOV		ECX,DWORD PTR DS:[ECX+4]
	//		MOV		EAX,DWORD PTR DS:[ECX]
			MOV		EDX,DWORD PTR DS:[ECX+4]
			MOV		EAX, -1
			RETN
		}
	}
	else
	{
		__asm {
			// DS:[63CEFCF8]=0133E227 (Mint.?GetObjectId@CObject@mint@@QBE_KXZ)
			MOV		ECX,DWORD PTR DS:[ECX+4]
			MOV		EAX,DWORD PTR DS:[ECX]
			MOV		EDX,DWORD PTR DS:[ECX+4]
			RETN
		}
	}
}

bool CPatcher_EnableSelfRightClick::IsPatchEnabled(void)
{
	if (PatchEnabled == true)
		return true;
	else return false;
}

//-----------------------------------------------------------------------------
// �������̵� �Լ�

bool CPatcher_EnableSelfRightClick::Uninstall( void ) {
	// �� ���� �ѹ� ��ġ�ϸ� ������ �� �����ϴ�
	return false;
}

bool CPatcher_EnableSelfRightClick::Toggle( void ) {
	// �� ���� �ѹ� ��ġ�ϸ� ������ �� �����ϴ�
	return false;
}

//-----------------------------------------------------------------------------
// ��ġ ��� �Լ�

bool CPatcher_EnableSelfRightClick::PatchEnable(void)
{
	PatchEnabled = true;
	return true;
}

bool CPatcher_EnableSelfRightClick::PatchDisable(void)
{
	PatchEnabled = false;
	return true;
}

bool CPatcher_EnableSelfRightClick::PatchToggle(void)
{
	if (IsPatchEnabled())
		PatchDisable();
	else PatchEnable();
	return true;
}
//-----------------------------------------------------------------------------
// INI Functions

bool CPatcher_EnableSelfRightClick::ReadINI( void )
{
	if ( ReadINI_Bool( L"EnableSelfRightClick" ))
		return PatchEnable();
	return true;
}

bool CPatcher_EnableSelfRightClick::WriteINI( void )
{
	WriteINI_Bool( L"EnableSelfRightClick", IsPatchEnabled() );
	return true;
}