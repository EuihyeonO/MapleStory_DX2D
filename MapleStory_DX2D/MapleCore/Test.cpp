#include "PrecompileHeader.h"
#include "Test.h"

#include "PlayerValue.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <ctime>

Test::Test()
{
}

Test::~Test()
{
}


void Test::Update(float _DeltaTime)
{

	//TimeCount();

	//RenderTime += CountTime;

	//if (RenderTime >= 0.03f)
	//{
	//	if (RenderIndex == 180)
	//	{
	//		return;
	//	}

	//	RenderIndex++;

	//	std::string Index = "Scene" + std::to_string(RenderIndex) + ".png";
	//	
	//	Render1->GetShaderResHelper().SetTexture("DiffuseTex", Index);
	//	RenderTime = 0.0f;
	//}

	
}

void Test::Start()
{
	Render1 = CreateComponent<GameEngineSpriteRenderer>();
	Render1->SetPipeLine("2DTexture");
	Render1->GetShaderResHelper().SetTexture("DiffuseTex", "AAAA.png");
	Render1->GetTransform()->SetLocalScale({800.0f, 600.0f, 0.0f});
	TimeCount();

	Color2 = { 0, 0, 0, 1.0f };

	Render0 = CreateComponent<GameEngineSpriteRenderer>();
	Render0->SetPipeLine("2DTexture");
	Render0->GetShaderResHelper().SetTexture("DiffuseTex", "Test.png");

	Color = { 0, 0, 0, 0.5f };

	Render0->GetTransform()->SetLocalScale({ 800.0f, 600.0f, 0.0f });

	int a = 0;
}

// 이건 디버깅용도나 
void Test::Render(float _Delta)
{
};


void Test::TimeCount()
{
	CurTime = static_cast<float>(clock());

	CountTime = (CurTime - PrevTime) / 1000.0f;

	PrevTime = CurTime;
}