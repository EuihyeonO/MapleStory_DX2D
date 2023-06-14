#include "PrecompileHeader.h"
#include "ZakumLArm_1.h"
#include "Zakum.h"
#include "Player.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>

ZakumLArm_1::ZakumLArm_1()
{
	ArmIndex = 1;
	isLeft = true;
}

ZakumLArm_1::~ZakumLArm_1()
{
}

void ZakumLArm_1::Start()
{
	ArmRender = CreateComponent<GameEngineSpriteRenderer>();
	
	SetAnimation();

	ArmCollision = CreateComponent<GameEngineCollision>();
	ArmCollision->GetTransform()->SetLocalScale({ 150, 60 });
	ArmCollision->SetColType(ColType::AABBBOX2D);
	ArmCollision->SetOrder(static_cast<int>(CollisionOrder::Monster));
	ArmCollision->GetTransform()->SetLocalPosition({ -30, -50 });
	ArmCollision->On();

	ArmRender->ChangeAnimation("Stand");
}

void ZakumLArm_1::Update(float _DeltaTime)
{
	DeltaTime = _DeltaTime;
}

void ZakumLArm_1::Render(float _DeltaTime)
{

}
void ZakumLArm_1::Attack()
{
	if (isAtCoolTime == true)
	{
		return;
	}

	int Num = GameEngineRandom::MainRandom.RandomInt(0, 0);

	switch (Num)
	{
	case 0:
		ArmRender->ChangeAnimation("1Attack");
		break;
	case 1:
		ArmRender->ChangeAnimation("Skill");
		break;
	}
}

