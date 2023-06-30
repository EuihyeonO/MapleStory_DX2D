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

#include <GameEngineBase/GameEngineRandom.h>


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

	IsDebugSwitch();
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

	//std::shared_ptr<KeyBox> NewBox = CreateActor<KeyBox>();
	//NewBox->GetTransform()->SetLocalPosition({ 0, -300 });

	//std::shared_ptr<KeyBox> NewBox1 = CreateActor<KeyBox>();
	//NewBox1->GetTransform()->SetLocalPosition({ -200, -300 });

	//std::shared_ptr<KeyBox> NewBox2 = CreateActor<KeyBox>();
	//NewBox2->GetTransform()->SetLocalPosition({ -400 , -300 });

	//std::shared_ptr<KeyBox> NewBox3 = CreateActor<KeyBox>();
	//NewBox3->GetTransform()->SetLocalPosition({ -600 , -300 });

	//std::shared_ptr<KeyBox> NewBox6 = CreateActor<KeyBox>();
	//NewBox6->GetTransform()->SetLocalPosition({ -800 , -300 }); 

	//std::shared_ptr<KeyBox> NewBox4 = CreateActor<KeyBox>();
	//NewBox4->GetTransform()->SetLocalPosition({ 500 , -150 });
	
	//std::shared_ptr<KeyBox> NewBox5 = CreateActor<KeyBox>();
	//NewBox5->GetTransform()->SetLocalPosition({ 700,  -150 });

	SetKeyBox();
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

void Level_ZakumRoad1::SetKeyBox()
{
	std::vector<int> NumVec;
	NumVec.reserve(5);

	std::function<bool(int)> IsDuplicated = [&NumVec](int _Num)
	{
		for (int i = 0; i < NumVec.size(); i++)
		{
			if (NumVec[i] == _Num)
			{
				return true;
			}
		}

		return false;
	};

	float4 StartPos = { 0, 0 };
	
	for(int i = 0; i < 10; i++)
	{
		int Index = GameEngineRandom::MainRandom.RandomInt(0, 28);
		
		while (IsDuplicated(Index) == true)
		{
			Index = GameEngineRandom::MainRandom.RandomInt(0, 28);
		}

		NumVec.push_back(Index);

		switch (Index)
		{
		case 0:
			StartPos = { -800, -300 };
			break;
		case 1:
			StartPos = { -600, -300 };
			break;
		case 2:
			StartPos = { -400, -300 };
			break;
		case 3:
			StartPos = { -200, -300 };
			break;
		case 4:
			StartPos = { 0, -300 };
			break;
		case 5:
			StartPos = { 450 , -200 };
			break;
		case 6:
			StartPos = { -200 , 0 };
			break;
		case 7:
			StartPos = { -50 , 0 };
			break;
		case 8:
			StartPos = { 250 , 300 };
			break;
		case 9:
			StartPos = { 100 , 300 };
			break;
		case 10:
			StartPos = { 600 , -200 };
			break;
		case 11:
			StartPos = { 750 , -200 };
			break;
		case 12:
			StartPos = { 100 , 0 };
			break;
		case 13:
			StartPos = { -350 , 0 };
			break;
		case 14:
			StartPos = { -350 , 200 };
			break;
		case 15:
			StartPos = { -200 , 200 };
			break;
		case 16:
			StartPos = { 570 , 0 };
			break;
		case 17:
			StartPos = { 720 , 0 };
			break;
		case 18:
			StartPos = { 420 , 0 };
			break;
		case 19:
			StartPos = { -280 , 500 };
			break;
		case 20:
			StartPos = { -130 , 500 };
			break;
		case 21:
			StartPos = { -600 , 100 };
			break;
		case 22:
			StartPos = { -780 , 100 };
			break;
		case 23:
			StartPos = { -580 , 400 };
			break;
		case 24:
			StartPos = { -730 , 400 };
			break;
		case 25:
			StartPos = { 630 , 700 };
			break;
		case 26:
			StartPos = { 780 , 700 };
			break;
		case 27:
			StartPos = { 480 , 700 };
			break;
		case 28:
			StartPos = { 330 , 700 };
			break;
		}

		std::shared_ptr<KeyBox> _NewBox = CreateActor<KeyBox>();
		_NewBox->SpawnStart(StartPos);
	}
}