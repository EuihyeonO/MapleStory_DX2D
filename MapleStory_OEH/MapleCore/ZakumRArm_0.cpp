#include "PrecompileHeader.h"
#include "ZakumRArm_0.h"
#include "Zakum.h"
#include "Player.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>

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
	DeltaTime = _DeltaTime;
}

void ZakumRArm_0::Render(float _DeltaTime) 
{

}

void ZakumRArm_0::Attack()
{
	if (isAtCoolTime == true)
	{
		return;
	}

	int Num = GameEngineRandom::MainRandom.RandomInt(0, 1);

	switch (Num)
	{
	case 0:
		ArmRender->ChangeAnimation("1Attack");
		break;
	case 1:
		ArmRender->ChangeAnimation("2Attack");
		break;

	}
}

void ZakumRArm_0::SetAnimation()
{
	//1Attack
	ArmRender->CreateAnimation({ .AnimationName = "1Attack",.SpriteName = "RArm0_1Attack",.Loop = false,.ScaleToTexture = true,.FrameTime = {0.12f, 0.12f, 0.12f, 0.115f, 0.125f, 0.115f, 0.125f, 0.115f, 0.12f, 0.12f, 0.12f, 0.12f, 0.12f } });
	ArmRender->SetAnimationUpdateEvent("1Attack", 0, [this] {GetTransform()->SetLocalPosition({ 145, 135, -4.0f }); ArmCollision->GetTransform()->SetLocalPosition({ -5, -15 }); isAttack = true; isAtCoolTime = true; });
	ArmRender->SetAnimationStartEvent("1Attack", 9, [this]
		{
			std::weak_ptr<GameEngineSpriteRenderer> Effect = CreateComponent<GameEngineSpriteRenderer>();
			Player::GetCurPlayer()->Hit(10);
			Effect.lock()->GetTransform()->SetWorldPosition(Player::GetCurPlayer()->GetTransform()->GetWorldPosition() + float4{ 3.0f, 40.0f, -10.0f });
			Effect.lock()->CreateAnimation({ .AnimationName = "1AtEffect",.SpriteName = "RArm0_1AtEffect",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
			Effect.lock()->ChangeAnimation("1AtEffect");
			Effect.lock()->SetAnimationUpdateEvent("1AtEffect", 6, [Effect]
				{
					if (Effect.lock()->IsAnimationEnd() == true)
					{
						Effect.lock()->Death();
					}
				});
		});

	ArmRender->SetAnimationUpdateEvent("1Attack", 12, [this]
		{
			if (ArmRender->IsAnimationEnd() == true)
			{
				isAttack = false;
				GetLevel()->TimeEvent.AddEvent(3.0f, [this](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager) {isAtCoolTime = false; }, false);
				GetTransform()->SetLocalPosition({ 130, 110, -4.0f });
				ArmCollision->GetTransform()->SetLocalPosition({ 10, 10 });
				ArmRender->ChangeAnimation("Stand");
			}
		});
	
	//2Attack
	ArmRender->CreateAnimation({ .AnimationName = "2Attack",.SpriteName = "RArm0_2Attack",.Loop = false,.ScaleToTexture = true,.FrameTime = {0.115f, 0.125f, 0.115f, 0.125f, 0.115f, 0.12f, 0.12f, 0.12f, 0.12f, 0.125f, 0.11f, 0.12f, 0.125f} });
	ArmRender->SetAnimationUpdateEvent("2Attack", 0, [this] {GetTransform()->SetLocalPosition({ 145, 135, -4.0f }); ArmCollision->GetTransform()->SetLocalPosition({ -5, -15 }); isAttack = true; isAtCoolTime = true; });
	ArmRender->SetAnimationStartEvent("2Attack", 9, [this]
		{
			std::weak_ptr<GameEngineSpriteRenderer> Effect = CreateComponent<GameEngineSpriteRenderer>();
			Player::GetCurPlayer()->Hit(10);
			Effect.lock()->GetTransform()->SetWorldPosition(Player::GetCurPlayer()->GetTransform()->GetWorldPosition() + float4{3.0f, 40.0f, -10.0f});
			Effect.lock()->CreateAnimation({ .AnimationName = "2AtEffect",.SpriteName = "RArm0_2AtEffect",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
			Effect.lock()->ChangeAnimation("2AtEffect");
			Effect.lock()->SetAnimationUpdateEvent("2AtEffect", 6, [Effect]
				{
					if (Effect.lock()->IsAnimationEnd() == true)
					{
						Effect.lock()->Death();
					}
				});
		});

	ArmRender->SetAnimationUpdateEvent("2Attack", 12, [this]
		{
			if (ArmRender->IsAnimationEnd() == true)
			{
				isAttack = false;
				GetLevel()->TimeEvent.AddEvent(3.0f, [this](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager) {isAtCoolTime = false; }, false);
				GetTransform()->SetLocalPosition({ 130, 110, -4.0f });
				ArmCollision->GetTransform()->SetLocalPosition({ 10, 10 });
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
				GetTransform()->SetLocalPosition({ 130, 110, -4.0f });
				ArmRender->ChangeAnimation("Stand");
			}
		});

	//Death
	std::vector<float> FrameVec;
	FrameVec.reserve(19);

	for (int i = 0; i < 19; i++)
	{
		FrameVec.push_back(0.11f);
	}

	FrameVec[18] = 1.0f;

	ArmRender->CreateAnimation({ .AnimationName = "Death",.SpriteName = "RArm0_Death",.Loop = false,.ScaleToTexture = true,.FrameTime = FrameVec });
	ArmRender->SetAnimationUpdateEvent("Death", 18, [this]
		{
			ArmRender->ColorOptionValue.MulColor.a -= 4.0f * DeltaTime;

			if (ArmRender->ColorOptionValue.MulColor.a <= 0.0f)
			{
				Zakum::GetZakum()->ArmDeath(isLeft, ArmIndex);
			}
		});

	ArmRender->SetAnimationUpdateEvent("Death", 0, [this]
		{
			GetTransform()->SetLocalPosition({ 160, 145, -4.0f });
			ArmCollision->Off();
		});
}