#include "PrecompileHeader.h"
#include "Test.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>

Test::Test()
{
}

Test::~Test()
{
}


void Test::Update(float _DeltaTime)
{

	float RotSpeed = 180.0f;

	float Speed = 200.0f;

	if (true == GameEngineInput::IsPress("TestSpeedBoost"))
	{
		Speed = 500.0f;
	}

	if (true == GameEngineInput::IsPress("TestMoveLeft"))
	{
		GetTransform()->AddLocalPosition(float4::Left * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("TestMoveRight"))
	{
		GetTransform()->AddLocalPosition(float4::Right * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("TestMoveUp"))
	{
		GetTransform()->AddLocalPosition(float4::Up * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("TestMoveDown"))
	{
		GetTransform()->AddLocalPosition(float4::Down * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("TestMoveForward"))
	{
		GetTransform()->AddLocalPosition(GetTransform()->GetLocalForwardVector() * Speed * _DeltaTime);
		// GetTransform()->AddLocalPosition(float4::Forward * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("TestMoveBack"))
	{
		GetTransform()->AddLocalPosition(float4::Back * Speed * _DeltaTime);
	}

	if (true == GameEngineInput::IsPress("TestRotY+"))
	{
		GetTransform()->AddLocalRotation({ 0.0f, RotSpeed * _DeltaTime, 0.0f });
	}
	if (true == GameEngineInput::IsPress("TestRotY-"))
	{
		GetTransform()->AddLocalRotation({ 0.0f, -RotSpeed * _DeltaTime, 0.0f });
	}
	if (true == GameEngineInput::IsPress("TestRotZ+"))
	{
		GetTransform()->AddLocalRotation({ 0.0f, 0.0f, RotSpeed * _DeltaTime });
	}
	if (true == GameEngineInput::IsPress("TestRotZ-"))
	{
		GetTransform()->AddLocalRotation({ 0.0f, 0.0f, -RotSpeed * _DeltaTime });
	}
	if (true == GameEngineInput::IsPress("TestRotX+"))
	{
		GetTransform()->AddLocalRotation({ RotSpeed * _DeltaTime, 0.0f, 0.0f });
	}
	if (true == GameEngineInput::IsPress("TestRotX-"))
	{
		GetTransform()->AddLocalRotation({ -RotSpeed * _DeltaTime, 0.0f, 0.0f });
	}

	float ScaleSpeed = 10.0f;

	if (true == GameEngineInput::IsPress("TestScaleY+"))
	{
		GetTransform()->AddLocalScale({ 0.0f, ScaleSpeed * _DeltaTime, 0.0f });
	}
	if (true == GameEngineInput::IsPress("TestScaleY-"))
	{
		GetTransform()->AddLocalScale({ 0.0f, -ScaleSpeed * _DeltaTime, 0.0f });
	}
	if (true == GameEngineInput::IsPress("TestScaleZ+"))
	{
		GetTransform()->AddLocalScale({ 0.0f, 0.0f, ScaleSpeed * _DeltaTime });
	}
	if (true == GameEngineInput::IsPress("TestScaleZ-"))
	{
		GetTransform()->AddLocalScale({ 0.0f, 0.0f, -ScaleSpeed * _DeltaTime });
	}
	if (true == GameEngineInput::IsPress("TestScaleX+"))
	{
		GetTransform()->AddLocalScale({ ScaleSpeed * _DeltaTime, 0.0f, 0.0f });
	}
	if (true == GameEngineInput::IsPress("TestScaleX-"))
	{
		GetTransform()->AddLocalScale({ -ScaleSpeed * _DeltaTime, 0.0f, 0.0f });
	}

	// Render1->GetTransform()->SetWorldPosition({ 0.0f, 0.0f, 0.0f });



	Render1->GetTransform()->SetLocalRotation(-GetTransform()->GetWorldRotation());
}

void Test::Start()
{
	if (false == GameEngineInput::IsKey("TestMoveLeft"))
	{
		GameEngineInput::CreateKey("TestMoveLeft", 'A');
		GameEngineInput::CreateKey("TestMoveRight", 'D');
		GameEngineInput::CreateKey("TestMoveUp", 'Q');
		GameEngineInput::CreateKey("TestMoveDown", 'E');
		GameEngineInput::CreateKey("TestMoveForward", 'W');
		GameEngineInput::CreateKey("TestMoveBack", 'S');

		GameEngineInput::CreateKey("TestScaleY+", 'Y');
		GameEngineInput::CreateKey("TestScaleY-", 'U');
		GameEngineInput::CreateKey("TestScaleZ+", 'H');
		GameEngineInput::CreateKey("TestScaleZ-", 'J');
		GameEngineInput::CreateKey("TestScaleX+", 'N');
		GameEngineInput::CreateKey("TestScaleX-", 'M');


		GameEngineInput::CreateKey("TestRotY+", VK_NUMPAD1);
		GameEngineInput::CreateKey("TestRotY-", VK_NUMPAD2);
		GameEngineInput::CreateKey("TestRotZ+", VK_NUMPAD4);
		GameEngineInput::CreateKey("TestRotZ-", VK_NUMPAD5);
		GameEngineInput::CreateKey("TestRotX+", VK_NUMPAD7);
		GameEngineInput::CreateKey("TestRotX-", VK_NUMPAD8);
		GameEngineInput::CreateKey("TestSpeedBoost", VK_LSHIFT);
	}


	// 나는 스케일을 1로 고정해 놓는게 좋다.
	Render0 = CreateComponent<GameEngineRenderer>();
	Render0->SetPipeLine("2DTexture");
	Render1 = CreateComponent<GameEngineRenderer>();
	Render1->SetPipeLine("2DTexture");
	Render2 = CreateComponent<GameEngineRenderer>();
	Render2->SetPipeLine("2DTexture");

	Render1->GetTransform()->DebugOn();

	Render0->GetTransform()->SetLocalPosition({ -200.0f, 0.0f, 0.0f });
	Render2->GetTransform()->SetLocalPosition({ 200.0f, 0.0f, 0.0f });
}

// 이건 디버깅용도나 
void Test::Render(float _Delta)
{
	// GetTransform()->AddLocalRotation({0.0f, 0.0f, 360.0f * _Delta});
};
