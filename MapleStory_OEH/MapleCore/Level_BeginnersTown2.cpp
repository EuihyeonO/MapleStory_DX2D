#include "PrecompileHeader.h"
#include "Level_BeginnersTown2.h"
#include "BeginnersTown2.h"
#include "Player.h"
#include "BottomBar.h"
#include "StatusWindow.h"
#include "Mouse.h"

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
}

void Level_BeginnersTown2::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);

	Map = CreateActor<BeginnersTown2>(static_cast<int>(RenderOrder::BasicMap));
	
	MyPlayer = CreateActor<Player>(static_cast<int>(RenderOrder::Player));
	
	MyPlayer->SetRight();
	MyPlayer->SetColMap(Map->GetColMapName());
	MyPlayer->SetCurPlayer(MyPlayer);

	CreateActor<BottomBar>(static_cast<int>(RenderOrder::UI));
	CreateActor<StatusWindow>(static_cast<int>(RenderOrder::UI));
	CreateActor<Mouse>(static_cast<int>(RenderOrder::UI));
}

void Level_BeginnersTown2::Update(float _DeltaTime)
{

}