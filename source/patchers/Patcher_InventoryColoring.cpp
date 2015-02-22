#include "Patcher_InventoryColoring.h"
#include "../Addr.h"
#include "../FileSystem.h"

//-----------------------------------------------------------------------------
// Static variable initialization

int CPatcher_InventoryColoring::strCount;

CPatcher_InventoryColoring::InvStruct CPatcher_InventoryColoring::InvColor[512];

unsigned long CPatcher_InventoryColoring::Color1;
unsigned long CPatcher_InventoryColoring::Color2;

bool CPatcher_InventoryColoring::ColorMOD = false;

LPBYTE CPatcher_InventoryColoring::addrTargetReturn = NULL;
LPBYTE CPatcher_InventoryColoring::addrItemColoring = NULL;

LPBYTE CPatcher_InventoryColoring::addrIsBroken = NULL;
LPBYTE CPatcher_InventoryColoring::addrIsExpired = NULL;
LPBYTE CPatcher_InventoryColoring::addrCheckFastStringID = NULL;

bool CPatcher_InventoryColoring::PatchEnabled = false;
//-----------------------------------------------------------------------------
// Constructor

CPatcher_InventoryColoring::CPatcher_InventoryColoring( void )
{
	patchname = "�κ��丮 �÷���";

	addrIsExpired = CAddr::Addr(IItem_IsExpired);
	addrIsBroken = CAddr::Addr(IItem_IsBroken);
	addrCheckFastStringID = CAddr::Addr(IItem_CheckFastStringID);

	int count = 0;

	//////////////////////////////////////////////////////////////////
	//																//
	//						�� ��Ʈ									//
	//																//
	//////////////////////////////////////////////////////////////////
	// �Ǳ�
	wcscpy_s(InvColor[count].category, 256, L"/instrument/");
	wcscpy_s(InvColor[count].name, 256, L"InvInstrument");
	count++;

	// å
	wcscpy_s(InvColor[count].category, 256, L"/book/");
	wcscpy_s(InvColor[count].name, 256, L"InvBook");
	count++;

	//////////////////////////////////////////////////////////////////
	//																//
	//						��� ��Ʈ								//
	//																//
	//////////////////////////////////////////////////////////////////

	// ȭ����
	wcscpy_s(InvColor[count].category, 256, L"/weapon/arrow/sac_item/largearrowsac/");
	wcscpy_s(InvColor[count].name, 256, L"InvArrowSac");
	count++;

	// ȭ��
	wcscpy_s(InvColor[count].category, 256, L"/weapon/arrow/");
	wcscpy_s(InvColor[count].name, 256, L"InvArrow");
	count++;

	// ����
	wcscpy_s(InvColor[count].category, 256, L"/weapon/");
	wcscpy_s(InvColor[count].name, 256, L"InvEquipWeapon");
	count++;

	// ���ɹ���
	wcscpy_s(InvColor[count].category, 256, L"/ego_weapon/");
	wcscpy_s(InvColor[count].name, 256, L"InvEgoWeapon");
	count++;

	// ����
	wcscpy_s(InvColor[count].category, 256, L"/shield/");
	wcscpy_s(InvColor[count].name, 256, L"InvEquipShield");
	count++;

	// �Ǽ�
	wcscpy_s(InvColor[count].category, 256, L"/accessary/");
	wcscpy_s(InvColor[count].name, 256, L"InvEquipAccessary");
	count++;

	// ����
	wcscpy_s(InvColor[count].category, 256, L"/equip/head/");
	wcscpy_s(InvColor[count].name, 256, L"InvEquipHead");
	count++;

	// ��
	wcscpy_s(InvColor[count].category, 256, L"/cloth/");
	wcscpy_s(InvColor[count].name, 256, L"InvEquipArmor");
	count++;

	// �Ź�
	wcscpy_s(InvColor[count].category, 256, L"/shoes/");
	wcscpy_s(InvColor[count].name, 256, L"InvEquipFoot");
	count++;

	// �尩
	wcscpy_s(InvColor[count].category, 256, L"/glove/");
	wcscpy_s(InvColor[count].name, 256, L"InvEquipHand");
	count++;

	// �κ�
	wcscpy_s(InvColor[count].category, 256, L"/robe/");
	wcscpy_s(InvColor[count].name, 256, L"InvEquipRobe");
	count++;


	//////////////////////////////////////////////////////////////////
	//																//
	//						 ���� & ġ�� ��Ʈ						//
	//																//
	//////////////////////////////////////////////////////////////////

	// ü��+���� ����
	wcscpy_s(InvColor[count].category, 256, L"/usable/potion/mana/hp/");
	wcscpy_s(InvColor[count].name, 256, L"InvHPManaPotion");
	count++;

	// ����+���� ����
	wcscpy_s(InvColor[count].category, 256, L"/usable/potion/stamina/hp/");
	wcscpy_s(InvColor[count].name, 256, L"InvStaminaManaPotion");
	count++;

	// ����� ����
	wcscpy_s(InvColor[count].category, 256, L"/usable/potion/hp/");
	wcscpy_s(InvColor[count].name, 256, L"InvHPPotion");
	count++;

	// ���� ����
	wcscpy_s(InvColor[count].category, 256, L"/usable/potion/mana/");
	wcscpy_s(InvColor[count].name, 256, L"InvManaPotion");
	count++;

	// ���׹̳� ����
	wcscpy_s(InvColor[count].category, 256, L"/usable/potion/stamina/");
	wcscpy_s(InvColor[count].name, 256, L"InvStaminaPotion");
	count++;

	// �λ� ȸ�� ����
	wcscpy_s(InvColor[count].category, 256, L"/usable/potion/wound/");
	wcscpy_s(InvColor[count].name, 256, L"InvWoundPotion");
	count++;

	// ���� ȸ�� ����
	wcscpy_s(InvColor[count].category, 256, L"/usable/potion/full_recovery_potion/");
	wcscpy_s(InvColor[count].name, 256, L"InvFullRecoveryPotion");
	count++;

	// �ູ�� ����
	wcscpy_s(InvColor[count].category, 256, L"/usable/blessing/");
	wcscpy_s(InvColor[count].name, 256, L"InvBlessPotion");
	count++;

	// �� ����
	wcscpy_s(InvColor[count].category, 256, L"/usable/potion/poison/");
	wcscpy_s(InvColor[count].name, 256, L"InvPoisonPotion");
	count++;

	// �ص� ����
	wcscpy_s(InvColor[count].category, 256, L"/usable/potion/antidote/");
	wcscpy_s(InvColor[count].name, 256, L"InvAntidotePotion");
	count++;

	// ������ ũ����Ż
	wcscpy_s(InvColor[count].category, 256, L"/usable/potion/no_hotkey/writelog_use/shadow_mission_bonus/not_feed/");
	wcscpy_s(InvColor[count].name, 256, L"InvShadowMissionBonus");
	count++;

	// �׿� ��� ���� ����
	wcscpy_s(InvColor[count].category, 256, L"/usable/potion/");
	wcscpy_s(InvColor[count].name, 256, L"InvOtherPotion");
	count++;

	// ���� ������
	wcscpy_s(InvColor[count].category, 256, L"/usable/resurrection/");
	wcscpy_s(InvColor[count].name, 256, L"InvResurrection");
	count++;

	// �ش� ������
	wcscpy_s(InvColor[count].category, 256, L"/usable/material/tailor/bandage/");
	wcscpy_s(InvColor[count].name, 256, L"InvBandage");
	count++;

	//////////////////////////////////////////////////////////////////
	//																//
	//						������Ż ��Ʈ							//
	//																//
	//////////////////////////////////////////////////////////////////
	
	// ���̽� ������Ż
	wcscpy_s(InvColor[count].category, 256, L"/ice_elemental/");
	wcscpy_s(InvColor[count].name, 256, L"InvIceElemental");
	count++;

	// ���̾� ������Ż
	wcscpy_s(InvColor[count].category, 256, L"/fire_elemental/");
	wcscpy_s(InvColor[count].name, 256, L"InvFireElemental");
	count++;
	
	// ����Ʈ�� ������Ż
	wcscpy_s(InvColor[count].category, 256, L"/lightning_elemental/");
	wcscpy_s(InvColor[count].name, 256, L"InvLightningElemental");
	count++;
	
	// ������Ż ������
	wcscpy_s(InvColor[count].category, 256, L"/elemental_remover/");
	wcscpy_s(InvColor[count].name, 256, L"InvElementalRemover");
	count++;

	//////////////////////////////////////////////////////////////////
	//																//
	//						 ���� ��Ʈ								//
	//																//
	//////////////////////////////////////////////////////////////////

	// ö����
	wcscpy_s(InvColor[count].category, 256, L"/ore/ironore/");
	wcscpy_s(InvColor[count].name, 256, L"InvIronOre");
	count++;
	wcscpy_s(InvColor[count].category, 256, L"/ore/ironore_fragment/");
	wcscpy_s(InvColor[count].name, 256, L"InvIronOre");
	count++;

	// ������
	wcscpy_s(InvColor[count].category, 256, L"/ore/silverore/");
	wcscpy_s(InvColor[count].name, 256, L"InvSilverOre");
	count++;
	wcscpy_s(InvColor[count].category, 256, L"/ore/silverore_fragment/");
	wcscpy_s(InvColor[count].name, 256, L"InvSilverOre");
	count++;

	// ������
	wcscpy_s(InvColor[count].category, 256, L"/ore/copperore/");
	wcscpy_s(InvColor[count].name, 256, L"InvCopperOre");
	count++;
	wcscpy_s(InvColor[count].category, 256, L"/ore/copperore_fragment/");
	wcscpy_s(InvColor[count].name, 256, L"InvCopperOre");
	count++;

	// �ݱ���
	wcscpy_s(InvColor[count].category, 256, L"/ore/goldore/");
	wcscpy_s(InvColor[count].name, 256, L"InvGoldOre");
	count++;
	wcscpy_s(InvColor[count].category, 256, L"/ore/goldore_fragment/");
	wcscpy_s(InvColor[count].name, 256, L"InvGoldOre");
	count++;

	// �̽�������
	wcscpy_s(InvColor[count].category, 256, L"/ore/mythrilore/");
	wcscpy_s(InvColor[count].name, 256, L"InvMythrilOre");
	count++;
	wcscpy_s(InvColor[count].category, 256, L"/ore/mythrilore_fragment/");
	wcscpy_s(InvColor[count].name, 256, L"InvMythrilOre");
	count++;

	// StrangeOre
	wcscpy_s(InvColor[count].category, 256, L"/ore/strangeore_fragment/");
	wcscpy_s(InvColor[count].name, 256, L"InvStrangeOre");
	count++;

	// ö��
	wcscpy_s(InvColor[count].category, 256, L"/ingot/ironingot/");
	wcscpy_s(InvColor[count].name, 256, L"InvIronIngot");
	count++;

	// ����
	wcscpy_s(InvColor[count].category, 256, L"/ingot/silveringot/");
	wcscpy_s(InvColor[count].name, 256, L"InvSilverIngot");
	count++;

	// ����
	wcscpy_s(InvColor[count].category, 256, L"/ingot/copperingot/");
	wcscpy_s(InvColor[count].name, 256, L"InvCopperIngot");
	count++;

	// �ݱ�
	wcscpy_s(InvColor[count].category, 256, L"/ingot/goldingot/");
	wcscpy_s(InvColor[count].name, 256, L"InvGoldIngot");
	count++;

	// �̽�����
	wcscpy_s(InvColor[count].category, 256, L"/ingot/mythrilingot/");
	wcscpy_s(InvColor[count].name, 256, L"InvMythrilIngot");
	count++;

	// ö��
	wcscpy_s(InvColor[count].category, 256, L"/plate/iron/");
	wcscpy_s(InvColor[count].name, 256, L"InvIronPlate");
	count++;

	// ����
	wcscpy_s(InvColor[count].category, 256, L"/plate/silver/");
	wcscpy_s(InvColor[count].name, 256, L"InvSilverPlate");
	count++;

	// ����
	wcscpy_s(InvColor[count].category, 256, L"/plate/copper/");
	wcscpy_s(InvColor[count].name, 256, L"InvCopperPlate");
	count++;

	// ����
	wcscpy_s(InvColor[count].category, 256, L"/plate/gold/");
	wcscpy_s(InvColor[count].name, 256, L"InvGoldPlate");
	count++;

	// �̽�����
	wcscpy_s(InvColor[count].category, 256, L"/plate/mythril/");
	wcscpy_s(InvColor[count].name, 256, L"InvMythrilPlate");
	count++;

	// ö��
	wcscpy_s(InvColor[count].category, 256, L"/bar/iron/");
	wcscpy_s(InvColor[count].name, 256, L"InvIronBar");
	count++;

	// ����
	wcscpy_s(InvColor[count].category, 256, L"/bar/silver/");
	wcscpy_s(InvColor[count].name, 256, L"InvSilverBar");
	count++;

	// ����
	wcscpy_s(InvColor[count].category, 256, L"/bar/copper/");
	wcscpy_s(InvColor[count].name, 256, L"InvCopperBar");
	count++;

	// �ݺ�
	wcscpy_s(InvColor[count].category, 256, L"/bar/gold/");
	wcscpy_s(InvColor[count].name, 256, L"InvGoldBar");
	count++;

	// �̽�����
	wcscpy_s(InvColor[count].category, 256, L"/bar/mythril/");
	wcscpy_s(InvColor[count].name, 256, L"InvMythrilBar");
	count++;

	//////////////////////////////////////////////////////////////////
	//																//
	//						�Ͽ�¡ ��Ʈ								//
	//																//
	//////////////////////////////////////////////////////////////////

	// �Ͽ�¡ ����
	wcscpy_s(InvColor[count].category, 256, L"/usable/warp_scroll/target/house/host_warp/");
	wcscpy_s(InvColor[count].name, 256, L"InvHousingKey");
	count++;

	// �Ͽ�¡ ��ȯ ����
	wcscpy_s(InvColor[count].category, 256, L"/usable/warp_scroll/target/destroyable/");
	wcscpy_s(InvColor[count].name, 256, L"InvHousingReturnCoupon");
	count++;

	//////////////////////////////////////////////////////////////////
	//																//
	//						���� ��Ʈ								//
	//																//
	//////////////////////////////////////////////////////////////////

	// ���� ������ #g3_pass
	wcscpy_s(InvColor[count].category, 256, L"/item/g3_pass/");
	wcscpy_s(InvColor[count].name, 256, L"InvDungeonPass");
	count++;

	// ���� ������ #dungeon_pass
	wcscpy_s(InvColor[count].category, 256, L"/item/dungeon_pass/");
	wcscpy_s(InvColor[count].name, 256, L"InvDungeonPass");
	count++;

	// ���� ������ #unlimited_dungeon_pass
	wcscpy_s(InvColor[count].category, 256, L"/usable/unlimited_dungeon_pass/");
	wcscpy_s(InvColor[count].name, 256, L"InvDungeonPass");
	count++;

	// ���� ������
	wcscpy_s(InvColor[count].category, 256, L"/item/ruin_pass/");
	wcscpy_s(InvColor[count].name, 256, L"InvRuinPass");
	count++;

	// �׸��ڹ̼� ������
	wcscpy_s(InvColor[count].category, 256, L"/item/shadowmission_pass/");
	wcscpy_s(InvColor[count].name, 256, L"InvShadowMissionPass");
	count++;

	// ���� Ű
	wcscpy_s(InvColor[count].category, 256, L"/dungeon/key/");
	wcscpy_s(InvColor[count].name, 256, L"InvDungeonKey");
	count++;

	//////////////////////////////////////////////////////////////////
	//																//
	//						ȭ�� ��Ʈ								//
	//																//
	//////////////////////////////////////////////////////////////////

	// ���� ������ ȭ��
	wcscpy_s(InvColor[count].category, 256, L"/item/usable/fossil_restoration/");
	wcscpy_s(InvColor[count].name, 256, L"InvFossilRestorable");
	count++;

	// ������ ȭ��
	wcscpy_s(InvColor[count].category, 256, L"/item/fossil/");
	wcscpy_s(InvColor[count].name, 256, L"InvFossil");
	count++;


	//////////////////////////////////////////////////////////////////
	//																//
	//					 ��ũ�� ������ ��Ʈ						//
	//																//
	//////////////////////////////////////////////////////////////////

	// ��æƮ ��ũ��
	wcscpy_s(InvColor[count].category, 256, L"/enchant/enchantscroll/");
	wcscpy_s(InvColor[count].name, 256, L"InvEnchantScroll");
	count++;

	// ���� ��ũ��
	wcscpy_s(InvColor[count].category, 256, L"/manual/");
	wcscpy_s(InvColor[count].name, 256, L"InvManualScroll");
	count++;

	// ����Ʈ ��ũ��
	wcscpy_s(InvColor[count].category, 256, L"/scroll/mission_paper/");
	wcscpy_s(InvColor[count].name, 256, L"InvQuestScroll");
	count++;
	wcscpy_s(InvColor[count].category, 256, L"/scroll/questscroll/");
	wcscpy_s(InvColor[count].name, 256, L"InvQuestScroll");
	count++;

	// �Ǻ� ��ũ��
	wcscpy_s(InvColor[count].category, 256, L"/scroll/lefthand/no_abrasion/score/");
	wcscpy_s(InvColor[count].name, 256, L"InvScoreScroll");
	count++;

	// �� �� ������ ��ũ��
	wcscpy_s(InvColor[count].category, 256, L"/scroll/");
	wcscpy_s(InvColor[count].name, 256, L"InvOtherScroll");
	count++;

	//////////////////////////////////////////////////////////////////
	//																//
	//					��밡�� ������ ��Ʈ						//
	//																//
	//////////////////////////////////////////////////////////////////

	// ���ָӴ�
	wcscpy_s(InvColor[count].category, 256, L"/pouch/money/");
	wcscpy_s(InvColor[count].name, 256, L"InvMoneyPouch");
	count++;

	// ���
	wcscpy_s(InvColor[count].category, 256, L"/money/not_given/");
	wcscpy_s(InvColor[count].name, 256, L"InvGoldMoney");
	count++;

	// ���� �ָӴ�
	wcscpy_s(InvColor[count].category, 256, L"/sac_item/woolsac/not_given/");
	wcscpy_s(InvColor[count].name, 256, L"InvWoolSac");
	count++;

	// ��ǰ
	wcscpy_s(InvColor[count].category, 256, L"/usable/food/");
	wcscpy_s(InvColor[count].name, 256, L"InvUsableFood");
	count++;

	// ���� ������
	wcscpy_s(InvColor[count].category, 256, L"/usable/warp_scroll/");
	wcscpy_s(InvColor[count].name, 256, L"InvWarpWing");
	count++;

	// ���̽� ����
	wcscpy_s(InvColor[count].category, 256, L"/usable/mine/ice/");
	wcscpy_s(InvColor[count].name, 256, L"InvIceMine");
	count++;

	// ���� ���� �㰡��
	wcscpy_s(InvColor[count].category, 256, L"/usable/personalshoplicense/");
	wcscpy_s(InvColor[count].name, 256, L"InvPersonalShopLicense");
	count++;

	//////////////////////////////////////////////////////////////////
	//																//
	//						���� ������ ��Ʈ						//
	//																//
	//////////////////////////////////////////////////////////////////

	// ������ ���� ������
	wcscpy_s(InvColor[count].category, 256, L"/usable/crystal/cloud/");
	wcscpy_s(InvColor[count].name, 256, L"InvCloudCrystal");
	count++;

	// �������� ���� ������
	wcscpy_s(InvColor[count].category, 256, L"/usable/crystal/snowstorm/");
	wcscpy_s(InvColor[count].name, 256, L"InvSnowStormCrystal");
	count++;

	// ��ȣ���� ���� ������
	wcscpy_s(InvColor[count].category, 256, L"/usable/crystal/barrier/");
	wcscpy_s(InvColor[count].name, 256, L"InvBarrierCrystal");
	count++;

	// ���� ���� ������
	wcscpy_s(InvColor[count].category, 256, L"/fire_crystal/crystal/");
	wcscpy_s(InvColor[count].name, 256, L"InvFireCrystal");
	count++;

	// ���� ���� ������
	wcscpy_s(InvColor[count].category, 256, L"/water_crystal/crystal/");
	wcscpy_s(InvColor[count].name, 256, L"InvWaterCrystal");
	count++;

	// �ٶ��� ���� ������
	wcscpy_s(InvColor[count].category, 256, L"/wind_crystal/crystal/");
	wcscpy_s(InvColor[count].name, 256, L"InvWindCrystal");
	count++;

	// ���� ���� ������
	wcscpy_s(InvColor[count].category, 256, L"/earth_crystal/crystal/");
	wcscpy_s(InvColor[count].name, 256, L"InvEarthCrystal");
	count++;

	// ���̾�� ���� ������
	wcscpy_s(InvColor[count].category, 256, L"/usable/item/crystal/mana_forming/hotkey_bar/fireball_crystal/");
	wcscpy_s(InvColor[count].name, 256, L"InvFireBallCrystal");
	count++;

	// ���̽� ���Ǿ��� ���� ������
	wcscpy_s(InvColor[count].category, 256, L"/usable/item/crystal/mana_forming/hotkey_bar/icespear_crystal/");
	wcscpy_s(InvColor[count].name, 256, L"InvIceSpearCrystal");
	count++;

	// ����� ���� ������
	wcscpy_s(InvColor[count].category, 256, L"/usable/item/crystal/mana_forming/hotkey_bar/thunder_crystal/");
	wcscpy_s(InvColor[count].name, 256, L"InvThunderCrystal");
	count++;

	// ������ �巹���� ���� ������
	wcscpy_s(InvColor[count].category, 256, L"/item/crystal/lifedrain/usable/");
	wcscpy_s(InvColor[count].name, 256, L"InvLifeDrainCrystal");
	count++;

	// ���� ĳ���� ���� ������
	wcscpy_s(InvColor[count].category, 256, L"/item/crystal/watercannon/");
	wcscpy_s(InvColor[count].name, 256, L"InvWaterCannonCrystal");
	count++;

	// ���� ���� ���� ������
	wcscpy_s(InvColor[count].category, 256, L"/item/crystal/rockgolem/recall/usable/");
	wcscpy_s(InvColor[count].name, 256, L"InvRockGolemCrystal");
	count++;

	// �� ���� ���� ������
	wcscpy_s(InvColor[count].category, 256, L"/item/crystal/forestgolem/recall/usable/");
	wcscpy_s(InvColor[count].name, 256, L"InvForestGolemCrystal");
	count++;

	// ��Ȳ ���� ���� ������
	wcscpy_s(InvColor[count].category, 256, L"/item/crystal/sulfurgolem/recall/usable/");
	wcscpy_s(InvColor[count].name, 256, L"InvSulfurGolemCrystal");
	count++;

	// ����/���� ���� ���� ������
	wcscpy_s(InvColor[count].category, 256, L"/item/crystal/whitegolem/recall/usable/");
	wcscpy_s(InvColor[count].name, 256, L"InvWhiteGolemCrystal");
	count++;

	// ����ũ�� ���� ������
	wcscpy_s(InvColor[count].category, 256, L"/item/crystal/spark/usable/");
	wcscpy_s(InvColor[count].name, 256, L"InvSparkCrystal");
	count++;

	// �� �� ���� ������
	wcscpy_s(InvColor[count].category, 256, L"/crystal/");
	wcscpy_s(InvColor[count].name, 256, L"InvCrystal");
	count++;

	//////////////////////////////////////////////////////////////////
	//																//
	//						ä�� ������ ��Ʈ						//
	//																//
	//////////////////////////////////////////////////////////////////

	// �����丷
	wcscpy_s(InvColor[count].category, 256, L"/item/wood/");
	wcscpy_s(InvColor[count].name, 256, L"InvWoodItem");
	count++;

	// ���
	wcscpy_s(InvColor[count].category, 256, L"/herb/");
	wcscpy_s(InvColor[count].name, 256, L"InvHerbItem");
	count++;

	// ���� ������
	wcscpy_s(InvColor[count].category, 256, L"/jewel/");
	wcscpy_s(InvColor[count].name, 256, L"InvJewel");
	count++;

	//////////////////////////////////////////////////////////////////
	//																//
	//						���� ������ ��Ʈ						//
	//																//
	//////////////////////////////////////////////////////////////////

	// ���� ��ũ��
	wcscpy_s(InvColor[count].category, 256, L"/item/evilscroll/");
	wcscpy_s(InvColor[count].name, 256, L"InvEvilScroll");
	count++;

	// ���� ��
	wcscpy_s(InvColor[count].category, 256, L"/item/nao_dress/");
	wcscpy_s(InvColor[count].name, 256, L"InvNaoDress");
	count++;

	//////////////////////////////////////////////////////////////////
	//																//
	//						�Ϲ� ������ ��Ʈ						//
	//																//
	//////////////////////////////////////////////////////////////////

	// ���� ������
	wcscpy_s(InvColor[count].category, 256, L"/present/");
	wcscpy_s(InvColor[count].name, 256, L"InvGiftItem");
	count++;

	// ��� ������
	wcscpy_s(InvColor[count].category, 256, L"/delivery/");
	wcscpy_s(InvColor[count].name, 256, L"InvDeliveryItem");
	count++;

	// ���� ����#01
	wcscpy_s(InvColor[count].category, 256, L"/item/stone01/");
	wcscpy_s(InvColor[count].name, 256, L"InvCuilinStone");
	count++;

	// ���� ����#02
	wcscpy_s(InvColor[count].category, 256, L"/item/stone02/");
	wcscpy_s(InvColor[count].name, 256, L"InvCuilinStone");
	count++;

	// ���� ����#03
	wcscpy_s(InvColor[count].category, 256, L"/item/stone03/");
	wcscpy_s(InvColor[count].name, 256, L"InvCuilinStone");
	count++;

	// ���� ����#04
	wcscpy_s(InvColor[count].category, 256, L"/item/stone04/");
	wcscpy_s(InvColor[count].name, 256, L"InvCuilinStone");
	count++;

	// ���ɼ�(����)
	wcscpy_s(InvColor[count].category, 256, L"/item/FragmentSpiritFossil/");
	wcscpy_s(InvColor[count].name, 256, L"InvSpiritFossil");
	count++;

	// ���ɼ�
	wcscpy_s(InvColor[count].category, 256, L"/item/ego_stone/");
	wcscpy_s(InvColor[count].name, 256, L"InvEgoStone");
	count++;

	strCount = count;

	WriteLog("%d���� �κ��丮 �÷��� �����Ͱ� �ֽ��ϴ�.\n", strCount);

	vector<WORD> search;
	vector<WORD> patch1;
	vector<WORD> patch2;
	vector<WORD> patch3;
	vector<WORD> backup1;
	vector<WORD> backup2;
	vector<WORD> backup3;

	search +=
		0xFF, 0xD7,
		0x52,
		0x50,
		0xE8, -1, -1, -1, -1,
		0x83, 0xC4, 0x0C,
		0x84, 0xC0,
		0x74, 0x76;
/*
	patch3 +=
		0xFF, 0xD7,
		0x52,
		0x50,
		0xE8, -1, -1, -1, -1,
		0xE8, 0x01FF, 0x01FF, 0x01FF, 0x01FF,
		0x74, 0x76;
*/
	MemoryPatch mp( NULL, search, search );
	mp.Search( L"Pleione.dll" );
	addrItemColoring = mp.GetAddr() + 0x10;

	// ������ �ى�����
	backup1 +=
		0x8B, 0xF8,
		0x85, 0xDB,
		0x0F, 0x84, -1, -1, -1, -1,
		0x85, 0xFF,
		0x0F, 0x84, -1, -1, -1, -1,
		0x8B, 0xCF,
		0xFF, 0x15, -1, -1, -1, -1,
		0x84, 0xC0,
		0x0F, 0x85;

	funcPointer = (LPBYTE)patchInventoryColoring;

	patch1 +=
		0x8B, 0xF8,
		0x85, 0xDB,
		0x0F, 0x84, -1, -1, -1, -1,
		0x85, 0xFF,
		0x0F, 0x84, -1, -1, -1, -1,
		0x8B, 0xCF,
		0xFF, 0x15,
		((int)(&funcPointer) & 0xFF),
		(((int)(&funcPointer) & 0xFF00) >> 8),
		(((int)(&funcPointer) & 0xFF0000) >> 16),
		(((int)(&funcPointer) & 0xFF000000) >> 24),
		0x84, 0xC0,
		0x0F, 0x85;

	MemoryPatch mp1( NULL, patch1, backup1 );
	mp1.Search( L"Pleione.dll" );

	backup2 +=
		0x59,
		0x59,
		0x8B, 0x4D, 0x1C,
		0x89, 0x01,
		0xB8, 0x00, 0x00, 0xA0, 0x00,
		0x09, 0x06,
		0x09, 0x07,
		0xB8, 0x00, 0x00, 0xD0, 0x00,
		0xE9;

	patch2 +=
		0x59,
		0x59,
		0x8B, 0x4D, 0x1C,
		0x89, 0x01,
		0xA1,
		((int)(&Color1) & 0xFF),
		(((int)(&Color1) & 0xFF00) >> 8),
		(((int)(&Color1) & 0xFF0000) >> 16),
		(((int)(&Color1) & 0xFF000000) >> 24),
		0x09, 0x06,
		0x09, 0x07,
		0xA1,
		((int)(&Color2) & 0xFF),
		(((int)(&Color2) & 0xFF00) >> 8),
		(((int)(&Color2) & 0xFF0000) >> 16),
		(((int)(&Color2) & 0xFF000000) >> 24),
		0xE9;

	MemoryPatch mp2( NULL, patch2, backup2 );
	mp2.Search( L"Pleione.dll" );

	backup3 +=
		0x83, 0xBE, 0xAC, 0x00, 0x00, 0x00, 0x04,
		0x74, 0x39,
		0x53,
		0xFF, 0x75, 0xF8,
		0x8D, 0x8E;

	patch3 +=
		0xE8, 0x01FF, 0x01FF, 0x01FF, 0x01FF,
		0x85, 0xC0,
		0x74, 0x39,
		0x53,
		0xFF, 0x75, 0xF8,
		0x8D, 0x8E;

	MemoryPatch mp3( NULL, patch3, backup3 );
	mp3.Search( L"Pleione.dll" );
	mp3.PatchRelativeAddress( 0x01, (LPBYTE)patchIsEnable );

	addrTargetReturn = mp3.GetAddr() + 0x07;
	
	patches += mp1;
	patches += mp2;
	patches += mp3;
	if (CheckPatches())
		WriteLog("��ġ �ʱ�ȭ �Ϸ�: %s.\n", patchname.c_str());
	else
		WriteLog("��ġ �ʱ�ȭ ����: %s.\n", patchname.c_str());
}

