#include "PrecompileHeader.h"
#include "UIWindowManager.h"
#include "StatusWindow.h"
#include "SkillWindow.h"
#include "InventoryWindow.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>

UIWindowManager::UIWindowManager()
{
}

UIWindowManager::~UIWindowManager()
{
}

void UIWindowManager::Start()
{
	CreateUIKey();
}

void UIWindowManager::Update(float _DeltaTime) 
{
	UIOnOff();
}

void UIWindowManager::Render(float _DeltaTime) 
{
}

void UIWindowManager::CreateUIKey()
{
	if (GameEngineInput::IsKey("StatWindowOpen") == false)
	{
		GameEngineInput::CreateKey("StatWindowOpen", 'S');
		GameEngineInput::CreateKey("SkillWindowOpen", 'K');
		GameEngineInput::CreateKey("InventoryWindowOpen", 'I');
	}
}

void UIWindowManager::UIOnOff()
{
	if (GameEngineInput::IsDown("StatWindowOpen") == true)
	{
		if (MyStatusWindow == nullptr)
		{
			MyStatusWindow = GetLevel()->CreateActor<StatusWindow>();
		}
		else
		{
			MyStatusWindow->Death();
			MyStatusWindow = nullptr;
		}
	}

	else if (GameEngineInput::IsDown("SkillWindowOpen") == true)
	{
		if (MySKillWindow == nullptr)
		{
			MySKillWindow = GetLevel()->CreateActor<SkillWindow>();
		}
		else
		{
			MySKillWindow->SkillListDeath();
			MySKillWindow->Death();
			MySKillWindow = nullptr;
		}
	}

	else if (GameEngineInput::IsDown("InventoryWindowOpen") == true)
	{
		if (MyInventoryWindow == nullptr)
		{
			MyInventoryWindow = GetLevel()->CreateActor<InventoryWindow>();
		}
		else
		{
			MyInventoryWindow->ClearInventory();
			MyInventoryWindow->Death();
			MyInventoryWindow = nullptr;
		}
	}
}

void UIWindowManager::AllWindowDeath()
{
	if(MyStatusWindow != nullptr)
	{
		MyStatusWindow->Death();
		MyStatusWindow = nullptr;
	}

	if (MySKillWindow != nullptr)
	{
		MySKillWindow->SkillListDeath();
		MySKillWindow->Death();
		MySKillWindow = nullptr;
	}

	if(MyInventoryWindow != nullptr)
	{
		MyInventoryWindow->ClearInventory();
		MyInventoryWindow->Death();
		MyInventoryWindow = nullptr;
	}
}