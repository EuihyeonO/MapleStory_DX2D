#include "PrecompileHeader.h"
#include "Level_AlterOfZakumEnt.h"
#include "AlterOfZakumEnt.h"
#include "Player.h"
#include "PlayerValue.h"
#include "Mouse.h"
#include "QuickSlot.h"
#include "BottomBar.h"
#include "GlobalFunction.h"
#include "UIWindowManager.h"
#include "MapleCore.h"

Level_AlterOfZakumEnt::Level_AlterOfZakumEnt()
{
}

Level_AlterOfZakumEnt::~Level_AlterOfZakumEnt()
{
}

void Level_AlterOfZakumEnt::Start() 
{
	SetName("ALTEROFZAKUMENT");

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetCamera(100)->SetProjectionType(CameraType::Orthogonal);

	GetMainCamera()->SetSortType(0, SortType::ZSort);
	GetCamera(100)->SetSortType(0, SortType::ZSort);
}

void Level_AlterOfZakumEnt::Update(float _DeltaTime) 
{

}

void Level_AlterOfZakumEnt::LevelChangeStart() 
{
	LoadResources();
	ActorCreate();
}

void Level_AlterOfZakumEnt::LevelChangeEnd() 
{
	UnLoadResources();
	ActorDeath();
}


void Level_AlterOfZakumEnt::ActorCreate()
{
	if (Map == nullptr)
	{
		Map = CreateActor<AlterOfZakumEnt>();
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

	MyPlayer->SetRight();
	MyPlayer->SetMoveType("Jump");

	MyPlayer->GetTransform()->SetLocalPosition({ -1200, -100, -5.0f });

	if (PlayerValue::GetValue()->GetPrevLevelName() != "Level_ZakumRoad1")
	{
		MapleCore::BGMPlayer.Stop();
		MapleCore::BGMPlayer = GameEngineSound::Play("HellGate.mp3");
	}
}

void Level_AlterOfZakumEnt::ActorDeath()
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

void Level_AlterOfZakumEnt::LoadResources()
{
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("MapleResources");
	NewDir.Move("MapleResources");
	NewDir.Move("AlterOfZakumEnt");
	NewDir.Move("AlterOfZakumEntNotSprite");

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

	if (nullptr == GameEngineSprite::Find("FireDewDrop"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakumEnt");
		NewDir.Move("AlterOfZakumEntSprite");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("FireDewDrop").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Adovis").GetFullPath());
	}
	else
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakumEnt");
		NewDir.Move("AlterOfZakumEntSprite");

		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("FireDewDrop").GetFullPath());
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("Adovis").GetFullPath());
	}
}

void Level_AlterOfZakumEnt::UnLoadResources()
{
	if (nullptr != GameEngineTexture::Find("AlterOfZakumEnt.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakumEnt");
		NewDir.Move("AlterOfZakumEntNotSprite");

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

	{
		GameEngineSprite::UnLoad("FireDewDrop");
		GameEngineSprite::UnLoad("Adovis");
	}
}

