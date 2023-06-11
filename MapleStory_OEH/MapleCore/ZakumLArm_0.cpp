#include "PrecompileHeader.h"
#include "ZakumLArm_0.h"
#include "Zakum.h"
#include "Player.h"

#include <GameEnginePlatform/GameEngineInput.h>

ZakumLArm_0::ZakumLArm_0()
{
	ArmIndex = 0;
	isLeft = true;
}

ZakumLArm_0::~ZakumLArm_0()
{

}



void ZakumLArm_0::Start()
{
	ArmRender = CreateComponent<GameEngineSpriteRenderer>();

	SetAnimation();

	ArmCollision = CreateComponent<GameEngineCollision>();
	ArmCollision->GetTransform()->SetLocalScale({ 150, 100 });
	ArmCollision->SetColType(ColType::AABBBOX2D);
	ArmCollision->SetOrder(static_cast<int>(CollisionOrder::Monster));
	ArmCollision->GetTransform()->SetLocalPosition({ -30, -30 });

	ArmRender->ChangeAnimation("Stand");
}

void ZakumLArm_0::Update(float _DeltaTime)
{
	if (GameEngineInput::IsKey("MyTest") == false)
	{
		GameEngineInput::CreateKey("MyTest", 'B');
	}

	if (GameEngineInput::IsDown("MyTest") == true)
	{
		ArmRender->ChangeAnimation("1Attack");
	}
}

void ZakumLArm_0::Render(float _DeltaTime)
{

}

void ZakumLArm_0::SetAnimation()
{
	ArmRender->CreateAnimation({ .AnimationName = "Stand",.SpriteName = "LArm0_Stand",.Loop = true,.ScaleToTexture = true,.FrameTime = {0.13f, 0.1f,0.1f, 0.1f, 0.13f, 0.1f, 0.1f, 0.1f } });
	ArmRender->SetAnimationUpdateEvent("Stand", 0, [this] {GetTransform()->SetLocalPosition({ -110, 110, -4.0f }); });

	ArmRender->CreateAnimation({ .AnimationName = "1Attack",.SpriteName = "LArm0_1Attack",.Loop = false,.ScaleToTexture = true,.FrameTime = {0.12f, 0.12f, 0.12f, 0.115f, 0.125f, 0.115f, 0.125f, 0.115f, 0.12f, 0.12f, 0.12f, 0.12f, 0.12f } });
	ArmRender->SetAnimationUpdateEvent("1Attack", 0, [this] {GetTransform()->SetLocalPosition({ -120, 135, -4.0f }); });
	ArmRender->SetAnimationStartEvent("1Attack", 9, [this]
		{
			std::shared_ptr<GameEngineSpriteRenderer> Eff = CreateComponent<GameEngineSpriteRenderer>();
			Player::GetCurPlayer()->Hit();
			Eff->GetTransform()->SetWorldPosition(Player::GetCurPlayer()->GetTransform()->GetWorldPosition() + float4{3.0f, 40.0f, -10.0f});
			Eff->CreateAnimation({ .AnimationName = "1AtEffect",.SpriteName = "LArm0_1AtEffect",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
			Eff->ChangeAnimation("1AtEffect");
			Eff->SetAnimationUpdateEvent("1AtEffect", 6, [Eff]
				{
					if (Eff->IsAnimationEnd() == true)
					{
						Eff->Death();
					}
				}); 
		});
	ArmRender->SetAnimationUpdateEvent("1Attack", 12, [this]
		{
			if (ArmRender->IsAnimationEnd() == true)
			{
				ArmRender->ChangeAnimation("Stand");
			}
		});

	ArmRender->CreateAnimation({ .AnimationName = "Hit",.SpriteName = "LArm0_Hit",.FrameInter = 0.5f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Hit", 0, [this]
		{
			GetTransform()->SetLocalPosition({ -120, 130, -4.0f });
			if (ArmRender->IsAnimationEnd() == true)
			{
				ArmRender->ChangeAnimation("Stand");
			}
		});

	ArmRender->CreateAnimation({ .AnimationName = "Death",.SpriteName = "LArm0_Death",.FrameInter = 0.11f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Death", 18, [this] {Zakum::GetZakum()->ArmDeath(isLeft, ArmIndex); });
	ArmRender->SetAnimationUpdateEvent("Death", 0, [this]
		{
			GetTransform()->SetLocalPosition({ -135, 140, -4.0f });
			ArmCollision->Off();
		});
}