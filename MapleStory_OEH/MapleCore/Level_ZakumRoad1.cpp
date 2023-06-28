#include "PrecompileHeader.h"
#include "Level_ZakumRoad1.h"
#include "ZakumRoad1.h"
#include "GlobalFunction.h"
#include "Player.h"
#include "Mouse.h"
#include "PlayerValue.h"
#include "QuickSlot.h"
#include "BottomBar.h"
#include "UIWindowManager.h"
#include "KeyBox.h"

Level_ZakumRoad1::Level_ZakumRoad1()
{
}

Level_ZakumRoad1::~Level_ZakumRoad1()
{
}

void Level_ZakumRoad1::Start()
{
	SetName("ZAKUMROAD1");

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetCamera(100)->SetProjectionType(CameraType::Orthogonal);

	GetMainCamera()->SetSortType(0, SortType::ZSort);
	GetCamera(100)->SetSortType(0, SortType::ZSort);
}

void Level_ZakumRoad1::Update(float _DeltaTime)
{

}

void Level_ZakumRoad1::LevelChangeStart()
{
	LoadResources();
	ActorCreate();
}

void Level_ZakumRoad1::LevelChangeEnd()
{
	ActorDeath();
	UnLoadResources();
}



void Level_ZakumRoad1::ActorCreate()
{
	if (Map == nullptr)
	{
		Map = CreateActor<ZakumRoad1>();
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

	std::shared_ptr<KeyBox> NewBox = CreateActor<KeyBox>();

}

void Level_ZakumRoad1::ActorDeath()
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

void Level_ZakumRoad1::LoadResources()
{
	if (nullptr == GameEngineTexture::Find("ZakumRoad1.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("ZakumRoad1");
		NewDir.Move("ZakumRoad1NotSprite");

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
		NewDir.Move("ZakumRoad1");
		NewDir.Move("ZakumRoad1NotSprite");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::ReLoad(File[i].GetFullPath());
		}
	}

	if (nullptr == GameEngineSprite::Find("KeyBox0Hit.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("ZakumRoad1");
		NewDir.Move("ZakumRoad1Sprite");
		NewDir.Move("KeyBox");
		NewDir.Move("KeyBox0");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("KeyBox0Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("KeyBox0Stand").GetFullPath());

		NewDir.MoveParent();
		NewDir.Move("KeyBox1");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("KeyBox1Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("KeyBox1Stand").GetFullPath());

		NewDir.MoveParent();
		NewDir.Move("KeyBox2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("KeyBox2Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("KeyBox2Stand").GetFullPath());

		NewDir.MoveParent();
		NewDir.Move("KeyBox3");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("KeyBox3Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("KeyBox3Stand").GetFullPath());
	}
	else
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("ZakumRoad1");
		NewDir.Move("ZakumRoad1Sprite");
		NewDir.Move("KeyBox");
		NewDir.Move("KeyBox0");

		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("KeyBox0Hit").GetFullPath());
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("KeyBox0Stand").GetFullPath());

		NewDir.MoveParent();
		NewDir.Move("KeyBox1");

		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("KeyBox1Hit").GetFullPath());
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("KeyBox1Stand").GetFullPath());

		NewDir.MoveParent();
		NewDir.Move("KeyBox2");

		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("KeyBox2Hit").GetFullPath());
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("KeyBox2Stand").GetFullPath());

		NewDir.MoveParent();
		NewDir.Move("KeyBox3");

		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("KeyBox3Hit").GetFullPath());
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("KeyBox3Stand").GetFullPath());
	}
}

void Level_ZakumRoad1::UnLoadResources()
{
	if (nullptr != GameEngineTexture::Find("ZakumRoad1.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("ZakumRoad1");
		NewDir.Move("ZakumRoad1NotSprite");

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

	if (nullptr != GameEngineSprite::Find("KeyBox0Hit.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("ZakumRoad1");
		NewDir.Move("ZakumRoad1Sprite");
		NewDir.Move("KeyBox");
		NewDir.Move("KeyBox0");

		GameEngineSprite::UnLoad(NewDir.GetPlusFileName("KeyBox0Hit").GetFullPath());
		GameEngineSprite::UnLoad(NewDir.GetPlusFileName("KeyBox0Stand").GetFullPath());

		NewDir.MoveParent();
		NewDir.Move("KeyBox1");

		GameEngineSprite::UnLoad(NewDir.GetPlusFileName("KeyBox1Hit").GetFullPath());
		GameEngineSprite::UnLoad(NewDir.GetPlusFileName("KeyBox1Stand").GetFullPath());

		NewDir.MoveParent();
		NewDir.Move("KeyBox2");

		GameEngineSprite::UnLoad(NewDir.GetPlusFileName("KeyBox2Hit").GetFullPath());
		GameEngineSprite::UnLoad(NewDir.GetPlusFileName("KeyBox2Stand").GetFullPath());

		NewDir.MoveParent();
		NewDir.Move("KeyBox3");

		GameEngineSprite::UnLoad(NewDir.GetPlusFileName("KeyBox3Hit").GetFullPath());
		GameEngineSprite::UnLoad(NewDir.GetPlusFileName("KeyBox3Stand").GetFullPath());
	}
}

