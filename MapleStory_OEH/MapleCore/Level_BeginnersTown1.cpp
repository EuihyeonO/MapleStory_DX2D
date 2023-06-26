#include "PrecompileHeader.h"
#include "Level_BeginnersTown1.h"
#include "BeginnersTown1.h"
#include "Player.h"
#include "BottomBar.h"
#include "StatusWindow.h"
#include "Mouse.h"
#include "SkillWindow.h"
#include "UIWindowManager.h"
#include "QuickSlot.h"
#include "PlayerValue.h"
#include "GlobalFunction.h"

#include <GameEngineCore/GameEngineCamera.h>

Level_BeginnersTown1::Level_BeginnersTown1()
{

}

Level_BeginnersTown1::~Level_BeginnersTown1()
{
	
}

void Level_BeginnersTown1::LevelChangeStart()
{
	LoadResources();
	ActorCreate();

	if (PlayerValue::GetValue()->GetPrevLevelName() == "Level_Title")
	{
		MyPlayer->SetRight();
		MyPlayer->SetMoveType("Jump");
		MyPlayer->GetTransform()->SetLocalPosition({ -500, 200 });
	}
	else if (PlayerValue::GetValue()->GetPrevLevelName() == "Level_BeginnersTown2")
	{
		MyPlayer->SetLeft();
		MyPlayer->SetMoveType("Jump");
		MyPlayer->GetTransform()->SetLocalPosition({ 625, -10 });
	}
}

void Level_BeginnersTown1::LevelChangeEnd()
{
	if (MyMouse != nullptr)
	{
		PlayerValue::GetValue()->SetPrevLevelName("Level_BeginnersTown1");
	}

	ActorDeath();
	UnLoadResources();
}

void Level_BeginnersTown1::Start()
{
	SetName("BEGINNERSTOWN1");

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetCamera(100)->SetProjectionType(CameraType::Orthogonal);

	GetMainCamera()->SetSortType(0 , SortType::ZSort);
	GetCamera(100)->SetSortType(0 , SortType::ZSort);
}

void Level_BeginnersTown1::Update(float _DeltaTime)
{

}

void Level_BeginnersTown1::ActorCreate()
{

	if (Map == nullptr)
	{
		Map = CreateActor<BeginnersTown1>();
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


}

void Level_BeginnersTown1::ActorDeath()
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
		Map->ActorDeath();
		Map->Death();
		Map = nullptr;
	}

}

void Level_BeginnersTown1::LoadResources()
{
	if (nullptr == GameEngineTexture::Find("HinaNormal0.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("BeginnersTown1");
		NewDir.Move("NotSprite");

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
		NewDir.Move("BeginnersTown1");
		NewDir.Move("NotSprite");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::ReLoad(File[i].GetFullPath());
		}
	}
}

void Level_BeginnersTown1::UnLoadResources()
{
	if (nullptr != GameEngineTexture::Find("HinaNormal0.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("BeginnersTown1");
		NewDir.Move("NotSprite");

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