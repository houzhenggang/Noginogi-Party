#include "MasterPatcher.h"

vector<IGenericPatcher *> CMasterPatcher::PatchList;

bool CMasterPatcher::PatchInstall( void )
{
	DebugLog("��ġ�� �ʱ�ȭ�մϴ�...\n");
	GetPatchList();
	vector<IGenericPatcher *>::iterator it;
	for (it = PatchList.begin(); it != PatchList.end(); it++) {
		(*it)->Install();
	}
	DebugLog("�ʱ�ȭ �Ϸ��߽��ϴ�.\n");
	return true;
}

bool CMasterPatcher::PatchFromINI( void )
{
	DebugLog("INI ���Ͽ��� ������ �н��ϴ�...\n");
	GetPatchList();
	vector<IGenericPatcher *>::iterator it;
	for (it = PatchList.begin(); it != PatchList.end(); it++) {
		(*it)->ReadINI();
	}
	DebugLog("������ �о����ϴ�.\n");
	return true;
}

bool CMasterPatcher::SaveToINI( void )
{
	DebugLog("INI ���Ͽ� ������ �����մϴ�...\n");
	GetPatchList();
	vector<IGenericPatcher *>::iterator it;
	for (it = PatchList.begin(); it != PatchList.end(); it++) {
		(*it)->WriteINI();
	}
	DebugLog("������ �����߽��ϴ�.\n");
	return true;
}

bool CMasterPatcher::ReloadINI( void )
{
	DebugLog("INI ���Ͽ��� ������ �ٽ� �н��ϴ�...\n");
	GetPatchList();
	vector<IGenericPatcher *>::iterator it;
	for (it = PatchList.begin(); it != PatchList.end(); it++) {
		(*it)->ReadINI();
	}
	DebugLog("������ �ٽ� �о����ϴ�.\n");
	return true;
}

bool CMasterPatcher::ExecuteINI( void )
{
	DebugLog("INI ������ �ҷ��ɴϴ�...\n");

	ShellExecute(NULL, NULL, L".\\nogiparty.ini", NULL, NULL, SW_NORMAL);
	return true;
}

bool CMasterPatcher::GetPatchList( void )
{
	PatchList.clear();
	PatchList +=
		//SngPatcher_MultipleInstance::Instance(),
		SngPatcher_DisableNighttime::Instance(),
		SngPatcher_EnableNameColoring::Instance(),
		SngPatcher_EnableSelfRightClick::Instance(),
		SngPatcher_EnterRemoteShop::Instance(),
		SngPatcher_ModifyZoomLimit::Instance(),
		SngPatcher_MoveToSameChannel::Instance(),
		SngPatcher_MoveWhileTalking::Instance(),
		//SngPatcher_ScreenshotQuality::Instance(),
		SngPatcher_ShowCombatPower::Instance(),
		SngPatcher_ExtendDurability::Instance(),
		//SngPatcher_ShowTrueFoodQuality::Instance(),
		SngPatcher_TalkToUnequippedEgo::Instance(),
		SngPatcher_TargetProps::Instance(),
		SngPatcher_UseBitmapFonts::Instance(),
		SngPatcher_UseDataFolder::Instance(),
		//SngPatcher_ParseCommand::Instance(),
		SngPatcher_UnlimitPartytime::Instance(),
		SngPatcher_MinuteClock::Instance(),
		SngPatcher_TimeAlerm::Instance(),
		SngPatcher_AnyPutSkillFx::Instance(),
		SngPatcher_ExpressBoard::Instance(),
		SngPatcher_Party2Adver::Instance(),
		SngPatcher_SimpleFrameIgnore::Instance(),
		//SngPatcher_TransformIgnore::Instance(),
		SngPatcher_FlyZeroHigh::Instance(),
		SngPatcher_MimicNaming::Instance(),
		SngPatcher_VisionInAllName::Instance(),
		SngPatcher_NoReflexLight::Instance(),
		SngPatcher_AfterADKill::Instance(),
		//SngPatcher_AlwaysBagView::Instance(),
		SngPatcher_BankTabEnable::Instance(),
		SngPatcher_NPCEquipView::Instance(),
		SngPatcher_IsolateUISave::Instance(),
		SngPatcher_CutSceneImmediateSkip::Instance(),
		SngPatcher_ItemDropPreservation::Instance(),
		SngPatcher_InventoryColoring::Instance(),
		SngPatcher_DeadlyHPShow::Instance(),
		SngPatcher_StatsFloating::Instance(),
		//SngPatcher_HideVisible::Instance(),
		SngPatcher_ShowItemPrice::Instance(),
		SngPatcher_FarSignRead::Instance(),
		SngPatcher_InframeWinPSV::Instance(),
		SngPatcher_SpaceUnlock::Instance(),
		SngPatcher_HackShield::Instance(),
		SngPatcher_ExtraThreads::Instance();
	return true;	
}