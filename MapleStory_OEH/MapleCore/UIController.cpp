#include "PrecompileHeader.h"
#include "UIController.h"
#include "QuickSlot.h"

UIController UIController::Value;

UIController::UIController()
{
	QuickSlotList.reserve(10);

	ItemList[static_cast<int>(ItemType::Equip)].reserve(24);
	ItemList[static_cast<int>(ItemType::Use)].reserve(24);
	ItemList[static_cast<int>(ItemType::Etc)].reserve(24);
	ItemList[static_cast<int>(ItemType::Setup)].reserve(24);
	ItemList[static_cast<int>(ItemType::Cash)].reserve(24);
}

UIController::~UIController()
{
}
