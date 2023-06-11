#include "PrecompileHeader.h"
#include "ZakumLArm_2.h"
#include "Zakum.h"


ZakumLArm_2::ZakumLArm_2()
{
	ArmIndex = 2;
	isLeft = true;
}

ZakumLArm_2::~ZakumLArm_2()
{
}


void ZakumLArm_2::Start()
{
	ArmRender = CreateComponent<GameEngineSpriteRenderer>();

	SetAnimation();

	ArmCollision = CreateComponent<GameEngineCollision>();
	ArmCollision->GetTransform()->SetLocalScale({ 150, 40 });
	ArmCollision->SetColType(ColType::AABBBOX2D);
	ArmCollision->SetOrder(static_cast<int>(CollisionOrder::Monster));
	ArmCollision->GetTransform()->SetLocalPosition({ -30, -50 });
	ArmCollision->On();

	ArmRender->ChangeAnimation("Stand");
}

void ZakumLArm_2::Update(float _DeltaTime)
{
}

void ZakumLArm_2::Render(float _DeltaTime)
{

}


void ZakumLArm_2::SetAnimation()
{
	//Skill1

	ArmRender->CreateAnimation({ .AnimationName = "Skill1",.SpriteName = "LArm2_1Skill",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Skill1", 0, [this] {GetTransform()->SetLocalPosition({ -160, -30, -4.0f }); isAttack = true;  });

	ArmRender->SetAnimationStartEvent("Skill1", 9, [this]
		{
		});

	ArmRender->SetAnimationUpdateEvent("Skill1", 14, [this]
		{
			if (ArmRender->IsAnimationEnd() == true)
			{
				isAttack = false;
				ArmRender->ChangeAnimation("Stand");
			}
		});

	//Skill2
	ArmRender->CreateAnimation({ .AnimationName = "Skill2",.SpriteName = "LArm2_2Skill",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Skill2", 0, [this] {GetTransform()->SetLocalPosition({ -160, -30, -4.0f }); isAttack = true;  });

	ArmRender->SetAnimationStartEvent("Skill2", 9, [this]
		{
		});

	ArmRender->SetAnimationUpdateEvent("Skill2", 14, [this]
		{
			if (ArmRender->IsAnimationEnd() == true)
			{
				isAttack = false;
				ArmRender->ChangeAnimation("Stand");
			}
		});

	//Skill3
	ArmRender->CreateAnimation({ .AnimationName = "Skill3",.SpriteName = "LArm2_3Skill",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Skill3", 0, [this] {GetTransform()->SetLocalPosition({ -160, -30, -4.0f }); isAttack = true;  });

	ArmRender->SetAnimationStartEvent("Skill3", 9, [this]
		{
		});

	ArmRender->SetAnimationUpdateEvent("Skill3", 14, [this]
		{
			if (ArmRender->IsAnimationEnd() == true)
			{
				isAttack = false;
				ArmRender->ChangeAnimation("Stand");
			}
		});

	//Skill4
	ArmRender->CreateAnimation({ .AnimationName = "Skill4",.SpriteName = "LArm2_4Skill",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Skill4", 0, [this] {GetTransform()->SetLocalPosition({ -160, -30, -4.0f }); isAttack = true;  });

	ArmRender->SetAnimationStartEvent("Skill4", 9, [this]
		{
		});

	ArmRender->SetAnimationUpdateEvent("Skill4", 14, [this]
		{
			if (ArmRender->IsAnimationEnd() == true)
			{
				isAttack = false;
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
				ArmRender->ChangeAnimation("Stand");
			}
		});

	ArmRender->CreateAnimation({ .AnimationName = "Death",.SpriteName = "LArm2_Death",.FrameInter = 0.11f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Death", 18, [this] {Zakum::GetZakum()->ArmDeath(isLeft, ArmIndex); });
	ArmRender->SetAnimationUpdateEvent("Death", 0, [this]
		{
			GetTransform()->SetLocalPosition({ -145, -60, -4.0f });
			ArmCollision->Off();
		});
}