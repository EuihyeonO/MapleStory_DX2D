#include "PrecompileHeader.h"
#include "Level_AlterOfZakum.h"
#include "Player.h"
#include "BottomBar.h"
#include "StatusWindow.h"
#include "Mouse.h"
#include "SkillWindow.h"
#include "UIWindowManager.h"
#include "QuickSlot.h"
#include "PlayerValue.h"
#include "GlobalFunction.h"
#include "AlterOfZakum.h"

Level_AlterOfZakum::Level_AlterOfZakum()
{
}

Level_AlterOfZakum::~Level_AlterOfZakum()
{
}

void Level_AlterOfZakum::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetCamera(100)->SetProjectionType(CameraType::Orthogonal);

	GetMainCamera()->SetSortType(0, SortType::ZSort);
	GetCamera(100)->SetSortType(0, SortType::ZSort);

	Map = CreateActor<AlterOfZakum>();

	MyPlayer = CreateActor<Player>();
	MyPlayer->SetRight();
	MyPlayer->SetColMap(Map->GetColMapName());
	MyPlayer->SetCurPlayer(MyPlayer);

	CreateActor<QuickSlot>();
	CreateActor<BottomBar>();
	MyUIWindowManager = CreateActor<UIWindowManager>();
	MyMouse = CreateActor<Mouse>();
	MyMouse->SetCurMouse(MyMouse);
}

void Level_AlterOfZakum::Update(float _DeltaTime)
{
}

void Level_AlterOfZakum::LevelChangeStart()
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
		//MyPlayer->SetLeft();
		//MyPlayer->SetMoveType("Jump");
		//MyPlayer->GetTransform()->SetLocalPosition({ 625, -10 });
	}

	if (Map != nullptr)
	{
		std::string ColMapName = Map->GetColMapName().data();
		std::shared_ptr<GameEngineTexture> ColMap = GameEngineTexture::Find(ColMapName);

		GlobalFunction::GetValue()->SetColMap(ColMap);
	}
}

void Level_AlterOfZakum::LevelChangeEnd()
{
	if (MyMouse != nullptr)
	{
		PlayerValue::GetValue()->SetPrevLevelName("Level_AlterOfZakum");
	}

	if (MyUIWindowManager != nullptr)
	{
		MyUIWindowManager->AllWindowDeath();
	}
}