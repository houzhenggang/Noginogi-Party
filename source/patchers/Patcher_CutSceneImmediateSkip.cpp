#include "Patcher_CutSceneImmediateSkip.h"
#include "../Addr.h"
#include "../FileSystem.h"

//-----------------------------------------------------------------------------
// Static variable initialization

bool CPatcher_CutSceneImmediateSkip::PatchEnabled = false;
//-----------------------------------------------------------------------------
// Constructor

CPatcher_CutSceneImmediateSkip::CPatcher_CutSceneImmediateSkip( void )
{
	patchname = "�ƽ� ������ ��ŵ";

	vector<WORD> patch;
	vector<WORD> backup;

	backup +=
		0x8B, 0x4F, 0x14,						// +26: MOV ECX,DWORD PTR DS:[EDI+14]
		0x81, 0xC1, 0xD0, 0x07, 0x00, 0x00,		// +29: ADD ECX,7D0
		0x3B, 0x4F, 0x0C;						// +2F: CMP ECX,DWORD PTR DS:[EDI+C]

	funcPointer = (LPBYTE)patchCutSceneImmediateSkip;

	patch +=
		0xFF, 0x15,
		((int)(&funcPointer) & 0xFF),
		(((int)(&funcPointer) & 0xFF00) >> 8),
		(((int)(&funcPointer) & 0xFF0000) >> 16),
		(((int)(&funcPointer) & 0xFF000000) >> 24),
		0x83, 0xC1, 0x00,
		0x3B, 0x4F, 0x0C;

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

NAKED void CPatcher_CutSceneImmediateSkip::patchCutSceneImmediateSkip(void)
{
	__asm {
		PUSH EAX
	}

	if (IsPatchEnabled())
	{
		__asm {
			MOV ECX,DWORD PTR DS:[EDI+0x14]
			POP EAX
			ADD ECX, 0
			RETN
		}
	}
	else
	{
		__asm {
			MOV ECX,DWORD PTR DS:[EDI+0x14]
			POP EAX
			ADD ECX,7D0h
			RETN
		}
	}
}
//-----------------------------------------------------------------------------
// �������̵� �Լ�

bool CPatcher_CutSceneImmediateSkip::Uninstall( void ) {
	// �� ���� �ѹ� ��ġ�ϸ� ������ �� �����ϴ�
	return false;
}

bool CPatcher_CutSceneImmediateSkip::Toggle( void ) {
	// �� ���� �ѹ� ��ġ�ϸ� ������ �� �����ϴ�
	return false;
}

//-----------------------------------------------------------------------------
// ��ġ ��� �Լ�

bool CPatcher_CutSceneImmediateSkip::IsPatchEnabled(void)
{
	if (PatchEnabled == true)
		return true;
	else return false;
}

bool CPatcher_CutSceneImmediateSkip::PatchEnable(void)
{
	PatchEnabled = true;
	return true;
}

bool CPatcher_CutSceneImmediateSkip::PatchDisable(void)
{
	PatchEnabled = false;
	return true;
}

bool CPatcher_CutSceneImmediateSkip::PatchToggle(void)
{
	if (IsPatchEnabled())
		PatchDisable();
	else PatchEnable();
	return true;
}
//-----------------------------------------------------------------------------
// INI Functions

bool CPatcher_CutSceneImmediateSkip::ReadINI( void )
{
	if ( ReadINI_Bool( L"CutSceneImmediateSkip" ))
		return PatchEnable();
	return true;
}

bool CPatcher_CutSceneImmediateSkip::WriteINI( void )
{
	WriteINI_Bool( L"CutSceneImmediateSkip", IsPatchEnabled() );
	return true;
}