//-----------------------------------------------------------------------------
// Hook functions

NAKED void CPatcher_InventoryColoring::patchInventoryColoring(void)
{
	if (IsPatchEnabled())
	{
		unsigned long c1;
		unsigned long c2;

		for(int lp=0; lp<strCount; lp++)
		{
			c1 = InvColor[lp].color[0];
			c2 = InvColor[lp].color[1];

			LPBYTE tp = (LPBYTE)&(InvColor[lp].category);

			__asm {
				MOV DWORD PTR DS:[Color1], 0x0A00000
				MOV DWORD PTR DS:[Color2], 0x0D00000

				MOV ECX, EDI
				CALL addrIsBroken
				TEST AL, AL
				JNE IsBroken

				//ColoringItem:

				MOV ECX, EDI
				PUSH DWORD PTR DS:[tp]
				CALL addrCheckFastStringID
				TEST AL, AL
				JNE TargetItem
				MOV BYTE PTR DS:[ColorMOD], 0
			}
		}

		__asm {
			JMP IsBroken
			// �ش�Ǵ� �������϶�
			TargetItem:
			MOV EAX, DWORD PTR DS:[c1]
			MOV DWORD PTR DS:[Color1], EAX
			MOV EAX, DWORD PTR DS:[c2]
			MOV DWORD PTR DS:[Color2], EAX
			MOV BYTE PTR DS:[ColorMOD], 1
		}

		// ���� �������� �ʾ��� �� �н�	
		if (c1 == 0 && c2 == 0)
		{
			__asm MOV BYTE PTR DS:[ColorMOD], 0
		}

		__asm {

			IsBroken:
			MOV ECX, EDI
			JMP addrIsBroken
		}
	}
	else
	{
		__asm {
			// �����ϱ�
			MOV ECX, EDI
			MOV DWORD PTR DS:[Color1], 0x0A00000
			MOV DWORD PTR DS:[Color2], 0x0D00000
			MOV BYTE PTR DS:[ColorMOD], 0
			JMP addrIsBroken
		}
	}
}

