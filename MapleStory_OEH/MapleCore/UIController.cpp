#include "PrecompileHeader.h"
#include "UIController.h"
#include "QuickSlot.h"

UIController UIController::Value;

UIController::UIController()
{
	QuickSlotList.reserve(10);

	EquipItemList[(static_cast<int>(EquipType::Cap))] = "";
	EquipItemList[(static_cast<int>(EquipType::Shoes))] = "";
	EquipItemList[(static_cast<int>(EquipType::Weapon))] = "";
	EquipItemList[(static_cast<int>(EquipType::Pants))] = "";
	EquipItemList[(static_cast<int>(EquipType::Coat))] = "";

}

UIController::~UIController()
{
}
