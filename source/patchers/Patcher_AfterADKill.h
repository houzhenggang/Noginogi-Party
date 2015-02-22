#pragma once

/* ���� ����� ���� ����
 * PATCHES: PLEIONE.dll
 */

#include "../Main.h"
#include "../Singleton.h"
#include "GenericPatcher.h"

class CPatcher_AfterADKill : public IGenericPatcher {
public:
	CPatcher_AfterADKill();
	bool Install( void );
	bool Uninstall( void );
	bool Toggle( void );

	bool ReadINI( void );
	bool WriteINI( void );

private:
	// Options
	// Hook functions
	// Variables for hook functions
};

typedef Singleton<CPatcher_AfterADKill> SngPatcher_AfterADKill;