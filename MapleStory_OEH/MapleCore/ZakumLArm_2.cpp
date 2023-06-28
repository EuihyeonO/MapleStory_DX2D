#include "PrecompileHeader.h"
#include "ZakumLArm_2.h"
#include "Zakum.h"
#include "Player.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>

ZakumLArm_2::ZakumLArm_2()
{
	ArmIndex = 2;
	isLeft = true;
}

ZakumLArm_2::~ZakumLArm_2()
{
	Zakum::GetZakum()->LArm_2_UnLoad();
}


void ZakumLArm_2::Start()
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

void ZakumLArm_2::Update(float _DeltaTime)
{
	DeltaTime = _DeltaTime;
}

void ZakumLArm_2::Render(float _DeltaTime)
{
}

void ZakumLArm_2::Attack()
{
	if (isAtCoolTime == true)
	{
		return;
	}

	if (isStartDeath == true)
	{
		return;
	}


	int Num = GameEngineRandom::MainRandom.RandomInt(0,3);

	switch (Num)
	{
	case 0:
		ArmRender->ChangeAnimation("1Skill");
		break;
	case 1:
		ArmRender->ChangeAnimation("2Skill");
		break;
	case 2:
		ArmRender->ChangeAnimation("3Skill");
		break;
	case 3:
		ArmRender->ChangeAnimation("4Skill");
		break;
	}
}

