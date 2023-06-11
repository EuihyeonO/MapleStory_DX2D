#include "PrecompileHeader.h"
#include "ZakumRArm_0.h"
#include "Zakum.h"
#include "Player.h"

#include <GameEnginePlatform/GameEngineInput.h>

ZakumRArm_0::ZakumRArm_0()
{
	ArmIndex = 0;
	isLeft = false;
}

ZakumRArm_0::~ZakumRArm_0()
{
}

void ZakumRArm_0::Start()
{
	ArmRender = CreateComponent<GameEngineSpriteRenderer>();

	SetAnimation();

	ArmCollision = CreateComponent<GameEngineCollision>();
	ArmCollision->GetTransform()->SetLocalScale({ 150, 100 });
	ArmCollision->SetColType(ColType::AABBBOX2D);
	ArmCollision->SetOrder(static_cast<int>(CollisionOrder::Monster));
	ArmCollision->GetTransform()->SetLocalPosition({ 10, 10 });
	ArmCollision->On();

	ArmRender->ChangeAnimation("Stand");

}

void ZakumRArm_0::Update(float _DeltaTime) 
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

void ZakumRArm_0::Render(float _DeltaTime) 
{

}

void ZakumRArm_0::SetAnimation()
{
	//1Attack
	ArmRender->CreateAnimation({ .AnimationName = "1Attack",.SpriteName = "RArm0_1Attack",.Loop = false,.ScaleToTexture = true,.FrameTime = {0.12f, 0.12f, 0.12f, 0.115f, 0.125f, 0.115f, 0.125f, 0.115f, 0.12f, 0.12f, 0.12f, 0.12f, 0.12f } });
	ArmRender->SetAnimationUpdateEvent("1Attack", 0, [this] {GetTransform()->SetLocalPosition({ 145, 135, -4.0f }); isAttack = true;  });
	ArmRender->SetAnimationStartEvent("1Attack", 9, [this]
		{
			std::shared_ptr<GameEngineSpriteRenderer> Eff = CreateComponent<GameEngineSpriteRenderer>();
			Player::GetCurPlayer()->Hit();
			Eff->GetTransform()->SetWorldPosition(Player::GetCurPlayer()->GetTransform()->GetWorldPosition() + float4{ 3.0f, 40.0f, -10.0f });
			Eff->CreateAnimation({ .AnimationName = "1AtEffect",.SpriteName = "RArm0_1AtEffect",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
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
				isAttack = false;
				ArmRender->ChangeAnimation("Stand");
			}
		});
	//
	ArmRender->CreateAnimation({ .AnimationName = "Stand",.SpriteName = "RArm0_Stand",.Loop = true,.ScaleToTexture = true,.FrameTime = {0.13f, 0.1f,0.1f, 0.1f, 0.13f, 0.1f, 0.1f, 0.1f } });
	ArmRender->SetAnimationUpdateEvent("Stand", 0, [this]
		{
			GetTransform()->SetLocalPosition({ 130, 110, -4.0f });
		});

	ArmRender->CreateAnimation({ .AnimationName = "Hit",.SpriteName = "RArm0_Hit",.FrameInter = 0.5f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Hit", 0, [this]
		{
			GetTransform()->SetLocalPosition({ 140, 125, -4.0f });
			if (ArmRender->IsAnimationEnd() == true)
			{
				ArmRender->ChangeAnimation("Stand");
			}
		});

	ArmRender->CreateAnimation({ .AnimationName = "Death",.SpriteName = "RArm0_Death",.FrameInter = 0.11f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Death", 18, [this] {Zakum::GetZakum()->ArmDeath(isLeft, ArmIndex); });
	ArmRender->SetAnimationUpdateEvent("Death", 0, [this]
		{
			GetTransform()->SetLocalPosition({ 160, 145, -4.0f });
			ArmCollision->Off();
		});
}