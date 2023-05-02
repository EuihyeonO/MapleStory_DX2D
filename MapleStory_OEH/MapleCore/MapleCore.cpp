#include "PrecompileHeader.h"
#include "MapleCore.h"
#include "PlayerValue.h"
#include "Level_Title.h"
#include "Level_BeginnersTown.h"

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineLevel.h>


MapleCore::MapleCore()
{
}

MapleCore::~MapleCore()
{
}

void MapleCore::ContentsResourcesCreate()
{
	// 텍스처 로드만 각 레벨별로 하고 정리하는 습관을 들이세요.


}
void MapleCore::GameStart()
{
	GameEngineCore::CreateLevel<Level_Title>();
	//GameEngineCore::CreateLevel<Level_BeginnersTown>();
	GameEngineCore::ChangeLevel("Level_Title");
}

void MapleCore::GameEnd()
{

}