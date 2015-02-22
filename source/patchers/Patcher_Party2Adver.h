#pragma once

/* ��Ƽ �Խ��� ����
 * ��Ƽ �Խ����� ������ �Խ������� ����
 * PATCHES: XXX.dll
 *
 * CTRL+H "Party2Adver"
 */

#include "../Main.h"
#include "../Singleton.h"
#include "GenericPatcher.h"

class CPatcher_Party2Adver : public IGenericPatcher {
public:
	CPatcher_Party2Adver();
	bool Uninstall( void );
	bool Toggle( void );

	bool ReadINI( void );
	bool WriteINI( void );
	static bool IsPatchEnabled(void);
	static bool PatchToggle(void);
	static bool PatchEnable(void);
	static bool PatchDisable(void);

private:
	// Options
	static bool PatchEnabled;
	// Hook functions
	static void patchParty2Adver(void);
	// Variables for hook functions
	static LPBYTE addrAdvertiseBoard;
	static LPBYTE addrTargetReturn;
	static LPBYTE addrPartyInlineCall;
	LPBYTE funcPointer;
};

typedef Singleton<CPatcher_Party2Adver> SngPatcher_Party2Adver;