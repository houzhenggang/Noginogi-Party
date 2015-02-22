#include "Patcher_MoveToSameChannel.h"
#include "../Addr.h"

//-------------------------------------------------------------------
// Local variables
bool CPatcher_MoveToSameChannel::PatchEnabled = false;

LPBYTE CPatcher_MoveToSameChannel::addrGetContents = NULL;
LPBYTE CPatcher_MoveToSameChannel::addrstrcmp = NULL;

//-----------------------------------------------------------------------------
// Constructor

CPatcher_MoveToSameChannel::CPatcher_MoveToSameChannel( void )
{
	patchname = "ä�� ������";

	addrstrcmp = CAddr::Addr(ESL_strcmp);
	addrGetContents = CAddr::Addr(CStringTUni_GetContents);

	if (!addrstrcmp ||
		!addrGetContents) {
		WriteLog("��ġ �ʱ�ȭ ����: %s.\n", patchname.c_str());
		WriteLog("   ���� ��Ұ� �����ϴ�.\n");
		return;
	}
	vector<WORD> patch;
	vector<WORD> backup;

	backup +=
		0xA1, -1, -1, -1, -1,				// +E4: MOV EAX,DWORD PTR DS:[xxxxxxxx]
		0x83, 0xC0, 0x0C,					// +E9: ADD EAX,0C
		0x50,								// +EC: PUSH EAX
		0xE8, -1, -1, -1, -1;				// +ED: CALL xxxxxxxx

	patch +=
		-1, -1, -1, -1, -1,
		-1, -1, -1,
		0x50,
		0xE8, 0x01FF, 0x01FF, 0x01FF, 0x01FF;

	MemoryPatch mp( NULL, patch, backup );
	mp.Search( L"Pleione.dll" );
	mp.PatchRelativeAddress( 0x01, (LPBYTE)patchMoveToSameChannel );
	
	patches += mp;
	if (CheckPatches())
		WriteLog("��ġ �ʱ�ȭ �Ϸ�: %s.\n", patchname.c_str());
	else
		WriteLog("��ġ �ʱ�ȭ ����: %s.\n", patchname.c_str());
}

NAKED void CPatcher_MoveToSameChannel::patchMoveToSameChannel(void)
{
	if (IsPatchEnabled())
	{
		__asm {
			MOV		EAX, 0			// ä�� �� �����ϱ�~~
			RETN
		}
	}
	else
	{
		__asm {
			MOV		ECX,DWORD PTR SS:[ESP+8]
			PUSH	ESI
			MOV		ESI, addrGetContents
			CALL	ESI
			MOV		ECX,DWORD PTR SS:[ESP+8]
			PUSH	EAX
			CALL	ESI
			PUSH	EAX
			CALL	addrstrcmp
			POP		ECX
			NEG		EAX
			POP		ECX
			SBB		EAX,EAX
			INC		EAX
			POP		ESI
			RETN
		}
	}
}

bool CPatcher_MoveToSameChannel::IsPatchEnabled(void)
{
	if (PatchEnabled == true)
		return true;
	else return false;
}

//-----------------------------------------------------------------------------
// �������̵� �Լ�

bool CPatcher_MoveToSameChannel::Uninstall( void ) {
	// �� ���� �ѹ� ��ġ�ϸ� ������ �� �����ϴ�
	return false;
}

bool CPatcher_MoveToSameChannel::Toggle( void ) {
	// �� ���� �ѹ� ��ġ�ϸ� ������ �� �����ϴ�
	return false;
}

//-----------------------------------------------------------------------------
// ��ġ ��� �Լ�

bool CPatcher_MoveToSameChannel::PatchEnable(void)
{
	PatchEnabled = true;
	return true;
}

bool CPatcher_MoveToSameChannel::PatchDisable(void)
{
	PatchEnabled = false;
	return true;
}

bool CPatcher_MoveToSameChannel::PatchToggle(void)
{
	if (IsPatchEnabled())
		PatchDisable();
	else PatchEnable();
	return true;
}
//-----------------------------------------------------------------------------
// INI Functions

bool CPatcher_MoveToSameChannel::ReadINI( void )
{
	if ( ReadINI_Bool( L"MoveToSameChannel" ))
		return PatchEnable();
	return true;
}

bool CPatcher_MoveToSameChannel::WriteINI( void )
{
	WriteINI_Bool( L"MoveToSameChannel", IsPatchEnabled() );
	return true;
}