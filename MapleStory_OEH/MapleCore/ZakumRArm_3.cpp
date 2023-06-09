#include "PrecompileHeader.h"
#include "ZakumRArm_3.h"
#include "Zakum.h"

ZakumRArm_3::ZakumRArm_3()
{
	ArmIndex = 3;
	isLeft = false;
}

ZakumRArm_3::~ZakumRArm_3()
{
}

void ZakumRArm_3::Start()
{
	ArmRender = CreateComponent<GameEngineSpriteRenderer>();

	if (nullptr == GameEngineSprite::Find("RArm3_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("Arm");
		NewDir.Move("Right_3");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm3_Stand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm3_Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm3_Hit").GetFullPath());
	}


	ArmRender->CreateAnimation({ .AnimationName = "Stand",.SpriteName = "RArm3_Stand",.Loop = true,.ScaleToTexture = true,.FrameTime = {0.13f, 0.1f,0.1f, 0.1f, 0.13f, 0.1f, 0.1f, 0.1f } });
	ArmRender->SetAnimationUpdateEvent("Stand", 0, [this]
		{
			GetTransform()->SetLocalPosition({ 180, -80, -4.0f });
		});

	ArmRender->CreateAnimation({ .AnimationName = "Hit",.SpriteName = "RArm3_Hit",.FrameInter = 0.5f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Hit", 0, [this]
		{
			GetTransform()->SetLocalPosition({ 200, -70, -4.0f });
			if (ArmRender->IsAnimationEnd() == true) 
			{
				ArmRender->ChangeAnimation("Stand"); 
			} 
		});
	
	ArmRender->CreateAnimation({ .AnimationName = "Death",.SpriteName = "RArm3_Death",.FrameInter = 0.11f,.Loop = false,.ScaleToTexture = true });	
	ArmRender->SetAnimationUpdateEvent("Death", 18, [this] {Zakum::GetZakum()->ArmDeath(isLeft, ArmIndex); });
	ArmRender->SetAnimationUpdateEvent("Death", 0, [this] 
		{
			GetTransform()->SetLocalPosition({ 200, -90, -4.0f });
			ArmCollision->Off();
		});
	
	ArmRender->ChangeAnimation("Stand");
	ArmCollision = CreateComponent<GameEngineCollision>();
	ArmCollision->GetTransform()->SetLocalScale({ 150, 70 });
	ArmCollision->SetColType(ColType::AABBBOX2D);
	ArmCollision->SetOrder(static_cast<int>(CollisionOrder::Monster));
	ArmCollision->GetTransform()->SetLocalPosition({ 10, -40 });
}

void ZakumRArm_3::Update(float _DeltaTime)
{

}

void ZakumRArm_3::Render(float _DeltaTime)
{

}

