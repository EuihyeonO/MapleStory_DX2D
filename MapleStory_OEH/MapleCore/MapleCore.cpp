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
	// �ؽ�ó �ε常 �� �������� �ϰ� �����ϴ� ������ ���̼���.


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