#include "PrecompileHeader.h"
#include "KeyBox.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>

KeyBox::KeyBox()
{
}

KeyBox::~KeyBox()
{
}

void KeyBox::Start()
{

	ColMap = GameEngineTexture::Find("ColZakumRoad1.png");

	BoxRender = CreateComponent<GameEngineSpriteRenderer>();
	
	BoxRender->CreateAnimation({ .AnimationName = "Stand0" ,.SpriteName = "KeyBox0Stand" ,.FrameInter = 0.1f ,.Loop = false,.ScaleToTexture = true });
	BoxRender->CreateAnimation({ .AnimationName = "Hit0" ,.SpriteName = "KeyBox0Hit" ,.FrameInter = 0.15f ,.Loop = false,.ScaleToTexture = true });
	BoxRender->SetAnimationUpdateEvent("Hit0", 2, [this] {if (BoxRender->IsAnimationEnd() == true) { BoxRender->ChangeAnimation("Stand1"); isHit = false; }});

	BoxRender->CreateAnimation({ .AnimationName = "Stand1" ,.SpriteName = "KeyBox1Stand" ,.FrameInter = 0.1f ,.Loop = false,.ScaleToTexture = true });
	BoxRender->CreateAnimation({ .AnimationName = "Hit1" ,.SpriteName = "KeyBox1Hit" ,.FrameInter = 0.15f ,.Loop = false,.ScaleToTexture = true });
	BoxRender->SetAnimationUpdateEvent("Hit1", 2, [this] {if (BoxRender->IsAnimationEnd() == true) { BoxRender->ChangeAnimation("Stand2"); isHit = false;}});

	BoxRender->CreateAnimation({ .AnimationName = "Stand2" ,.SpriteName = "KeyBox2Stand" ,.FrameInter = 0.1f ,.Loop = false,.ScaleToTexture = true });
	BoxRender->CreateAnimation({ .AnimationName = "Hit2" ,.SpriteName = "KeyBox2Hit" ,.FrameInter = 0.15f ,.Loop = false,.ScaleToTexture = true });
	BoxRender->SetAnimationUpdateEvent("Hit2", 2, [this] {if (BoxRender->IsAnimationEnd() == true) { BoxRender->ChangeAnimation("Stand3"); isHit = false;}});

	BoxRender->CreateAnimation({ .AnimationName = "Stand3" ,.SpriteName = "KeyBox3Stand" ,.FrameInter = 0.1f ,.Loop = false,.ScaleToTexture = true });
	BoxRender->CreateAnimation({ .AnimationName = "Hit3" ,.SpriteName = "KeyBox3Hit" ,.FrameInter = 0.15f ,.Loop = false,.ScaleToTexture = true });
	BoxRender->SetAnimationUpdateEvent("Hit3", 2, [this] {
		if 
		(BoxRender->IsAnimationEnd() == true) 
		{
			Death(); 
		}});

	BoxRender->GetTransform()->SetLocalPosition({ 0, 47 });

	//test
	BoxRender->ChangeAnimation("Stand0");
	BoxRender->ColorOptionValue.MulColor.a = 0.0f;

	BoxCollision = CreateComponent<GameEngineCollision>();
	BoxCollision->GetTransform()->SetLocalScale({ 90, 60 });
	BoxCollision->GetTransform()->SetLocalPosition({ 10, 28 });
	
	BoxCollision->SetColType(ColType::AABBBOX2D);
	BoxCollision->SetOrder(static_cast<int>(CollisionOrder::Object));

	UpdateFunc = &KeyBox::Spawn;

}

void KeyBox::Update(float _DeltaTime)
{
	if (GameEngineInput::IsKey("MyTest") == false)
	{
		GameEngineInput::CreateKey("MyTest", 'B');
	}

	if (UpdateFunc != nullptr)
	{
		bool isEnd = UpdateFunc(*this, _DeltaTime);

		if (isEnd == true)
		{
			UpdateFunc = nullptr;
		}
	}
}

void KeyBox::Render(float _DeltaTime)
{

}

void KeyBox::GravityUpdate(float _DeltaTime)
{
	float Gravity = 2000.0f;

	float4 PlayerPos = GetTransform()->GetLocalPosition();

	float4 MapHalfScale = { static_cast<float>(ColMap->GetWidth() / 2) ,  static_cast<float>(ColMap->GetHeight() / 2) };
	float4 ColorPos = float4{ MapHalfScale.x, MapHalfScale.y } + float4{ PlayerPos.x, -PlayerPos.y };

	GameEnginePixelColor Color = { (char)255, 0, (char)255, (char)255 };

	int X = static_cast<int>(ColorPos.x);
	int Y = static_cast<int>(ColorPos.y);

	GameEnginePixelColor MapColor = ColMap->GetPixel(static_cast<int>(ColorPos.x), static_cast<int>(ColorPos.y));

	if (Color != MapColor)
	{
		GetTransform()->AddLocalPosition({ 0 , -Gravity * _DeltaTime, 0 });

		isGround = false;
	}
	else
	{
		float Count = 0.0f;

		while (Color == MapColor)
		{
			ColorPos.y--;
			MapColor = ColMap->GetPixel(static_cast<int>(ColorPos.x), static_cast<int>(ColorPos.y));
			Count++;
		}

		GetTransform()->AddLocalPosition({ 0, Count - 1 });

		Gravity = 2000.0f;

		isGround = true;
	}
}

bool KeyBox::Spawn(float _DeltaTime)
{
	if (isGround == false)
	{
		GravityUpdate(_DeltaTime);
	}
	else
	{
		if (isGround == true)
		{
			BoxRender->ColorOptionValue.MulColor.a += 1.0f * _DeltaTime;

			if (BoxRender->ColorOptionValue.MulColor.a >= 1.0f)
			{
				BoxRender->ColorOptionValue.MulColor.a = 1.0f;
				isSet = true;

				return true;
			}
		}
	}

	return false;
}

void KeyBox::SpawnStart(float4 _Pos)
{
	GetTransform()->SetLocalPosition(_Pos);
	UpdateFunc = &KeyBox::Spawn;
}

void KeyBox::Hit()
{
	if (isHit == true)
	{
		return;
	}
	
	GetLevel()->TimeEvent.AddEvent(0.45f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) 
		{
			BoxRender->ChangeAnimation("Hit" + std::to_string(count));
			count++;
			isHit = true;
		});


	
}