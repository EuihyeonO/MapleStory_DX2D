#include "PrecompileHeader.h"
#include "UIController.h"
#include "QuickSlot.h"

UIController UIController::Value;

UIController::UIController()
{
	QuickSlotList.reserve(10);
}

UIController::~UIController()
{
}
