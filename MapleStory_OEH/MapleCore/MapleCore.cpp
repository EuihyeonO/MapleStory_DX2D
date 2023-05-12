#include "PrecompileHeader.h"
#include "MapleCore.h"
#include "PlayerValue.h"
#include "Level_Title.h"
#include "Level_BeginnersTown1.h"

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCoreWindow.h>

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

	//GameEngineGUI::GUIWindowCreate<GameEngineCoreWindow>(" ");

	GameEngineCore::CreateLevel<Level_Title>();
	GameEngineCore::CreateLevel<Level_BeginnersTown1>();
	GameEngineCore::ChangeLevel("Level_BeginnersTown1");
}

void MapleCore::GameEnd()
{

}