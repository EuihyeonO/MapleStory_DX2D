#include "PrecompileHeader.h"
#include "Level_BeginnersTown2.h"
#include "BeginnersTown2.h"
#include "Player.h"
#include "BottomBar.h"
#include "StatusWindow.h"
#include "Mouse.h"
#include "PlayerValue.h"
#include "UIWindowManager.h"
#include "QuickSlot.h"

#include <GameEngineCore/GameEngineCamera.h>

Level_BeginnersTown2::Level_BeginnersTown2()
{
}

Level_BeginnersTown2::~Level_BeginnersTown2()
{
}

void Level_BeginnersTown2::LevelChangeStart()
{
	if (MyPlayer != nullptr)
	{
		MyPlayer->SetCurPlayer(MyPlayer);
	}

	if (MyMouse != nullptr)
	{
		MyMouse->SetCurMouse(MyMouse);
	}

	if (PlayerValue::GetValue()->GetPrevLevelName() == "Level_BeginnersTown1")
	{
		MyPlayer->SetRight();
		MyPlayer->SetMoveType("Jump");
		MyPlayer->GetTransform()->SetLocalPosition({ -460, 45 });
	}
}

void Level_BeginnersTown2::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);

	Map = CreateActor<BeginnersTown2>(static_cast<int>(RenderOrder::BasicMap));
	
	MyPlayer = CreateActor<Player>(static_cast<int>(RenderOrder::Player));
	
	MyPlayer->SetRight();
	MyPlayer->SetColMap(Map->GetColMapName());
	MyPlayer->SetCurPlayer(MyPlayer);

	CreateActor<QuickSlot>(static_cast<int>(RenderOrder::UI));
	CreateActor<BottomBar>(static_cast<int>(RenderOrder::UI));
	MyUIWindowManager = CreateActor<UIWindowManager>(static_cast<int>(RenderOrder::UI));
	MyMouse = CreateActor<Mouse>(static_cast<int>(RenderOrder::Mouse));
	MyMouse->SetCurMouse(MyMouse);
}

void Level_BeginnersTown2::LevelChangeEnd()
{
	if (MyMouse != nullptr)
	{
		PlayerValue::GetValue()->SetPrevLevelName("Level_BeginnersTown2");
	}

	if (MyUIWindowManager != nullptr)
	{
		MyUIWindowManager->AllWindowDeath();
	}
}
void Level_BeginnersTown2::Update(float _DeltaTime)
{

}