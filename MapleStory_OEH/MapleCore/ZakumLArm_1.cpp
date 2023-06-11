#include "PrecompileHeader.h"
#include "ZakumLArm_1.h"
#include "Zakum.h"
#include "Player.h"


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
	ArmCollision->GetTransform()->SetLocalScale({ 150, 40 });
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

void ZakumLArm_1::SetAnimation()
{
	//1Attack
	ArmRender->CreateAnimation({ .AnimationName = "1Attack",.SpriteName = "LArm1_1Attack",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("1Attack", 0, [this] {GetTransform()->SetLocalPosition({ -195, 40, -4.0f }); isAttack = true;  });
	
	ArmRender->SetAnimationStartEvent("1Attack", 9, [this]	
		{
			//ºÒ¶Ë ÀÌÆåÆ®
		});

	ArmRender->SetAnimationUpdateEvent("1Attack", 14, [this]
		{
			if (ArmRender->IsAnimationEnd() == true)
			{
				isAttack = false;
				ArmRender->ChangeAnimation("Stand");
			}
		});

	//Skill
	
	ArmRender->CreateAnimation({ .AnimationName = "Skill",.SpriteName = "LArm1_Skill",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Skill", 0, [this] {GetTransform()->SetLocalPosition({ -175, 40, -4.0f }); isAttack = true;  });

	ArmRender->SetAnimationStartEvent("Skill", 9, [this]
		{
			//µ¶°¡½º ÀÌÆåÆ®
		});

	ArmRender->SetAnimationUpdateEvent("Skill", 14, [this]
		{
			if (ArmRender->IsAnimationEnd() == true)
			{
				isAttack = false;
				ArmRender->ChangeAnimation("Stand");
			}
		});

	//Stand
	ArmRender->CreateAnimation({ .AnimationName = "Stand",.SpriteName = "LArm1_Stand",.Loop = true,.ScaleToTexture = true,.FrameTime = {0.13f, 0.1f,0.1f, 0.1f, 0.13f, 0.1f, 0.1f, 0.1f } });
	ArmRender->SetAnimationUpdateEvent("Stand", 0, [this]
		{
			GetTransform()->SetLocalPosition({ -120, 60, -4.0f });
		});

	ArmRender->CreateAnimation({ .AnimationName = "Hit",.SpriteName = "LArm1_Hit",.FrameInter = 0.5f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Hit", 0, [this]
		{
			GetTransform()->SetLocalPosition({ -135, 50, -4.0f });
			if (ArmRender->IsAnimationEnd() == true)
			{
				ArmRender->ChangeAnimation("Stand");
			}
		});

	ArmRender->CreateAnimation({ .AnimationName = "Death",.SpriteName = "LArm1_Death",.FrameInter = 0.11f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Death", 18, [this] {Zakum::GetZakum()->ArmDeath(isLeft, ArmIndex); });
	ArmRender->SetAnimationUpdateEvent("Death", 0, [this]
		{
			GetTransform()->SetLocalPosition({ -145, 60, -4.0f });
			ArmCollision->Off();
		});

}

