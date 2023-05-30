#include "PrecompileHeader.h"
#include "MapleCore.h"
#include "PlayerValue.h"
#include "Level_Title.h"
#include "Level_BeginnersTown1.h"
#include "Level_BeginnersTown2.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEnginePixelShader.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>

MapleCore::MapleCore()
{
}

MapleCore::~MapleCore()
{
}

void MapleCore::ContentsResourcesCreate()
{
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("MapleResources");
	NewDir.Move("MapleResources");
	NewDir.Move("ContentShader");

	std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".hlsl", ".fx" });

	GameEngineVertexShader::Load(Files[0].GetFullPath(), "Content_VS");
	GameEnginePixelShader::Load(Files[0].GetFullPath(), "Content_PS");

	std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("ContentShader");

	Pipe->SetVertexBuffer("Rect");
	Pipe->SetIndexBuffer("Rect");
	Pipe->SetVertexShader("ContentShader.hlsl");
	Pipe->SetRasterizer("Engine2DBase");
	Pipe->SetPixelShader("ContentShader.hlsl");
	Pipe->SetBlendState("AlphaBlend");
	Pipe->SetDepthState("EngineDepth");
}

void MapleCore::GameStart()
{
	ContentsResourcesCreate();
	//GameEngineGUI::GUIWindowCreate<GameEngineCoreWindow>(" ");

	GameEngineCore::CreateLevel<Level_Title>();
	GameEngineCore::CreateLevel<Level_BeginnersTown1>();
	GameEngineCore::CreateLevel<Level_BeginnersTown2>();
	GameEngineCore::ChangeLevel("Level_BeginnersTown1");
}

void MapleCore::GameEnd()
{

}