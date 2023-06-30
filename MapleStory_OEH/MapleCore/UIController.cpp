#include "PrecompileHeader.h"
#include "UIController.h"
#include "QuickSlot.h"

UIController UIController::Value;

UIController::UIController()
{

	MyItemList[(static_cast<int>(ItemType::Equip))].reserve(24);
	MyItemList[(static_cast<int>(ItemType::Use))].reserve(24);
	MyItemList[(static_cast<int>(ItemType::Etc))].reserve(24);
	MyItemList[(static_cast<int>(ItemType::Setup))].reserve(24);
	MyItemList[(static_cast<int>(ItemType::Cash))].reserve(24);

	for (int i = 0; i < 24; i++)
	{
		MyItemList[(static_cast<int>(ItemType::Equip))].push_back(nullptr);
		MyItemList[(static_cast<int>(ItemType::Use))].push_back(nullptr);
		MyItemList[(static_cast<int>(ItemType::Etc))].push_back(nullptr);
		MyItemList[(static_cast<int>(ItemType::Setup))].push_back(nullptr);
		MyItemList[(static_cast<int>(ItemType::Cash))].push_back(nullptr);
	}

	EquipItemList[(static_cast<int>(EquipType::Cap))] = nullptr;
	EquipItemList[(static_cast<int>(EquipType::Shoes))] = nullptr;
	EquipItemList[(static_cast<int>(EquipType::Weapon))] = nullptr;
	EquipItemList[(static_cast<int>(EquipType::Pants))] = nullptr;
	EquipItemList[(static_cast<int>(EquipType::Coat))] = nullptr;

}

UIController::~UIController()
{
}
