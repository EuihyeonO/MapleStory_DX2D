#include "PrecompileHeader.h"
#include "Level_SouthFerry.h"
#include "Player.h"
#include "BottomBar.h"
#include "StatusWindow.h"
#include "Mouse.h"
#include "PlayerValue.h"
#include "UIWindowManager.h"
#include "QuickSlot.h"
#include "GlobalFunction.h"
#include "SouthFerry.h"
#include "UIController.h"

Level_SouthFerry::Level_SouthFerry()
{
}

Level_SouthFerry::~Level_SouthFerry()
{
}

void Level_SouthFerry::Start()
{
	SetName("SOUTHFERRY");

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetCamera(100)->SetProjectionType(CameraType::Orthogonal);

	GetMainCamera()->SetSortType(0, SortType::ZSort);
	GetCamera(100)->SetSortType(0, SortType::ZSort);

	//test
	std::shared_ptr<ItemInfo> NewItem1 = std::make_shared<ItemInfo>();
	NewItem1->EquipType = static_cast<int>(EquipType::Weapon);
	NewItem1->ItemName = "Ganier";

	std::shared_ptr<ItemInfo> NewItem2 = std::make_shared<ItemInfo>();
	NewItem2->EquipType = static_cast<int>(EquipType::Pants);
	NewItem2->ItemName = "BLUEPANTS";

	std::shared_ptr<ItemInfo> NewItem3 = std::make_shared<ItemInfo>();
	NewItem3->EquipType = static_cast<int>(EquipType::Coat);
	NewItem3->ItemName = "BLUEGOWN";

	UIController::GetUIController()->AddToEquipItemList(NewItem1, static_cast<int>(ItemType::Equip));
	UIController::GetUIController()->AddToEquipItemList(NewItem2, static_cast<int>(ItemType::Equip));
	UIController::GetUIController()->AddToEquipItemList(NewItem3, static_cast<int>(ItemType::Equip));
}

void Level_SouthFerry::Update(float _DeltaTime)
{

}

void Level_SouthFerry::LevelChangeStart()
{
	LoadResources();
	ActorCreate();
}

void Level_SouthFerry::LevelChangeEnd()
{
	ActorDeath();
	UnLoadResources();
}

void Level_SouthFerry::ActorCreate()
{
	if (Map == nullptr)
	{
		Map = CreateActor<SouthFerry>();
		std::string ColMapName = Map->GetColMapName().data();
		std::shared_ptr<GameEngineTexture> ColMap = GameEngineTexture::Find(ColMapName);
		GlobalFunction::GetValue()->SetColMap(ColMap);
	}

	if (MyPlayer == nullptr)
	{
		MyPlayer = CreateActor<Player>();
		MyPlayer->SetCurPlayer(MyPlayer);
		MyPlayer->SetColMap(Map->GetColMapName());
		MyPlayer->SetCurPlayer(MyPlayer);
	}

	if (MyMouse == nullptr)
	{
		MyMouse = CreateActor<Mouse>();
		MyMouse->SetCurMouse(MyMouse);
	}

	if (MyQuickSlot == nullptr)
	{
		MyQuickSlot = CreateActor<QuickSlot>();
	}

	if (MyBottomBar == nullptr)
	{
		MyBottomBar = CreateActor<BottomBar>();
	}

	if (MyUIWindowManager == nullptr)
	{
		MyUIWindowManager = CreateActor<UIWindowManager>();
	}


	if (PlayerValue::GetValue()->GetPrevLevelName() == "123")
	{
		MyPlayer->SetRight();
		MyPlayer->SetMoveType("Jump");
		MyPlayer->GetTransform()->SetLocalPosition({ -500, 200 });
	}
	else if (PlayerValue::GetValue()->GetPrevLevelName() == "123")
	{
		MyPlayer->SetLeft();
		MyPlayer->SetMoveType("Jump");
		MyPlayer->GetTransform()->SetLocalPosition({ 625, -10 });
	}
}

void Level_SouthFerry::ActorDeath()
{
	if (MyPlayer != nullptr)
	{
		MyPlayer->Death();
		MyPlayer = nullptr;
	}

	if (MyMouse != nullptr)
	{
		MyMouse->Death();
		MyMouse = nullptr;
	}

	if (MyQuickSlot != nullptr)
	{
		MyQuickSlot = nullptr;
	}

	if (MyBottomBar != nullptr)
	{
		MyBottomBar = nullptr;
	}

	if (MyUIWindowManager != nullptr)
	{
		MyUIWindowManager->AllWindowDeath();
		MyUIWindowManager->Death();
		MyUIWindowManager = nullptr;
	}

	if (Map != nullptr)
	{
		Map->Death();
		Map = nullptr;
	}
}

void Level_SouthFerry::LoadResources()
{
	if (nullptr == GameEngineTexture::Find("SouthFerry.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("SouthFerry");
		NewDir.Move("SouthFerryNotSprite");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}
	else
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("SouthFerry");
		NewDir.Move("SouthFerryNotSprite");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::ReLoad(File[i].GetFullPath());
		}
	}
}

void Level_SouthFerry::UnLoadResources()
{
	if (nullptr != GameEngineTexture::Find("SouthFerry.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("SouthFerry");
		NewDir.Move("SouthFerryNotSprite");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{

			std::string FileFullPath = File[i].GetFullPath();
			std::string FileName = "";
			size_t Count = 0;

			for (Count = FileFullPath.size(); Count > 0; Count--)
			{
				char a = FileFullPath[Count];
				if (FileFullPath[Count] == '\\')
				{
					break;
				}
			}

			for (size_t j = Count + 1; j < FileFullPath.size(); j++)
			{
				FileName.push_back(FileFullPath[j]);
			}

			GameEngineTexture::UnLoad(FileName);
		}
	}
}

