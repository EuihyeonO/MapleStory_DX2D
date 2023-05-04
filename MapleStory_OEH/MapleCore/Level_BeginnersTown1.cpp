#include "PrecompileHeader.h"
#include "Level_BeginnersTown1.h"
#include "BeginnersTown1.h"
#include "Player.h"

#include <GameEngineCore/GameEngineCamera.h>

Level_BeginnersTown1::Level_BeginnersTown1()
{

}

Level_BeginnersTown1::~Level_BeginnersTown1()
{

}

void Level_BeginnersTown1::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);

	Map = CreateActor<BeginnersTown1>();

	MyPlayer = CreateActor<Player>();
	MyPlayer->SetRight();
	MyPlayer->SetColMap(Map->GetColMapName());
}

void Level_BeginnersTown1::Update(float _DeltaTime)
{

}