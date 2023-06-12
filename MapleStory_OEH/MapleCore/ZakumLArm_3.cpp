#include "PrecompileHeader.h"
#include "ZakumLArm_3.h"
#include "Zakum.h"
#include "Player.h"

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
	DeltaTime = _DeltaTime;
}

void ZakumLArm_3::Render(float _DeltaTime)
{

}

void ZakumLArm_3::SetAnimation()
{
	//1Attack
	ArmRender->CreateAnimation({ .AnimationName = "1Attack",.SpriteName = "LArm3_1Attack",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true});
	ArmRender->SetAnimationUpdateEvent("1Attack", 0, [this] {GetTransform()->SetLocalPosition({ -190, -25, -4.0f }); isAttack = true;  });
	ArmRender->SetAnimationStartEvent("1Attack", 9, [this]
		{
			std::shared_ptr<GameEngineSpriteRenderer> Eff = CreateComponent<GameEngineSpriteRenderer>();
			Player::GetCurPlayer()->Hit();
			Eff->GetTransform()->SetWorldPosition(Player::GetCurPlayer()->GetTransform()->GetWorldPosition() + float4{ 3.0f, 40.0f, -10.0f });
			Eff->CreateAnimation({ .AnimationName = "1AtEffect",.SpriteName = "LArm3_1AtEffect",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
			Eff->ChangeAnimation("1AtEffect");
			Eff->SetAnimationUpdateEvent("1AtEffect", 1, [Eff, this]
				{
					Eff->ColorOptionValue.MulColor.a -= 1.5f * DeltaTime;
					
					if (Eff->ColorOptionValue.MulColor.a <= 0)
					{
						Eff->Death();
					}
				});
		});
	ArmRender->SetAnimationUpdateEvent("1Attack", 14, [this]
		{
			if (ArmRender->IsAnimationEnd() == true)
			{
				isAttack = false;
				ArmRender->ChangeAnimation("Stand");
			}
		});

	// 2Skill
	ArmRender->CreateAnimation({ .AnimationName = "2Attack",.SpriteName = "LArm3_2Attack",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("2Attack", 0, [this] {GetTransform()->SetLocalPosition({ -135, -65, -4.0f }); isAttack = true;  });
	ArmRender->SetAnimationStartEvent("2Attack", 9, [this]
		{
			std::shared_ptr<GameEngineSpriteRenderer> Eff = CreateComponent<GameEngineSpriteRenderer>();
			Player::GetCurPlayer()->Hit();
			Eff->GetTransform()->SetWorldPosition(Player::GetCurPlayer()->GetTransform()->GetWorldPosition() + float4{ 3.0f, 60.0f, -10.0f });
			Eff->CreateAnimation({ .AnimationName = "2AtEffect",.SpriteName = "LArm3_2AtEffect",.Loop = false,.ScaleToTexture = true,.FrameTime = {0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.01f} });
			Eff->ChangeAnimation("2AtEffect");
			Eff->SetAnimationUpdateEvent("2AtEffect", 5, [Eff, this]
				{
					Eff->ColorOptionValue.MulColor.a -= 1.5f * DeltaTime;

					if (Eff->ColorOptionValue.MulColor.a <= 0)
					{
						Eff->Death();
					}
				});
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
	ArmRender->CreateAnimation({ .AnimationName = "Stand",.SpriteName = "LArm3_Stand",.Loop = true,.ScaleToTexture = true,.FrameTime = {0.13f, 0.1f,0.1f, 0.1f, 0.13f, 0.1f, 0.1f, 0.1f } });
	ArmRender->SetAnimationUpdateEvent("Stand", 0, [this]
		{
			GetTransform()->SetLocalPosition({ -120, -80, -4.0f });
		});

	ArmRender->CreateAnimation({ .AnimationName = "Hit",.SpriteName = "LArm3_Hit",.FrameInter = 0.5f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("Hit", 0, [this]
		{
			GetTransform()->SetLocalPosition({ -135, -70, -4.0f });
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

	ArmRender->CreateAnimation({ .AnimationName = "Death",.SpriteName = "LArm3_Death",.Loop = false,.ScaleToTexture = true,.FrameTime = FrameVec });
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
			GetTransform()->SetLocalPosition({ -150, -95, -4.0f });
			ArmCollision->Off();
		});
}