void ZakumLArm_1::SetAnimation()
{
	//1Attack
	ArmRender->CreateAnimation({ .AnimationName = "1Attack",.SpriteName = "LArm1_1Attack",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("1Attack", 0, [this] {GetTransform()->SetLocalPosition({ -195, 40, -4.0f }); ArmCollision->GetTransform()->SetLocalPosition({ 45, -30 }); isAttack = true; isAtCoolTime = true;  });
	
	ArmRender->SetAnimationStartEvent("1Attack", 9, [this]	
		{
			FireRain();
		});

	ArmRender->SetAnimationUpdateEvent("1Attack", 14, [this]
		{
			if (ArmRender->IsAnimationEnd() == true)
			{
				isAttack = false;
				GetLevel()->TimeEvent.AddEvent(3.0f, [this](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager) {isAtCoolTime = false; }, false);
				GetTransform()->SetLocalPosition({ -120, 60, -4.0f });
				ArmCollision->GetTransform()->SetLocalPosition({ -30, -50 });
				ArmRender->ChangeAnimation("Stand");
			}
		});

	//Skill
	
	ArmRender->CreateAnimation({ .AnimationName = "Skill",.SpriteName = "LArm1_Skill",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Skill", 0, [this] {GetTransform()->SetLocalPosition({ -175, 40, -4.0f }); ArmCollision->GetTransform()->SetLocalPosition({ 25, -30 }); isAttack = true;  isAtCoolTime = true; });

	ArmRender->SetAnimationStartEvent("Skill", 9, [this]
		{
			//독가스 이펙트
		});

	ArmRender->SetAnimationUpdateEvent("Skill", 14, [this]
		{
			if (ArmRender->IsAnimationEnd() == true)
			{
				isAttack = false;
				GetLevel()->TimeEvent.AddEvent(3.0f, [this](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager) {isAtCoolTime = false; }, false);
				GetTransform()->SetLocalPosition({ -120, 60, -4.0f });
				ArmCollision->GetTransform()->SetLocalPosition({ -30, -50 });
				ArmRender->ChangeAnimation("Stand");
			}
		});

	//Stand
	ArmRender->CreateAnimation({ .AnimationName = "Stand",.SpriteName = "LArm1_Stand",.Loop = true,.ScaleToTexture = true,.FrameTime = {0.13f, 0.1f,0.1f, 0.1f, 0.13f, 0.1f, 0.1f, 0.1f } });
	ArmRender->SetAnimationUpdateEvent("Stand", 0, [this]
		{
			GetTransform()->SetLocalPosition({ -120, 60, -4.0f });
		});


	//Hit
	ArmRender->CreateAnimation({ .AnimationName = "Hit",.SpriteName = "LArm1_Hit",.FrameInter = 0.5f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Hit", 0, [this]
		{
			GetTransform()->SetLocalPosition({ -135, 50, -4.0f });
			if (ArmRender->IsAnimationEnd() == true)
			{
				GetTransform()->SetLocalPosition({ -120, 60, -4.0f });
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

	ArmRender->CreateAnimation({ .AnimationName = "Death",.SpriteName = "LArm1_Death",.Loop = false,.ScaleToTexture = true,.FrameTime = FrameVec });
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
			GetTransform()->SetLocalPosition({ -145, 60, -4.0f });
			ArmCollision->Off();
		});

}

void ZakumLArm_1::FireRain()
{
	for (int i = 0; i < 30; i++)
	{
		float Xpos = GameEngineRandom::MainRandom.RandomFloat(-500, 500);
		float Ypos = GameEngineRandom::MainRandom.RandomFloat(-50, 100);
		
		int Index = GameEngineRandom::MainRandom.RandomInt(0, 2);

		std::string EffName = "LArm1_1AtObj" + std::to_string(Index);

		std::weak_ptr<GameEngineSpriteRenderer> NewEff = CreateComponent<GameEngineSpriteRenderer>();
		NewEff.lock()->GetTransform()->SetWorldPosition({ Xpos , Ypos , -6.0f});
		NewEff.lock()->CreateAnimation({.AnimationName = "Fire",.SpriteName = EffName ,.FrameInter = 0.1f,.Loop = true,.ScaleToTexture = true});
		
		std::weak_ptr<GameEngineCollision> NewEffCol = CreateComponent<GameEngineCollision>();
		NewEffCol.lock()->SetColType(ColType::SPHERE2D);
		NewEffCol.lock()->GetTransform()->SetWorldScale({ 40, 40 });
		NewEffCol.lock()->SetOrder(static_cast<int>(CollisionOrder::Monster));
		
		float Speed = GameEngineRandom::MainRandom.RandomFloat(200, 300);
		for(int i = 0; i < 3; i++)
		{
			NewEff.lock()->SetAnimationUpdateEvent("Fire", i, [NewEff, NewEffCol, this, Speed]
				{
					NewEff.lock()->GetTransform()->AddWorldPosition({ -Speed * DeltaTime, -Speed * DeltaTime });
					NewEffCol.lock()->GetTransform()->SetWorldPosition(NewEff.lock()->GetTransform()->GetWorldPosition());

					if (NewEffCol.lock()->Collision(static_cast<int>(CollisionOrder::Player), ColType::SPHERE2D, ColType::AABBBOX2D) != nullptr)
					{
						if(Player::GetCurPlayer()->GetisHit() == false)
						{
							std::weak_ptr<GameEngineSpriteRenderer> NewHitEff = CreateComponent<GameEngineSpriteRenderer>();
							NewHitEff.lock()->GetTransform()->SetWorldPosition(Player::GetCurPlayer()->GetTransform()->GetWorldPosition() + float4{0, 25.0f, -1.0f});
							NewHitEff.lock()->CreateAnimation({ .AnimationName = "AtEffect",.SpriteName = "LArm1_1AtEffect",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
							NewHitEff.lock()->SetAnimationUpdateEvent("AtEffect", 3, [NewHitEff] {if (NewHitEff.lock()->IsAnimationEnd() == true) { NewHitEff.lock()->Death(); }});
							NewHitEff.lock()->ChangeAnimation("AtEffect");
						}
						Player::GetCurPlayer()->Hit(10);
					}
				});
		}


		NewEff.lock()->ChangeAnimation("Fire");
		float DeathTime = GameEngineRandom::MainRandom.RandomFloat(0.25f, 0.5f);
		GetLevel()->TimeEvent.AddEvent(DeathTime, [NewEff, NewEffCol](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {NewEff.lock()->Death(); NewEffCol.lock()->Death(); }, false);
	}
}