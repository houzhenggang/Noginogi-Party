#include "Patcher_AfterADKill.h"
#include "../Addr.h"
#include "../FileSystem.h"

//-----------------------------------------------------------------------------
// Static variable initialization

//-----------------------------------------------------------------------------
// Constructor

CPatcher_AfterADKill::CPatcher_AfterADKill( void )
{
	patchname = "���� ���� ���� ����";

	vector<WORD> patch;
	vector<WORD> backup;

	backup +=
		0x84, 0xC0,				// +550: TEST AL,AL
		0x74, 0x02,				// +552: JE 0x02
		0x32, 0xDB,				// +554: XOR BL, BL
		0x84, 0xDB,				// +556: TEST BL, BL
		0x74, 0x29,				// +558: JE 0x29
		0x8D, 0x4D, 0xEC,		// +55A: LEA ECX,DWORD PTR SS:[EBP-14]
		0xFF, 0x15;				// +55D: CALL DWORD PTR DS:[xxxxxxxx] (ESL.?GetLength@?$CStringT@_WVunicode_string_trait@esl@@Vunicode_string_implement@2@@esl@@QBEKXZ)

	patch +=
		0x84, 0xC0,
		-1, -1,
		-1, -1,
		-1, -1,
		0xEB, -1,
		-1, -1, -1,
		-1, -1;

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
// �������̵� �Լ�

bool CPatcher_AfterADKill::Install( void ) {
	if ( ReadINI_Bool( L"AfterADKill" ))
		// INI�� �����ϸ� ��ġ
		return Install2();
	return true;
}
bool CPatcher_AfterADKill::Uninstall( void ) {
	// �� ���� �ѹ� ��ġ�ϸ� ������ �� �����ϴ�
	return false;
}

bool CPatcher_AfterADKill::Toggle( void ) {
	// �� ���� �ѹ� ��ġ�ϸ� ������ �� �����ϴ�
	return false;
}

//-----------------------------------------------------------------------------
// INI Functions

bool CPatcher_AfterADKill::ReadINI( void )
{
	return true;
}

bool CPatcher_AfterADKill::WriteINI( void )
{
	return true;
}