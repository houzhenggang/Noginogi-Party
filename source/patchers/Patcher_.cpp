#include "Patcher_NameOfMod.h"
#include "../Addr.h"
#include "../FileSystem.h"

//-----------------------------------------------------------------------------
// Static variable initialization

bool CPatcher_NameOfMod::PatchEnabled = false;
//-----------------------------------------------------------------------------
// Constructor

CPatcher_NameOfMod::CPatcher_NameOfMod( void )
{
	patchname = "NameOfMod";

	LPBYTE addrXXX = CAddr::Addr(kernel32_CreateRemoteThread);
	if (!addrXXX) {
		WriteLog("��ġ �ʱ�ȭ ����: %s.\n", patchname.c_str());
		WriteLog("   ���� ��Ұ� �����ϴ�.\n");
		return;
	}

	vector<WORD> patch;
	vector<WORD> backup;

	backup +=
		0x90, 0x90, 0x90;	// NOP

	funcPointer = (LPBYTE)patchNameOfMod;

	patch +=
		0x90, 0x90, 0x90;	// NOP -> NOP

	MemoryPatch mp( NULL, patch, backup );
	mp.Search( L"Target.dll" );
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

NAKED void CPatcher_NameOfMod::patchNameOfMod(void)
{

}
//-----------------------------------------------------------------------------
// �������̵� �Լ�

bool CPatcher_NameOfMod::Uninstall( void ) {
	// �� ���� �ѹ� ��ġ�ϸ� ������ �� �����ϴ�
	return false;
}

bool CPatcher_NameOfMod::Toggle( void ) {
	// �� ���� �ѹ� ��ġ�ϸ� ������ �� �����ϴ�
	return false;
}

//-----------------------------------------------------------------------------
// ��ġ ��� �Լ�

bool CPatcher_NameOfMod::IsPatchEnabled(void)
{
	if (PatchEnabled == true)
		return true;
	else return false;
}

bool CPatcher_NameOfMod::PatchEnable(void)
{
	PatchEnabled = true;
	return true;
}

bool CPatcher_NameOfMod::PatchDisable(void)
{
	PatchEnabled = false;
	return true;
}

bool CPatcher_NameOfMod::PatchToggle(void)
{
	if (IsPatchEnabled())
		PatchDisable();
	else PatchEnable();
	return true;
}
//-----------------------------------------------------------------------------
// INI Functions

bool CPatcher_NameOfMod::ReadINI( void )
{
	if ( ReadINI_Bool( L"NameOfMod" ))
		return PatchEnable();
	return true;
}

bool CPatcher_NameOfMod::WriteINI( void )
{
	WriteINI_Bool( L"NameOfMod", IsPatchEnabled() );
	return true;
}