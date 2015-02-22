#pragma once

/* Anything Put Skill Fx
 * ��ųâ�� �ƹ��ų� �ø���
 * PATCHES: PLEIONE.dll
 *
 * CTRL+H "AnyPutSkillFx"
 */

#include "../Main.h"
#include "../Singleton.h"
#include "GenericPatcher.h"

class CPatcher_AnyPutSkillFx : public IGenericPatcher {
public:
	CPatcher_AnyPutSkillFx();
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
	static void patchAnyPutSkillFx(void);
	// Variables for hook functions
	LPBYTE funcPointer;
};

typedef Singleton<CPatcher_AnyPutSkillFx> SngPatcher_AnyPutSkillFx;