#include "PrecompileHeader.h"
#include "MapleCore.h"
#include "Level_Title.h"

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineLevel.h>


MapleCore::MapleCore()
{
}

MapleCore::~MapleCore()
{
}

void MapleCore::GameStart()
{
	GameEngineCore::CreateLevel<Level_Title>();
	GameEngineCore::ChangeLevel("Level_Title");
}

void MapleCore::GameEnd()
{

}