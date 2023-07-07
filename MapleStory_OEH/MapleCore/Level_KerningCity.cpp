#include "PrecompileHeader.h"
#include "Level_KerningCity.h"
#include "Player.h"
#include "BottomBar.h"
#include "StatusWindow.h"
#include "Mouse.h"
#include "PlayerValue.h"
#include "UIWindowManager.h"
#include "QuickSlot.h"
#include "GlobalFunction.h"
#include "KerningCity.h"
#include "UIController.h"
#include "MapleCore.h"

#include <GameEnginePlatform/GameEngineSound.h>

Level_KerningCity::Level_KerningCity()
{
}

Level_KerningCity::~Level_KerningCity()
{
}

void Level_KerningCity::Start()
{
	SetName("KERNINGCITY");

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetCamera(100)->SetProjectionType(CameraType::Orthogonal);

	GetMainCamera()->SetSortType(0, SortType::ZSort);
	GetCamera(100)->SetSortType(0, SortType::ZSort);
}

void Level_KerningCity::Update(float _DeltaTime)
{

}

void Level_KerningCity::LevelChangeStart()
{
	LoadResources();
	ActorCreate();

}

void Level_KerningCity::LevelChangeEnd()
{
	ActorDeath();
	UnLoadResources();
}

void Level_KerningCity::ActorCreate()
{
	if (Map == nullptr)
	{
		Map = CreateActor<KerningCity>();
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


	if (PlayerValue::GetValue()->GetPrevLevelName() == "Level_SouthFerry")
	{
		MyPlayer->SetRight();
		MyPlayer->SetMoveType("Jump");
		MyPlayer->GetTransform()->SetLocalPosition({ -1000, 200 });

		MapleCore::BGMPlayer.Stop();
		MapleCore::BGMPlayer = GameEngineSound::Play("KerningCity.mp3");
		MapleCore::BGMPlayer.SetVolume(0.3f);
	}
	else if (PlayerValue::GetValue()->GetPrevLevelName() == "123")
	{
		MyPlayer->SetLeft();
		MyPlayer->SetMoveType("Jump");
		MyPlayer->GetTransform()->SetLocalPosition({ 625, -10 });
	}
}

void Level_KerningCity::ActorDeath()
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

void Level_KerningCity::LoadResources()
{
	if (nullptr == GameEngineTexture::Find("KerningCity.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("KerningCity");
		NewDir.Move("KerningCityNotSprite");

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
		NewDir.Move("KerningCity");
		NewDir.Move("KerningCityNotSprite");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::ReLoad(File[i].GetFullPath());
		}
	}
}

void Level_KerningCity::UnLoadResources()
{
	if (nullptr != GameEngineTexture::Find("KerningCity.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("KerningCity");
		NewDir.Move("KerningCityNotSprite");

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

