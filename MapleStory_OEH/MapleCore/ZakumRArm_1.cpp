#include "PrecompileHeader.h"
#include "ZakumRArm_1.h"
#include "Zakum.h"


ZakumRArm_1::ZakumRArm_1()
{
	ArmIndex = 1;
	isLeft = false;
}

ZakumRArm_1::~ZakumRArm_1()
{
}

void ZakumRArm_1::Start()
{
	ArmRender = CreateComponent<GameEngineSpriteRenderer>();

	SetAnimation();

	ArmCollision = CreateComponent<GameEngineCollision>();
	ArmCollision->GetTransform()->SetLocalScale({ 150, 70 });
	ArmCollision->SetColType(ColType::AABBBOX2D);
	ArmCollision->SetOrder(static_cast<int>(CollisionOrder::Monster));
	ArmCollision->GetTransform()->SetLocalPosition({ 10, -30 });
	ArmCollision->On();

	ArmRender->ChangeAnimation("Stand");
}

void ZakumRArm_1::Update(float _DeltaTime)
{
	DeltaTime = _DeltaTime;
}

void ZakumRArm_1::Render(float _DeltaTime)
{

}

void ZakumRArm_1::SetAnimation()
{
	//1Attack

	ArmRender->CreateAnimation({ .AnimationName = "1Attack",.SpriteName = "RArm1_1Attack",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("1Attack", 0, [this] {GetTransform()->SetLocalPosition({ 210, 50, -4.0f }); isAttack = true;  });

	ArmRender->SetAnimationStartEvent("1Attack", 9, [this]
		{
			//ÀÌÆåÆ®
		});

	ArmRender->SetAnimationUpdateEvent("1Attack", 14, [this]
		{
			if (ArmRender->IsAnimationEnd() == true)
			{
				isAttack = false;
				ArmRender->ChangeAnimation("Stand");
			}
		});

	//2Attack

	ArmRender->CreateAnimation({ .AnimationName = "2Attack",.SpriteName = "RArm1_2Attack",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("2Attack", 0, [this] {GetTransform()->SetLocalPosition({ 200, 50, -4.0f }); isAttack = true;  });

	ArmRender->SetAnimationStartEvent("2Attack", 9, [this]
		{
			//ÀÌÆåÆ®
		});

	ArmRender->SetAnimationUpdateEvent("2Attack", 14, [this]
		{
			if (ArmRender->IsAnimationEnd() == true)
			{
				isAttack = false;
				ArmRender->ChangeAnimation("Stand");
			}
		});

	//
	ArmRender->CreateAnimation({ .AnimationName = "Stand",.SpriteName = "RArm1_Stand",.Loop = true,.ScaleToTexture = true,.FrameTime = {0.13f, 0.1f,0.1f, 0.1f, 0.13f, 0.1f, 0.1f, 0.1f } });
	ArmRender->SetAnimationUpdateEvent("Stand", 0, [this]
		{
			GetTransform()->SetLocalPosition({ 160, 60, -4.0f });
		});

	ArmRender->CreateAnimation({ .AnimationName = "Hit",.SpriteName = "RArm1_Hit",.FrameInter = 0.5f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Hit", 0, [this]
		{
			GetTransform()->SetLocalPosition({ 180, 50, -4.0f });
			if (ArmRender->IsAnimationEnd() == true)
			{
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

	ArmRender->CreateAnimation({ .AnimationName = "Death",.SpriteName = "RArm1_Death",.Loop = false,.ScaleToTexture = true,.FrameTime = FrameVec });
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
			GetTransform()->SetLocalPosition({ 200, 70, -4.0f });
			ArmCollision->Off();
		});
}