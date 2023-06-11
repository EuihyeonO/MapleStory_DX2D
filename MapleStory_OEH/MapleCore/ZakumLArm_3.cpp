#include "PrecompileHeader.h"
#include "ZakumLArm_3.h"
#include "Zakum.h"

ZakumLArm_3::ZakumLArm_3()
{
	ArmIndex = 3;
	isLeft = true;
}

ZakumLArm_3::~ZakumLArm_3()
{
}

void ZakumLArm_3::Start()
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

void ZakumLArm_3::Update(float _DeltaTime)
{

}

void ZakumLArm_3::Render(float _DeltaTime)
{

}

void ZakumLArm_3::SetAnimation()
{

	ArmRender->CreateAnimation({ .AnimationName = "Stand",.SpriteName = "LArm3_Stand",.Loop = true,.ScaleToTexture = true,.FrameTime = {0.13f, 0.1f,0.1f, 0.1f, 0.13f, 0.1f, 0.1f, 0.1f } });
	ArmRender->SetAnimationUpdateEvent("Stand", 0, [this]
		{
			GetTransform()->SetLocalPosition({ -140, -80, -4.0f });
		});

	ArmRender->CreateAnimation({ .AnimationName = "Hit",.SpriteName = "LArm3_Hit",.FrameInter = 0.5f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Hit", 0, [this]
		{
			GetTransform()->SetLocalPosition({ -155, -70, -4.0f });
			if (ArmRender->IsAnimationEnd() == true)
			{
				ArmRender->ChangeAnimation("Stand");
			}
		});

	ArmRender->CreateAnimation({ .AnimationName = "Death",.SpriteName = "LArm3_Death",.FrameInter = 0.11f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Death", 18, [this] {Zakum::GetZakum()->ArmDeath(isLeft, ArmIndex); });
	ArmRender->SetAnimationUpdateEvent("Death", 0, [this]
		{
			GetTransform()->SetLocalPosition({ -170, -95, -4.0f });
			ArmCollision->Off();
		});
}