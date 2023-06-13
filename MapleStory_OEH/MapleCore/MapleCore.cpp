#include "PrecompileHeader.h"
#include "MapleCore.h"
#include "PlayerValue.h"
#include "Level_Title.h"
#include "Level_BeginnersTown1.h"
#include "Level_BeginnersTown2.h"
#include "Level_CrossRoad.h"
#include "Level_AlterOfZakum.h"

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEnginePixelShader.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEngineRenderTarget.h>

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

	//Pipe->SetVertexBuffer("Rect");
	//Pipe->SetIndexBuffer("Rect");
	Pipe->SetVertexShader("ContentShader.hlsl");
	Pipe->SetRasterizer("Engine2DBase");
	Pipe->SetPixelShader("ContentShader.hlsl");
	Pipe->SetBlendState("AlphaBlend");
	Pipe->SetDepthState("EngineDepth");
}

void MapleCore::GameStart()
{
	ContentsResourcesCreate();

	GameEngineCore::CreateLevel<Level_Title>();
	GameEngineCore::CreateLevel<Level_BeginnersTown1>();
	GameEngineCore::CreateLevel<Level_BeginnersTown2>();
	GameEngineCore::CreateLevel<Level_CrossRoad>();
	GameEngineCore::CreateLevel<Level_AlterOfZakum>();
	GameEngineCore::ChangeLevel("Level_Title");
}

void MapleCore::GameEnd()
{

}