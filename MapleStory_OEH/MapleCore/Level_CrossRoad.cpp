#include "PrecompileHeader.h"
#include "Level_CrossRoad.h"

#include "Player.h"
#include "UIWindowManager.h"
#include "Mouse.h"
#include "PlayerValue.h"
#include "GlobalFunction.h"
#include "BeginnersTown2.h"
#include "CrossRoad.h"
#include "QuickSlot.h"
#include "BottomBar.h"

Level_CrossRoad::Level_CrossRoad()
{
}

Level_CrossRoad::~Level_CrossRoad()
{
}


void Level_CrossRoad::Start()
{
	SetName("CROSSROAD");

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetCamera(100)->SetProjectionType(CameraType::Orthogonal);

	GetMainCamera()->SetSortType(0, SortType::ZSort);
	GetCamera(100)->SetSortType(0, SortType::ZSort);
}

void Level_CrossRoad::Update(float _DeltaTime)
{
}

void Level_CrossRoad::LevelChangeStart()
{
	LoadResources();
	ActorCreate();

	if (PlayerValue::GetValue()->GetPrevLevelName() == "Level_BeginnersTown2")
	{
		MyPlayer->SetRight();
		MyPlayer->SetMoveType("Jump");
		MyPlayer->GetTransform()->SetLocalPosition({ -1750, 45 });
		GetMainCamera()->GetTransform()->SetLocalPosition({ -1750, 45 });
	}
}

void Level_CrossRoad::LevelChangeEnd()
{
	PlayerValue::GetValue()->SetPrevLevelName("Level_CrossRoad");

	ActorDeath();
	UnLoadResources();
}

void Level_CrossRoad::ActorCreate()
{

	if (Map == nullptr)
	{
		Map = CreateActor<CrossRoad>();
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

void Level_CrossRoad::ActorDeath()
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

void Level_CrossRoad::LoadResources()
{
	if (nullptr == GameEngineTexture::Find("CrossRoad.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("CrossRoad");
		NewDir.Move("CrossRoadNotSprite");

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
		NewDir.Move("CrossRoad");
		NewDir.Move("CrossRoadNotSprite");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::ReLoad(File[i].GetFullPath());
		}
	}

	if (nullptr == GameEngineSprite::Find("GreenSnailDeath"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("CrossRoad");
		NewDir.Move("CrossRoadSprite");
		NewDir.Move("GreenSnail");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GreenSnailDeath").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GreenSnailHit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GreenSnailMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GreenSnailStand").GetFullPath());

		NewDir.MoveParent();
		NewDir.Move("Spore");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SporeDeath").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SporeHit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SporeMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SporeStand").GetFullPath());

		NewDir.MoveParent();
		NewDir.Move("BlueSnail");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("BlueSnailDeath").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("BlueSnailHit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("BlueSnailMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("BlueSnailStand").GetFullPath());
	}
	else
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("CrossRoad");
		NewDir.Move("CrossRoadSprite");
		NewDir.Move("GreenSnail");

		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("GreenSnailDeath").GetFullPath());
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("GreenSnailHit").GetFullPath());
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("GreenSnailMove").GetFullPath());
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("GreenSnailStand").GetFullPath());

		NewDir.MoveParent();
		NewDir.Move("Spore");

		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("SporeDeath").GetFullPath());
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("SporeHit").GetFullPath());
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("SporeMove").GetFullPath());
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("SporeStand").GetFullPath());

		NewDir.MoveParent();
		NewDir.Move("BlueSnail");

		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("BlueSnailDeath").GetFullPath());
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("BlueSnailHit").GetFullPath());
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("BlueSnailMove").GetFullPath());
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("BlueSnailStand").GetFullPath());
	}
}

void Level_CrossRoad::UnLoadResources()
{
	if (nullptr != GameEngineTexture::Find("RozarStand0.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("CrossRoad");
		NewDir.Move("CrossRoadNotSprite");

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

	if (nullptr != GameEngineSprite::Find("GreenSnailDeath"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("CrossRoad");
		NewDir.Move("CrossRoadSprite");
		NewDir.Move("GreenSnail");

		GameEngineSprite::UnLoad("GreenSnailDeath");
		GameEngineSprite::UnLoad("GreenSnailHit");
		GameEngineSprite::UnLoad("GreenSnailMove");
		GameEngineSprite::UnLoad("GreenSnailStand");

		NewDir.MoveParent();
		NewDir.Move("Spore");

		GameEngineSprite::UnLoad("SporeDeath");
		GameEngineSprite::UnLoad("SporeHit");
		GameEngineSprite::UnLoad("SporeMove");
		GameEngineSprite::UnLoad("SporeStand");

		NewDir.MoveParent();
		NewDir.Move("BlueSnail");

		GameEngineSprite::UnLoad("BlueSnailDeath");
		GameEngineSprite::UnLoad("BlueSnailHit");
		GameEngineSprite::UnLoad("BlueSnailMove");
		GameEngineSprite::UnLoad("BlueSnailStand");
	}
}