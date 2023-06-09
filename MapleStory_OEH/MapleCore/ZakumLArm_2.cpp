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

	if (nullptr == GameEngineSprite::Find("LArm2_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("Arm");
		NewDir.Move("Left_2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm2_Stand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm2_Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm2_Hit").GetFullPath());
	}

	ArmRender->CreateAnimation({ .AnimationName = "Stand",.SpriteName = "LArm2_Stand",.Loop = true,.ScaleToTexture = true,.FrameTime = {0.13f, 0.1f,0.1f, 0.1f, 0.13f, 0.1f, 0.1f, 0.1f } });
	ArmRender->SetAnimationUpdateEvent("Stand", 0, [this]
		{
			GetTransform()->SetLocalPosition({ -140, -10, -4.0f });
		});

	ArmRender->CreateAnimation({ .AnimationName = "Hit",.SpriteName = "LArm2_Hit",.FrameInter = 0.5f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Hit", 0, [this]
		{
			GetTransform()->SetLocalPosition({ -165, -40, -4.0f });
			if (ArmRender->IsAnimationEnd() == true)
			{
				ArmRender->ChangeAnimation("Stand");
			}
		});

	ArmRender->CreateAnimation({ .AnimationName = "Death",.SpriteName = "LArm2_Death",.FrameInter = 0.11f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Death", 18, [this] {Zakum::GetZakum()->ArmDeath(isLeft, ArmIndex);});
	ArmRender->SetAnimationUpdateEvent("Death", 0, [this]
		{
			GetTransform()->SetLocalPosition({ -165, -60, -4.0f });
			ArmCollision->Off();
		});

	ArmRender->ChangeAnimation("Stand");
	
	ArmCollision = CreateComponent<GameEngineCollision>();
	ArmCollision->GetTransform()->SetLocalScale({ 150, 40 });
	ArmCollision->SetColType(ColType::AABBBOX2D);
	ArmCollision->SetOrder(static_cast<int>(CollisionOrder::Monster));
	ArmCollision->GetTransform()->SetLocalPosition({ -30, -50 });
}

void ZakumLArm_2::Update(float _DeltaTime)
{

}

void ZakumLArm_2::Render(float _DeltaTime)
{

}
