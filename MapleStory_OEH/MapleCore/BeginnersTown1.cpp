#include "PrecompileHeader.h"
#include "BeginnersTown1.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <ctime>

BeginnersTown1::BeginnersTown1()
{
}

BeginnersTown1::~BeginnersTown1()
{
}

void BeginnersTown1::Start()
{
	LandScape0 = CreateComponent<GameEngineSpriteRenderer>();
	LandScape0->SetTexture("MapBackGround0.png");
	LandScape0->GetTransform()->SetLocalScale({2000, 2000});

	Cloud0 = CreateComponent<GameEngineSpriteRenderer>();
	Cloud0->SetScaleToTexture("MapBackGround1.png");
	Cloud0->GetTransform()->SetLocalPosition({ 0, 250 });
	Cloud1 = CreateComponent<GameEngineSpriteRenderer>();
	Cloud1->SetScaleToTexture("MapBackGround1.png");
	Cloud1->GetTransform()->SetLocalPosition({ -1024, 250 });
	Cloud2 = CreateComponent<GameEngineSpriteRenderer>();
	Cloud2->SetScaleToTexture("MapBackGround1.png");
	Cloud2->GetTransform()->SetLocalPosition({ 1024, 250 });

	LandScape2 = CreateComponent<GameEngineSpriteRenderer>();
	LandScape2->SetScaleToTexture("MapBackGround2.png");
	LandScape2->GetTransform()->SetLocalPosition({0, 200});

	BackGroundLayer = CreateComponent<GameEngineSpriteRenderer>();
	BackGroundLayer->SetScaleToTexture("BeginnersTown1Layer.png");

	BackGround = CreateComponent<GameEngineSpriteRenderer>();
	BackGround->SetScaleToTexture("BeginnersTown1.png");
	
	Rope = CreateComponent<GameEngineSpriteRenderer>();
	Rope->SetScaleToTexture("BeginnersTown1Rope.png");

}

void BeginnersTown1::Update(float _DeltaTime)
{

	XMoveTime += 0.05f * _DeltaTime;

	if (XMoveTime > 1.0f)
	{
		XMoveTime -= 1.0f;
	}

	Cloud0->SetMoveTime({ XMoveTime, 0 });
	Cloud1->SetMoveTime({ XMoveTime, 0 });
	Cloud2->SetMoveTime({ XMoveTime, 0 });

}

void BeginnersTown1::Render(float _DeltaTime) 
{
}