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
}

void Level_BeginnersTown1::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetCamera(100)->SetSortType(100, SortType::ZSort);

	Map = CreateActor<BeginnersTown1>(static_cast<int>(RenderOrder::BasicMap));

	MyPlayer = CreateActor<Player>(static_cast<int>(RenderOrder::Player));
	MyPlayer->SetRight();
	MyPlayer->SetColMap(Map->GetColMapName());
	MyPlayer->SetCurPlayer(MyPlayer);

	CreateActor<QuickSlot>(static_cast<int>(RenderOrder::UI));
	CreateActor<BottomBar>(static_cast<int>(RenderOrder::UI));
	CreateActor<UIWindowManager>(static_cast<int>(RenderOrder::UI));
	MyMouse = CreateActor<Mouse>(static_cast<int>(RenderOrder::Mouse));
	MyMouse->SetCurMouse(MyMouse);
}

void Level_BeginnersTown1::Update(float _DeltaTime)
{

}