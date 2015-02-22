#include "Patcher_ExtraThreads.h"
#include "../Addr.h"
#include "../ModifyWindow.h"
#include "../ThreadWatch.h"

//-----------------------------------------------------------------------------
// Constructor

CPatcher_ExtraThreads::CPatcher_ExtraThreads( void )
{
	patchname = "����Ʈ�� ������";
}

//-----------------------------------------------------------------------------
// Overriden Patching Functions

bool CPatcher_ExtraThreads::Install( void ) {
	bool result = true;
	result &= CThreadWatch::SpawnWatcher();
	result &= CModifyWindow::SpawnModifier();
	installed = result;
	return result;
}


//-----------------------------------------------------------------------------
// �������̵� �Լ�

bool CPatcher_ExtraThreads::Uninstall( void ) {
	// �� ���� �ѹ� ��ġ�ϸ� ������ �� �����ϴ�
	return false;
}

bool CPatcher_ExtraThreads::Toggle( void ) {
	// �� ���� �ѹ� ��ġ�ϸ� ������ �� �����ϴ�
	return false;
}

//-----------------------------------------------------------------------------
// INI Functions

bool CPatcher_ExtraThreads::ReadINI( void )
{
	return true;
}

bool CPatcher_ExtraThreads::WriteINI( void )
{
	return true;
}
