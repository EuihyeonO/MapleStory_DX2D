#include "PrecompileHeader.h"
#include "UIController.h"
#include "QuickSlot.h"

UIController UIController::Value;

UIController::UIController()
{

	MyItemList[(static_cast<int>(EquipType::Cap))].reserve(24);
	MyItemList[(static_cast<int>(EquipType::Shoes))].reserve(24);
	MyItemList[(static_cast<int>(EquipType::Weapon))].reserve(24);
	MyItemList[(static_cast<int>(EquipType::Pants))].reserve(24);
	MyItemList[(static_cast<int>(EquipType::Coat))].reserve(24);

	for (int i = 0; i < 24; i++)
	{
		MyItemList[(static_cast<int>(EquipType::Cap))].push_back(nullptr);
		MyItemList[(static_cast<int>(EquipType::Shoes))].push_back(nullptr);
		MyItemList[(static_cast<int>(EquipType::Weapon))].push_back(nullptr);
		MyItemList[(static_cast<int>(EquipType::Pants))].push_back(nullptr);
		MyItemList[(static_cast<int>(EquipType::Coat))].push_back(nullptr);
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