NAKED void CPatcher_InventoryColoring::patchIsEnable(void)
{
	__asm {
		//ADD ESP, 4h
		PUSH EAX
		/*
		TEST AL, AL
		JE lNext

		// Broke & Expire
		MOV DWORD PTR DS:[Color1], 0x0A00000
		MOV DWORD PTR DS:[Color2], 0x0D00000

		lNext:
		*/
	}

	// ��ġ�������̰� �κ��丮 �÷����� �ɸ��༮�϶�
	if (IsPatchEnabled() && ColorMOD == 1)
	{
		__asm {
			POP EAX
			CMP DWORD PTR DS:[ESI+0xAC],4
			JE lMousePut
			//ADD ESP, 0x0C
			ADD ESP, 0x04
			JMP addrItemColoring
		}
	}
	else
	{
		__asm {
			POP EAX
			lMousePut:
			//ADD ESP, 0x0C
			CMP DWORD PTR DS:[ESI+0xAC],4
			RETN
		}
	}

}
//-----------------------------------------------------------------------------
// �������̵� �Լ�

bool CPatcher_InventoryColoring::Uninstall( void ) {
	// �� ���� �ѹ� ��ġ�ϸ� ������ �� �����ϴ�
	return false;
}

bool CPatcher_InventoryColoring::Toggle( void ) {
	// �� ���� �ѹ� ��ġ�ϸ� ������ �� �����ϴ�
	return false;
}