void ZakumLArm_2::SetAnimation()
{
	//Skill1

	ArmRender->CreateAnimation({ .AnimationName = "1Skill",.SpriteName = "LArm2_1Skill",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("1Skill", 0, [this] {GetTransform()->SetLocalPosition({ -160, -30, -4.0f }); ArmCollision->GetTransform()->SetLocalPosition({ 10, -30 });  isAttack = true; isAtCoolTime = true; });

	ArmRender->SetAnimationStartEvent("1Skill", 9, [this]
		{
			SkillLock();
		});

	ArmRender->SetAnimationUpdateEvent("1Skill", 14, [this]
		{
			if (ArmRender->IsAnimationEnd() == true)
			{
				isAttack = false;
				GetLevel()->TimeEvent.AddEvent(3.0f, [this](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager) {isAtCoolTime = false; }, false);
				GetTransform()->SetLocalPosition({ -120, -10, -4.0f });
				ArmCollision->GetTransform()->SetLocalPosition({ -30, -50 });
				ArmRender->ChangeAnimation("Stand");
			}
		});

	//Skill2
	ArmRender->CreateAnimation({ .AnimationName = "2Skill",.SpriteName = "LArm2_2Skill",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("2Skill", 0, [this] {GetTransform()->SetLocalPosition({ -160, -30, -4.0f }); ArmCollision->GetTransform()->SetLocalPosition({ 10, -30 });  isAttack = true; isAtCoolTime = true; });

	ArmRender->SetAnimationStartEvent("2Skill", 9, [this]
		{
			MoreMiss();
		});

	ArmRender->SetAnimationUpdateEvent("2Skill", 14, [this]
		{
			if (ArmRender->IsAnimationEnd() == true)
			{
				isAttack = false;
				GetLevel()->TimeEvent.AddEvent(3.0f, [this](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager) {isAtCoolTime = false; }, false);
				GetTransform()->SetLocalPosition({ -120, -10, -4.0f });
				ArmCollision->GetTransform()->SetLocalPosition({ -30, -50 });
				ArmRender->ChangeAnimation("Stand");
			}
		});

	//Skill3
	ArmRender->CreateAnimation({ .AnimationName = "3Skill",.SpriteName = "LArm2_3Skill",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("3Skill", 0, [this] {GetTransform()->SetLocalPosition({ -160, -30, -4.0f }); ArmCollision->GetTransform()->SetLocalPosition({ 10, -30 }); isAttack = true; isAtCoolTime = true; });

	ArmRender->SetAnimationStartEvent("3Skill", 9, [this]
		{
			DamagedDouble();
		});

	ArmRender->SetAnimationUpdateEvent("3Skill", 14, [this]
		{
			if (ArmRender->IsAnimationEnd() == true)
			{
				isAttack = false;
				GetLevel()->TimeEvent.AddEvent(3.0f, [this](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager) {isAtCoolTime = false; }, false);
				GetTransform()->SetLocalPosition({ -120, -10, -4.0f });
				ArmCollision->GetTransform()->SetLocalPosition({ -30, -50 });
				ArmRender->ChangeAnimation("Stand");
			}
		});

	//Skill4
	ArmRender->CreateAnimation({ .AnimationName = "4Skill",.SpriteName = "LArm2_4Skill",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("4Skill", 0, [this] {GetTransform()->SetLocalPosition({ -160, -30, -4.0f });  ArmCollision->GetTransform()->SetLocalPosition({ 10, -30 }); isAttack = true; isAtCoolTime = true; });

	ArmRender->SetAnimationStartEvent("4Skill", 9, [this]
		{
			CannotJump();
		});

	ArmRender->SetAnimationUpdateEvent("4Skill", 14, [this]
		{
			if (ArmRender->IsAnimationEnd() == true)
			{
				isAttack = false;
				GetLevel()->TimeEvent.AddEvent(3.0f, [this](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager) {isAtCoolTime = false; }, false);
				GetTransform()->SetLocalPosition({ -120, -10, -4.0f });
				ArmCollision->GetTransform()->SetLocalPosition({ -30, -50 });
				ArmRender->ChangeAnimation("Stand");
			}
		});

	//Stand
	ArmRender->CreateAnimation({ .AnimationName = "Stand",.SpriteName = "LArm2_Stand",.Loop = true,.ScaleToTexture = true,.FrameTime = {0.13f, 0.1f,0.1f, 0.1f, 0.13f, 0.1f, 0.1f, 0.1f } });
	ArmRender->SetAnimationUpdateEvent("Stand", 0, [this]
		{
			GetTransform()->SetLocalPosition({ -120, -10, -4.0f });
		});

	ArmRender->CreateAnimation({ .AnimationName = "Hit",.SpriteName = "LArm2_Hit",.FrameInter = 0.5f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Hit", 0, [this]
		{
			GetTransform()->SetLocalPosition({ -145, -40, -4.0f });
			if (ArmRender->IsAnimationEnd() == true)
			{
				GetTransform()->SetLocalPosition({ -120, -10, -4.0f });
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

	ArmRender->CreateAnimation({ .AnimationName = "Death",.SpriteName = "LArm2_Death",.Loop = false,.ScaleToTexture = true,.FrameTime = FrameVec });
	ArmRender->SetAnimationUpdateEvent("Death", 18, [this]
		{
			if (isArmDeath == true)
			{
				return;
			}

			ArmRender->ColorOptionValue.MulColor.a -= 4.0f * DeltaTime;

			if (ArmRender->ColorOptionValue.MulColor.a <= 0.0f)
			{
				ArmRender->ColorOptionValue.MulColor.a = 0.0f;

				Zakum::GetZakum()->ArmDeath(isLeft, ArmIndex);
				Zakum::GetZakum()->SubArmCount();
				Zakum::GetZakum()->BodyStart();

				isArmDeath = true;
			}
		});

	ArmRender->SetAnimationUpdateEvent("Death", 0, [this]
		{
			isStartDeath = true;
			GetTransform()->SetLocalPosition({ -145, -60, -4.0f });
			ArmCollision->Off();
		});
}

void ZakumLArm_2::SkillLock()
{
	Player::GetCurPlayer()->SkillLock(4.0f);
}

void ZakumLArm_2::MoreMiss()
{
	Player::GetCurPlayer()->MoreMiss(1.0f);
}

void ZakumLArm_2::DamagedDouble()
{
	Player::GetCurPlayer()->DamagedDouble(4.0f);
}

void ZakumLArm_2::CannotJump()
{
	Player::GetCurPlayer()->CannotJump(4.0f);
}