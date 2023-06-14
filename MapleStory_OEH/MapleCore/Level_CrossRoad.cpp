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

	Map = CreateActor<CrossRoad>(static_cast<int>(RenderOrder::BasicMap));

	MyPlayer = CreateActor<Player>(static_cast<int>(RenderOrder::Player));

	MyPlayer->SetRight();
	MyPlayer->SetColMap(Map->GetColMapName());
	MyPlayer->SetCurPlayer(MyPlayer);

	CreateActor<QuickSlot>();
	CreateActor<BottomBar>();
	MyUIWindowManager = CreateActor<UIWindowManager>();
	MyMouse = CreateActor<Mouse>();
	MyMouse->SetCurMouse(MyMouse);
}

void Level_CrossRoad::Update(float _DeltaTime)
{
}

void Level_CrossRoad::LevelChangeStart()
{
	if (MyPlayer != nullptr)
	{
		MyPlayer->SetCurPlayer(MyPlayer);
	}

	if (MyMouse != nullptr)
	{
		MyMouse->SetCurMouse(MyMouse);
	}

	if (PlayerValue::GetValue()->GetPrevLevelName() == "Level_BeginnersTown2")
	{
		MyPlayer->SetRight();
		MyPlayer->SetMoveType("Jump");
		MyPlayer->GetTransform()->SetLocalPosition({ -1750, 45 });
		GetMainCamera()->GetTransform()->SetLocalPosition({ -1750, 45 });
	}

	if (Map != nullptr)
	{
		std::string ColMapName = Map->GetColMapName().data();
		std::shared_ptr<GameEngineTexture> ColMap = GameEngineTexture::Find(ColMapName);

		GlobalFunction::GetValue()->SetColMap(ColMap);
	}
}

void Level_CrossRoad::LevelChangeEnd()
{
	if (MyMouse != nullptr)
	{
		PlayerValue::GetValue()->SetPrevLevelName("Level_CrossRoad");
	}

	if (MyUIWindowManager != nullptr)
	{
		MyUIWindowManager->AllWindowDeath();
	}
}