//-----------------------------------------------------------------------------
// ��ġ ��� �Լ�

bool CPatcher_InventoryColoring::IsPatchEnabled(void)
{
	if (PatchEnabled == true)
		return true;
	else return false;
}

bool CPatcher_InventoryColoring::PatchEnable(void)
{
	PatchEnabled = true;
	return true;
}

bool CPatcher_InventoryColoring::PatchDisable(void)
{
	PatchEnabled = false;
	return true;
}

bool CPatcher_InventoryColoring::PatchToggle(void)
{
	if (IsPatchEnabled())
		PatchDisable();
	else PatchEnable();
	return true;
}
//-----------------------------------------------------------------------------
// INI Functions

bool CPatcher_InventoryColoring::ReadINI( void )
{
	wchar_t buf[256];
	wchar_t name[256];
	wchar_t *endptr = NULL;

	for (int i=0; i<strCount; i++)
	{
		for (int j=1; j<=2; j++)
		{
			swprintf(name, sizeof(name), L"%ls%d", InvColor[i].name, j);
			ReadINI_String(name, buf);
			InvColor[i].color[j-1] = wcstoul(buf, &endptr, 16);
			WriteLog("%ls: #%08X\n", name, InvColor[i].color[j-1]);
		}

	}

	if ( ReadINI_Bool( L"InvColoring" ))
		return PatchEnable();
	return true;
}

bool CPatcher_InventoryColoring::WriteINI( void )
{
	WriteINI_Bool( L"InvColoring", IsPatchEnabled() );
	return true;
}