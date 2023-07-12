#include "PrecompileHeader.h"
#include "MapleCore.h"
#include "PlayerValue.h"
#include "Level_Title.h"
#include "Level_BeginnersTown1.h"
#include "Level_BeginnersTown2.h"
#include "Level_CrossRoad.h"
#include "Level_AlterOfZakumEnt.h"
#include "Level_AlterOfZakum.h"
#include "Level_ZakumRoad1.h"
#include "Level_ZakumRoad2.h"
#include "Level_SouthFerry.h"
#include "Level_KerningCity.h"
#include "Level_JazzBar.h"

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEnginePixelShader.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEngineRenderTarget.h>

GameEngineSoundPlayer MapleCore::MapleCore::BGMPlayer;

MapleCore::MapleCore()
{
}

MapleCore::~MapleCore()
{
}

void MapleCore::ContentsResourcesCreate()
{


	{//D3D11_FILTER_MIN_MAG_MIP_POINT
		D3D11_SAMPLER_DESC SamperData = {};
		SamperData.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		SamperData.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		SamperData.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		SamperData.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

		// ≈ÿΩ∫√≥∞° ∏÷∏Æ¿÷¿ª∂ß π∂∞∂≤®≥ƒ
		// æ»π∂∞µ¥Ÿ.
		SamperData.MipLODBias = 0.0f;
		SamperData.MaxAnisotropy = 1;
		SamperData.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		SamperData.MinLOD = -FLT_MAX;
		SamperData.MaxLOD = FLT_MAX;

		GameEngineSampler::ReSetting("ENGINEBASE", SamperData);
	}

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
	GameEngineCore::CreateLevel<Level_ZakumRoad1>();
	GameEngineCore::CreateLevel<Level_ZakumRoad2>();
	GameEngineCore::CreateLevel<Level_AlterOfZakum>();
	GameEngineCore::CreateLevel<Level_AlterOfZakumEnt>();
	GameEngineCore::CreateLevel<Level_SouthFerry>();
	GameEngineCore::CreateLevel<Level_KerningCity>();
	GameEngineCore::CreateLevel<Level_JazzBar>();
	GameEngineCore::ChangeLevel("Level_Title");
}

void MapleCore::GameEnd()
{

}