#include "PrecompileHeader.h"
#include "KeyBox.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>

KeyBox::KeyBox()
{
}

KeyBox::~KeyBox()
{
}

void KeyBox::Start()
{
	BoxRender = CreateComponent<GameEngineSpriteRenderer>();
	BoxRender->CreateAnimation({ .AnimationName = "Stand0" ,.SpriteName = "KeyBox0Stand" ,.FrameInter = 0.1f ,.Loop = false,.ScaleToTexture = true });
	BoxRender->CreateAnimation({ .AnimationName = "Hit0" ,.SpriteName = "KeyBox0Hit" ,.FrameInter = 0.1f ,.Loop = false,.ScaleToTexture = true });

	BoxRender->CreateAnimation({ .AnimationName = "Stand1" ,.SpriteName = "KeyBox1Stand" ,.FrameInter = 0.1f ,.Loop = false,.ScaleToTexture = true });
	BoxRender->CreateAnimation({ .AnimationName = "Hit1" ,.SpriteName = "KeyBox1Hit" ,.FrameInter = 0.1f ,.Loop = false,.ScaleToTexture = true });
	
	BoxRender->CreateAnimation({ .AnimationName = "Stand2" ,.SpriteName = "KeyBox2Stand" ,.FrameInter = 0.1f ,.Loop = false,.ScaleToTexture = true });
	BoxRender->CreateAnimation({ .AnimationName = "Hit2" ,.SpriteName = "KeyBox2Hit" ,.FrameInter = 0.1f ,.Loop = false,.ScaleToTexture = true });
	
	BoxRender->CreateAnimation({ .AnimationName = "Stand3" ,.SpriteName = "KeyBox3Stand" ,.FrameInter = 0.1f ,.Loop = false,.ScaleToTexture = true });
	BoxRender->CreateAnimation({ .AnimationName = "Hit3" ,.SpriteName = "KeyBox3Hit" ,.FrameInter = 0.1f ,.Loop = false,.ScaleToTexture = true });
	
	//test
	BoxRender->ChangeAnimation("Stand0");
	GetTransform()->AddLocalPosition({ 0, -300.0f });
}

void KeyBox::Update(float _DeltaTime)
{
	if (GameEngineInput::IsKey("MyTest") == false)
	{
		GameEngineInput::CreateKey("MyTest", 'B');
	}

	if (GameEngineInput::IsDown("MyTest") == true)
	{
		BoxRender->ChangeAnimation("Hit0");
	}
}

void KeyBox::Render(float _DeltaTime)
{

}