#include "PrecompileHeader.h"
#include "ZakumRArm_2.h"
#include "Zakum.h"

ZakumRArm_2::ZakumRArm_2()
{
	ArmIndex = 2;
	isLeft = false;
}

ZakumRArm_2::~ZakumRArm_2()
{
}

void ZakumRArm_2::Start()
{
	ArmRender = CreateComponent<GameEngineSpriteRenderer>();

	SetAnimation();

	ArmCollision = CreateComponent<GameEngineCollision>();
	ArmCollision->GetTransform()->SetLocalScale({ 150, 70 });
	ArmCollision->SetColType(ColType::AABBBOX2D);
	ArmCollision->SetOrder(static_cast<int>(CollisionOrder::Monster));
	ArmCollision->GetTransform()->SetLocalPosition({ 10, -35 });
	ArmCollision->On();

	ArmRender->ChangeAnimation("Stand");
}

void ZakumRArm_2::Update(float _DeltaTime)
{

}

void ZakumRArm_2::Render(float _DeltaTime)
{

}

void ZakumRArm_2::SetAnimation()
{

	std::vector<float> FrameTimeVec;
	FrameTimeVec.reserve(49);

	ArmRender->CreateAnimation({ .AnimationName = "Hit",.SpriteName = "RArm2_Hit",.FrameInter = 0.5f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Hit", 0, [this]
		{
			GetTransform()->SetLocalPosition({ 200, -10, -4.0f });
			if (ArmRender->IsAnimationEnd() == true)
			{
				ArmRender->ChangeAnimation("Stand");
			}
		});

	ArmRender->CreateAnimation({ .AnimationName = "Death",.SpriteName = "RArm2_Death",.FrameInter = 0.11f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationStartEvent("Death", 18, [this] {Zakum::GetZakum()->ArmDeath(isLeft, ArmIndex); });
	ArmRender->SetAnimationUpdateEvent("Death", 0, [this]
		{
			GetTransform()->SetLocalPosition({ 200, 10, -4.0f });
			ArmCollision->Off();
		});

	ArmRender->CreateAnimation({ .AnimationName = "Stand",.SpriteName = "RArm2_Stand",.Loop = true,.ScaleToTexture = true,.FrameTime = {0.13f, 0.1f,0.1f, 0.1f, 0.13f, 0.1f, 0.1f, 0.1f } });
	ArmRender->SetAnimationUpdateEvent("Stand", 0, [this]
		{
			GetTransform()->SetLocalPosition({ 170, -10, -4.0f });
		});
}