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

	if (nullptr == GameEngineSprite::Find("RArm1_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("Arm");
		NewDir.Move("Right_1");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_Stand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_Hit").GetFullPath());
	}


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

	ArmRender->CreateAnimation({ .AnimationName = "Death",.SpriteName = "RArm1_Death",.FrameInter = 0.11f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Death", 18, [this] {Zakum::GetZakum()->ArmDeath(isLeft, ArmIndex); });
	ArmRender->SetAnimationUpdateEvent("Death", 0, [this]
		{
			GetTransform()->SetLocalPosition({ 200, 70, -4.0f });
			ArmCollision->Off();
		});

	ArmRender->ChangeAnimation("Stand");

	ArmCollision = CreateComponent<GameEngineCollision>();
	ArmCollision->GetTransform()->SetLocalScale({ 150, 70 });
	ArmCollision->SetColType(ColType::AABBBOX2D);
	ArmCollision->SetOrder(static_cast<int>(CollisionOrder::Monster));
	ArmCollision->GetTransform()->SetLocalPosition({ 10, -30 });
}

void ZakumRArm_1::Update(float _DeltaTime)
{
	float4 Pos = GetTransform()->GetLocalPosition();
	int a = 0;

}

void ZakumRArm_1::Render(float _DeltaTime)
{

}
