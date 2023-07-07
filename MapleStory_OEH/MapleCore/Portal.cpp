#include "PrecompileHeader.h"
#include "Portal.h"
#include "ContentEnums.h"
#include "Player.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>

Portal::Portal()
{
}

Portal::~Portal()
{
}

void Portal::Start()
{
	PortalRender = CreateComponent<GameEngineSpriteRenderer>();

	PortalRender->CreateAnimation({.AnimationName = "Portal",.SpriteName = "Portal",.Start = 0,.End = 7 ,.FrameInter = 0.1f,.Loop = true ,.ScaleToTexture = true });
	PortalRender->ChangeAnimation("Portal");

	PortalCollision = CreateComponent<GameEngineCollision>();

	PortalCollision->GetTransform()->SetLocalPosition({ 0, -80 });
	PortalCollision->GetTransform()->SetLocalScale({ 70, 80 });

	BlackOut = CreateComponent<GameEngineUIRenderer>();
	BlackOut->GetTransform()->SetWorldScale({ 800, 600 });
	BlackOut->GetTransform()->SetWorldPosition({ 0, 0 });
	BlackOut->ColorOptionValue.MulColor = { 0.0f, 0.0f, 0.0f, 0.0f };
}

void Portal::Update(float _DeltaTime)
{
	std::shared_ptr<GameEngineCollision> Collision = PortalCollision->Collision(static_cast<int>(CollisionOrder::Player), ColType::AABBBOX2D, ColType::AABBBOX2D);
	
	if (Collision != nullptr)
	{
		if (GameEngineInput::IsDown("UpKey") == true)
		{
			GameEngineSound::Play("Portal.mp3");
			Player::GetCurPlayer()->SetMovable(false);
			FadeOutUpdate = &Portal::FadeOut;
		}
	}

	if (FadeOutUpdate != nullptr)
	{
		FadeOutUpdate(*this, _DeltaTime);
	}
}

void Portal::Render(float _DeltaTime)
{
}

void Portal::FadeOut(float _DeltaTime)
{
	if (BlackOut == nullptr)
	{
		return;
	}

	BlackOut->ColorOptionValue.MulColor.a += 1.0f * _DeltaTime;

	if (BlackOut->ColorOptionValue.MulColor.a >= 1.0f)
	{
		BlackOut->Death();
		BlackOut = nullptr;

		FadeOutUpdate = nullptr;
		GameEngineCore::ChangeLevel(LinkedMap);
	}
}
