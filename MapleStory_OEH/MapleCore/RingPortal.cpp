#include "PrecompileHeader.h"
#include "RingPortal.h"
#include "Player.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>

bool RingPortal::isUsed = false;

RingPortal::RingPortal()
{
}

RingPortal::~RingPortal()
{
}

void RingPortal::Start()
{
	PortalRender = CreateComponent<GameEngineSpriteRenderer>();

	PortalRender->CreateAnimation({ .AnimationName = "RingPortal",.SpriteName = "RingPortal",.Start = 0,.End = 6 ,.FrameInter = 0.1f,.Loop = true ,.ScaleToTexture = true });
	PortalRender->ChangeAnimation("RingPortal");

	PortalRender->ColorOptionValue.MulColor.a = 0.0f;

	PortalCollision = CreateComponent<GameEngineCollision>();
	PortalCollision->SetColType(ColType::AABBBOX2D);
	PortalCollision->GetTransform()->SetLocalScale({ 80, 120 });
}

void RingPortal::Update(float _DeltaTime)
{
	CollisionCheck();
	AlphaUpdate(_DeltaTime);
	SetPlayerPosToLinkedPos();
}

void RingPortal::Render(float _DeltaTime)
{

}

void RingPortal::CollisionCheck()
{
	std::shared_ptr<GameEngineCollision> Col = PortalCollision->Collision(static_cast<int>(CollisionOrder::Player), ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (Col != nullptr)
	{
		isColToPlayer = true;
	}
	else
	{
		isColToPlayer = false;
	}
}

void RingPortal::AlphaUpdate(float _DeltaTime)
{
	if (isColToPlayer == true)
	{
		PortalRender->ColorOptionValue.MulColor.a += 2.0f * _DeltaTime;

		if (PortalRender->ColorOptionValue.MulColor.a >= 1.0f)
		{
			PortalRender->ColorOptionValue.MulColor.a = 1.0f;
		}
	}
	else
	{
		PortalRender->ColorOptionValue.MulColor.a -= 2.0f * _DeltaTime;

		if (PortalRender->ColorOptionValue.MulColor.a <= 0.0f)
		{
			PortalRender->ColorOptionValue.MulColor.a = 0.0f;
		}
	}
}

void RingPortal::SetPlayerPosToLinkedPos()
{
	if (isColToPlayer == false || isUsed == true)
	{
		return;
	}

	if (GameEngineInput::IsDown("UpKey") == true)
	{
		Player::GetCurPlayer()->GetTransform()->SetWorldPosition(LinkedPos);
		isUsed = true;
		
		GetLevel()->TimeEvent.AddEvent(0.3f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)
			{
				isUsed = false;
			});
	}
}