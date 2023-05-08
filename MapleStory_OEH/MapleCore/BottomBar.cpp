#include "PrecompileHeader.h"
#include "BottomBar.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

BottomBar::BottomBar()
{
}

BottomBar::~BottomBar()
{
}

void BottomBar::Start()
{
	BottomBarBackGround = CreateComponent<GameEngineSpriteRenderer>();
	BottomBarBackGround->SetScaleToTexture("BottomBarBackGround.png");

	BottomBarLayer = CreateComponent<GameEngineSpriteRenderer>();
	BottomBarLayer->SetScaleToTexture("BottomBarLayer.png");

	StatusBar = CreateComponent<GameEngineSpriteRenderer>();
	StatusBar->SetScaleToTexture("StatusBar.png");
}

void BottomBar::Update(float _DeltaTime) 
{
	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();
	BottomBarBackGround->GetTransform()->SetLocalPosition({ CameraPos.x, CameraPos.y - 300 + 35});

	BottomBarLayer->GetTransform()->SetLocalPosition({ CameraPos.x - 400 + 285, CameraPos.y - 300 + 35 });
}

void BottomBar::Render(float _DeltaTime) 
{

}