#pragma once

#include "../Main.h"
#include "../FileSystem.h"
#include "../MemoryPatch.h"

class IGenericPatcher
{
public:
	IGenericPatcher( void ) {
		installed = false;
		patchname = "";
	}
	virtual ~IGenericPatcher( void ) {}
	virtual bool Install( void ) {
		return Install2();
	}
	virtual bool Install2( void ) {
		if (patches.empty()) return false;

		bool result = true;
		vector<MemoryPatch>::iterator it;
		for (it = patches.begin(); it != patches.end(); it++)
		{

			result &= (*it).Apply();
		}
		if (result) {
			installed = true;
			WriteLog("��ġ ��ġ �Ϸ�: %s.\n", patchname.c_str());
		} else {
			WriteLog("��ġ ��ġ ����: %s.\n", patchname.c_str());
			for (it = patches.begin(); it != patches.end(); it++)
			result &= (*it).Revert();
		}
		return result;
	}
	virtual bool Uninstall( void ) {
		bool result = true;
		vector<MemoryPatch>::iterator it;
		for (it = patches.begin(); it != patches.end(); it++)
			result &= (*it).Revert();
		WriteLog("��ġ ���� �Ϸ�: %s.\n", patchname.c_str());
		installed = false;
		return result;
	}
	virtual bool IsInstalled( void ) {
		return installed;
	}
	virtual bool Toggle( void ) {
		if (IsInstalled())
			return Uninstall();
		else return Install();
	}
	virtual bool ReadINI( void ) = 0;
	virtual bool WriteINI( void ) = 0;

protected:
	bool CheckPatches( void ) {
		vector<MemoryPatch>::iterator it;
		for (it = patches.begin(); it != patches.end(); it++) {
			if (!(*it).Check()) {
				WriteLog("����: 0x%08lX �ּҿ��� Ű üũ�� �����߽��ϴ�.\n", (*it).GetAddr());
				(*it).Dump();
				patches.clear();
				return false;
			}
		}
		return true;
	}

	vector<MemoryPatch> patches;
	bool installed;
	string patchname; // For logging
};