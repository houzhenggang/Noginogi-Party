#include "Patcher_MimicNaming.h"
#include "../Addr.h"
#include "../FileSystem.h"

//-----------------------------------------------------------------------------
// Static variable initialization

LPBYTE CPatcher_MimicNaming::addrIsPet = NULL;

bool CPatcher_MimicNaming::PatchEnabled = false;
//-----------------------------------------------------------------------------
// Constructor

CPatcher_MimicNaming::CPatcher_MimicNaming( void )
{
	patchname = "�̹� �̸�ǥ";

	addrIsPet = CAddr::Addr(ICharacter_IsPet);

	vector<WORD> patch;
	vector<WORD> backup;

	backup +=
		0x85, 0xC0,									// +60: TEST EAX,EAX
		0x0F, 0x84, -1, -1, -1, -1,					// +62: JE xxxxxxxx
		0x8B, 0xCE,									// +68: MOV ECX,ESI
		0xE8, -1, -1, -1, -1,						// +6A: CALL xxxxxxxx (Standard.?IsPet@ICharacter@core@@QBE_NXZ)
		0x84, 0xC0,									// +6F: TEST AL, AL
		0x74, 0x16,									// +71: JE 0x16
		0x32, 0xDB;									// +73: XOR BL, BL

	patch +=
		0x85, 0xC0,
		-1, -1, -1, -1, -1, -1,
		-1, -1,
		0xE8, 0x01FF, 0x01FF, 0x01FF, 0x01FF,
		-1, -1,
		-1, -1,
		-1, -1;

	MemoryPatch mp( NULL, patch, backup );
	mp.Search( L"Standard.dll" );
	//mp.PatchExactAddress( 0x01, (LPBYTE)patchNameOfMod );
	mp.PatchRelativeAddress( 0x01, (LPBYTE)patchMimicNaming );
	
	patches += mp;
	if (CheckPatches())
		WriteLog("��ġ �ʱ�ȭ �Ϸ�: %s.\n", patchname.c_str());
	else
		WriteLog("��ġ �ʱ�ȭ ����: %s.\n", patchname.c_str());
}

//-----------------------------------------------------------------------------
// Hook functions

NAKED void CPatcher_MimicNaming::patchMimicNaming(void)
{
	// �̹� �̸�ǥ ���̱�
	if(IsPatchEnabled())
	{
		__asm {
			MOV EAX, 1
			RETN
		}
	}
	// �̹� �̸�ǥ �Ⱥ��̱�
	else
	{
		__asm JMP addrIsPet
	}
}
//-----------------------------------------------------------------------------
// �������̵� �Լ�

bool CPatcher_MimicNaming::Uninstall( void ) {
	// �� ���� �ѹ� ��ġ�ϸ� ������ �� �����ϴ�
	return false;
}

bool CPatcher_MimicNaming::Toggle( void ) {
	// �� ���� �ѹ� ��ġ�ϸ� ������ �� �����ϴ�
	return false;
}

//-----------------------------------------------------------------------------
// ��ġ ��� �Լ�

bool CPatcher_MimicNaming::IsPatchEnabled(void)
{
	if (PatchEnabled == true)
		return true;
	else return false;
}

bool CPatcher_MimicNaming::PatchEnable(void)
{
	PatchEnabled = true;
	return true;
}

bool CPatcher_MimicNaming::PatchDisable(void)
{
	PatchEnabled = false;
	return true;
}

bool CPatcher_MimicNaming::PatchToggle(void)
{
	if (IsPatchEnabled())
		PatchDisable();
	else PatchEnable();
	return true;
}
//-----------------------------------------------------------------------------
// INI Functions

bool CPatcher_MimicNaming::ReadINI( void )
{
	if ( ReadINI_Bool( L"MimicNaming" ))
		return PatchEnable();
	return true;
}

bool CPatcher_MimicNaming::WriteINI( void )
{
	WriteINI_Bool( L"MimicNaming", IsPatchEnabled() );
	return true;
}