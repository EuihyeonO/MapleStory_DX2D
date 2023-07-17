#include "PrecompileHeader.h"
#include "Level_ZakumRoad2.h"
#include "ZakumRoad2.h"
#include "GlobalFunction.h"
#include "Player.h"
#include "Mouse.h"
#include "PlayerValue.h"
#include "QuickSlot.h"
#include "BottomBar.h"
#include "UIWindowManager.h"
#include "KeyBox.h"
#include "BigBox.h"
#include "UIController.h"
#include "MapleCore.h"

Level_ZakumRoad2::Level_ZakumRoad2()
{
}

Level_ZakumRoad2::~Level_ZakumRoad2()
{
}

void Level_ZakumRoad2::Start() 
{
	SetName("ZAKUMROAD2");

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetCamera(100)->SetProjectionType(CameraType::Orthogonal);

	GetMainCamera()->SetSortType(0, SortType::ZSort);
	GetCamera(100)->SetSortType(0, SortType::ZSort);
}

void Level_ZakumRoad2::Update(float _DeltaTime) 
{

}

void Level_ZakumRoad2::LevelChangeStart() 
{
	LoadResources();
	ActorCreate();

	MyPlayer->GetTransform()->SetLocalPosition({ -2000, 0.0f });
}

void Level_ZakumRoad2::LevelChangeEnd() 
{
	ActorDeath();
	UnLoadResources();
}

void Level_ZakumRoad2::ActorCreate()
{
	if (Map == nullptr)
	{
		Map = CreateActor<ZakumRoad2>();
		std::string ColMapName = Map->GetColMapName().data();
		std::shared_ptr<GameEngineTexture> ColMap = GameEngineTexture::Find(ColMapName);
		GlobalFunction::GetValue()->SetColMap(ColMap);
	}

	if (MyPlayer == nullptr)
	{
		MyPlayer = CreateActor<Player>();
		MyPlayer->SetCurPlayer(MyPlayer);
		MyPlayer->SetColMap(Map->GetColMapName());
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
}

void Level_ZakumRoad2::ActorDeath()
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
		//Map->ActorDeath();

		Map = nullptr;
	}
}

void Level_ZakumRoad2::LoadResources()
{
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("MapleResources");
	NewDir.Move("MapleResources");
	NewDir.Move("ZakumRoad2");
	NewDir.Move("ZakumRoad2NotSprite");

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

		if (GameEngineTexture::Find(FileName) != nullptr)
		{
			GameEngineTexture::ReLoad(File[i].GetFullPath());
		}
		else
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	if (GameEngineSprite::Find("StoneTrap") == nullptr)
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("ZakumRoad2");
		NewDir.Move("ZakumRoad2Sprite");
		
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("StoneTrap").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SteamTrap").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Lira").GetFullPath());
	}
	else if (GameEngineSprite::Find("StoneTrap") != nullptr)
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("ZakumRoad2");
		NewDir.Move("ZakumRoad2Sprite");

		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("StoneTrap").GetFullPath());
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("SteamTrap").GetFullPath());
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("Lira").GetFullPath());
	}
}

void Level_ZakumRoad2::UnLoadResources()
{
	if (nullptr != GameEngineTexture::Find("ZakumRoad2.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("ZakumRoad2");
		NewDir.Move("ZakumRoad2NotSprite");

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

	if (GameEngineSprite::Find("StoneTrap") != nullptr)
	{
		GameEngineSprite::UnLoad("StoneTrap");
		GameEngineSprite::UnLoad("SteamTrap");
		GameEngineSprite::UnLoad("Lira");
	}
}
