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
		MyPlayer->SetLeft();
		MyPlayer->SetMoveType("Jump");
		MyPlayer->GetTransform()->SetLocalPosition({ 625, -10 });
	}

	if (Map != nullptr)
	{
		std::string ColMapName = Map->GetColMapName().data();
		std::shared_ptr<GameEngineTexture> ColMap = GameEngineTexture::Find(ColMapName);

		GlobalFunction::GetValue()->SetColMap(ColMap);
	}
}

void Level_BeginnersTown1::LevelChangeEnd()
{
	if (MyMouse != nullptr)
	{
		PlayerValue::GetValue()->SetPrevLevelName("Level_BeginnersTown1");
	}

	if (MyUIWindowManager != nullptr)
	{
		MyUIWindowManager->AllWindowDeath();
	}

}

void Level_BeginnersTown1::Start()
{
	SetName("BEGINNERSTOWN1");

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetCamera(100)->SetProjectionType(CameraType::Orthogonal);

	GetMainCamera()->SetSortType(0 , SortType::ZSort);
	GetCamera(100)->SetSortType(0 , SortType::ZSort);

	Map = CreateActor<BeginnersTown1>();

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

void Level_BeginnersTown1::Update(float _DeltaTime)
{

}