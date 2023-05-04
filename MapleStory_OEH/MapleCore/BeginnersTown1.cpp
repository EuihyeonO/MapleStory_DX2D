#include "PrecompileHeader.h"
#include "BeginnersTown1.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

BeginnersTown1::BeginnersTown1()
{
}

BeginnersTown1::~BeginnersTown1()
{
}

void BeginnersTown1::Start()
{
	BackGroundLayer = CreateComponent<GameEngineSpriteRenderer>();
	BackGroundLayer->SetScaleToTexture("BeginnersTown1Layer.png");

	BackGround = CreateComponent<GameEngineSpriteRenderer>();
	BackGround->SetScaleToTexture("BeginnersTown1.png");
}

void BeginnersTown1::Update(float _DeltaTime)
{
}

void BeginnersTown1::Render(float _DeltaTime) 
{
}