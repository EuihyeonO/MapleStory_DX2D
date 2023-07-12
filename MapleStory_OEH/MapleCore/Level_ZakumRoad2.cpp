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
	if (nullptr == GameEngineTexture::Find("ZakumRoad2.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("ZakumRoad2");
		NewDir.Move("ZakumRoad2NotSprite");

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
		NewDir.Move("ZakumRoad2");
		NewDir.Move("ZakumRoad2NotSprite");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::ReLoad(File[i].GetFullPath());
		}
	}

}

void Level_ZakumRoad2::UnLoadResources()
{

}
