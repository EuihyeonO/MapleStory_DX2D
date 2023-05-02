#include "PrecompileHeader.h"
#include "Level_BeginnersTown.h"
#include "Player.h"

Level_BeginnersTown::Level_BeginnersTown()
{
}

Level_BeginnersTown::~Level_BeginnersTown()
{
}

void Level_BeginnersTown::Start()
{
	std::shared_ptr<Player> _Player = CreateActor<Player>();
}

void Level_BeginnersTown::Update(float _DeltaTime) 
{

}