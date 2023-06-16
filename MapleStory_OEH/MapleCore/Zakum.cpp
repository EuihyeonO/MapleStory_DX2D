#include "PrecompileHeader.h"
#include "Zakum.h"
#include "ZakumRArm_0.h"
#include "ZakumRArm_1.h"
#include "ZakumRArm_2.h"
#include "ZakumRArm_3.h"

#include "ZakumLArm_0.h"
#include "ZakumLArm_1.h"
#include "ZakumLArm_2.h"
#include "ZakumLArm_3.h"

#include "Player.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>

std::shared_ptr<Zakum> Zakum::GlobalZakum = nullptr;

Zakum::Zakum()
{
}

Zakum::~Zakum()
{
}

void Zakum::Start()
{
	GlobalZakum = DynamicThis<Zakum>();

	TimeCounting();

	BodyRender = CreateComponent<GameEngineSpriteRenderer>();
	GetTransform()->SetLocalPosition({ -10.0f , 40.0f, -5.0f });
	
	SetAnimation();
	BodyRender->ChangeAnimation("Spawn");
}

void Zakum::Update(float _DeltaTime)
{
	if (GameEngineInput::IsKey("MyTest") == false)
	{
		GameEngineInput::CreateKey("MyTest", 'B');
	}

	if (GameEngineInput::IsDown("MyTest") == true)
	{
		float4 Dir = Player::GetCurPlayer()->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();
		Dir.Normalize();

		Player::GetCurPlayer()->KnockBack(Dir, 1000.0f, 10);
	}

	//ArmAttack();
}

void Zakum::Render(float _DeltaTime)
{

}

void Zakum::CreateArm(bool _isLeft, int _ArmIndex)
{
	if (_isLeft == true)
	{
		switch (_ArmIndex)
		{
		case 0:
			if (LArm_0 == nullptr)
			{
				LArm_0 = GetLevel()->CreateActor<ZakumLArm_0>();
				LArm_0->GetTransform()->SetLocalPosition({ -110, 110, -4.0f });
			}
			break;
		case 1:
			if (LArm_1 == nullptr)
			{
				LArm_1 = GetLevel()->CreateActor<ZakumLArm_1>();
				LArm_1->GetTransform()->SetLocalPosition({ -140, 60, -4.0f });
			}
			break;
		case 2:
			if (LArm_2 == nullptr)
			{
				LArm_2 = GetLevel()->CreateActor<ZakumLArm_2>();
				LArm_2->GetTransform()->SetLocalPosition({ -140, -10, -4.0f });
			}
			break;
		case 3:
			if (LArm_3 == nullptr)
			{
				LArm_3 = GetLevel()->CreateActor<ZakumLArm_3>();
				LArm_3->GetTransform()->SetLocalPosition({ -140, -80, -4.0f });
			}
			break;
		}
	}
	else if (_isLeft == false)
	{
		switch (_ArmIndex)
		{
		case 0:
			if (RArm_0 == nullptr)
			{
				RArm_0 = GetLevel()->CreateActor<ZakumRArm_0>();
				RArm_0->GetTransform()->SetLocalPosition({ 130, 110, -4.0f });
			}
			break;
		case 1:
			if (RArm_1 == nullptr)
			{
				RArm_1 = GetLevel()->CreateActor<ZakumRArm_1>();
				RArm_1->GetTransform()->SetLocalPosition({ 160, 60, -4.0f });
			}
			break;
		case 2:
			if (RArm_2 == nullptr)
			{
				RArm_2 = GetLevel()->CreateActor<ZakumRArm_2>();
				RArm_2->GetTransform()->SetLocalPosition({ 170, -10, -4.0f });
			}
			break;
		case 3:
			if (RArm_3 == nullptr)
			{
				RArm_3 = GetLevel()->CreateActor<ZakumRArm_3>();
				RArm_3->GetTransform()->SetLocalPosition({ 180, -80, -4.0f });
			}
			break;
		}
	}
}

void Zakum::SetAnimation()
{
	if (nullptr == GameEngineSprite::Find("ZakumSpawn"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ZakumSpawn").GetFullPath());

		NewDir.Move("Phase1");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase1Stand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase1Die").GetFullPath());

		NewDir.MoveParent();
		NewDir.Move("Phase2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase2Stand").GetFullPath());
	}

	BodyRender->CreateAnimation({ .AnimationName = "Spawn",.SpriteName = "ZakumSpawn",.FrameInter = 0.11f,.Loop = false,.ScaleToTexture = true });
	BodyRender->CreateAnimation({ .AnimationName = "Phase1Die",.SpriteName = "Phase1Die",.FrameInter = 0.11f,.Loop = false,.ScaleToTexture = true });
	BodyRender->CreateAnimation({ .AnimationName = "Phase2Stand",.SpriteName = "Phase2Stand",.FrameInter = 0.09f,.Loop = true,.ScaleToTexture = true });

	BodyRender->SetAnimationStartEvent("Spawn", 20, [this]
		{
			BodyRender->ChangeAnimation("Phase1Stand");
			GetTransform()->AddLocalPosition({ 22, -33, 0.0f });
			CreateArm(true, 0);
			CreateArm(true, 1);
			CreateArm(true, 2);
			CreateArm(true, 3);
			CreateArm(false, 0);
			CreateArm(false, 1);
			CreateArm(false, 2);
			CreateArm(false, 3);
		});

	BodyRender->CreateAnimation({ .AnimationName = "Phase1Stand",.SpriteName = "Phase1Stand",.FrameInter = 0.09f,.Loop = true,.ScaleToTexture = true });
}

void Zakum::ArmDeath(bool _isLeft, int _ArmIndex)
{
	if (_isLeft == true)
	{
		switch (_ArmIndex)
		{
		case 0:
			if(LArm_0 != nullptr)
			{
				LArm_0->Death();
				LArm_0 = nullptr;
			}
			break;
		case 1:
			if (LArm_1 != nullptr)
			{
				LArm_1->Death();
				LArm_1 = nullptr;
			}
			break;
		case 2:
			if (LArm_2 != nullptr)
			{
				LArm_2->Death();
				LArm_2 = nullptr;
			}
			break;
		case 3:
			if (LArm_3 != nullptr)
			{
				LArm_3->Death();
				LArm_3 = nullptr;
			}
			break;
		}
	}
	else if (_isLeft == false)
	{
		switch (_ArmIndex)
		{
		case 0:
			if (RArm_0 != nullptr)
			{
				RArm_0->Death();
				RArm_0 = nullptr;
			}
			break;
		case 1:
			if (RArm_1 != nullptr)
			{
				RArm_1->Death();
				RArm_1 = nullptr;
			}
			break;
		case 2:
			if (RArm_2 != nullptr)
			{
				RArm_2->Death();
				RArm_2 = nullptr;
			}
			break;
		case 3:
			if (RArm_3 != nullptr)
			{
				RArm_3->Death();
				RArm_3 = nullptr;
			}
			break;
		}
	}
}


void Zakum::ArmAttack()
{
	if (isArmAtCoolTime == true)
	{
		return;
	}

	int Num = GameEngineRandom::MainRandom.RandomInt(0, 7);

	switch (Num)
	{
	case 0:
		if(LArm_0 != nullptr)
		{
			LArm_0->Attack();
		}
		break;
	case 1:
		if (LArm_1 != nullptr)
		{
			LArm_1->Attack();
		}
		break;
	case 2:
		if (LArm_2 != nullptr)
		{
			LArm_2->Attack();
		}
		break;
	case 3:
		if (LArm_3 != nullptr)
		{
			LArm_3->Attack();
		}
		break;
	case 4:
		if (RArm_0 != nullptr)
		{
			RArm_0->Attack();
		}
		break;
	case 5:
		if (RArm_1 != nullptr)
		{
			RArm_1->Attack();
		}
		break;
	case 6:
		if (RArm_2 != nullptr)
		{
			RArm_2->Attack();
		}
		break;
	case 7:
		if (RArm_3 != nullptr)
		{
			RArm_3->Attack();
		}
		break;
	}

	isArmAtCoolTime = true;

	GetLevel()->TimeEvent.AddEvent(1.0f, [this](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager){isArmAtCoolTime = false; }, false);
}

void Zakum::DefUp()
{
	std::weak_ptr<GameEngineSpriteRenderer> DefUpEff = CreateComponent<GameEngineSpriteRenderer>();
	DefUpEff.lock()->SetScaleToTexture("DefUp.png");
	DefUpEff.lock()->GetTransform()->SetWorldPosition({ 15, 80, -5.0f });

	Zakum::GetZakum()->SetIsDefUp(true);

	GetLevel()->TimeEvent.AddEvent(10.0f, [DefUpEff, this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {DefUpEff.lock()->Death(); Zakum::GetZakum()->SetIsDefUp(false); }, false);
}

void Zakum::AtPowerUp()
{
	std::weak_ptr<GameEngineSpriteRenderer> AtUpEff = CreateComponent<GameEngineSpriteRenderer>();
	AtUpEff.lock()->SetScaleToTexture("AtPowerUp.png");
	AtUpEff.lock()->GetTransform()->SetWorldPosition({ 0, 80, -5.0f });
	Zakum::GetZakum()->SetIsAtPowerUp(true);

	GetLevel()->TimeEvent.AddEvent(10.0f, [AtUpEff, this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {AtUpEff.lock()->Death(); Zakum::GetZakum()->SetIsAtPowerUp(false); }, false);
}

//void Zakum::BodyStart()
//{
//	if (ArmCount <= 0)
//	{
//		BodyAttackStart = true;
//		//GetTransform()->AddLocalPosition({ 0, -6.0f });
//		//CurPhase++;
//		//BodyRender->ChangeAnimation("Phase1Die");
//		
//		//GetLevel()->TimeEvent.AddEvent(1.0f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {BodyRender->ChangeAnimation("Phase2Stand"); });
//		//다음페이즈스폰	
//	}
//	
//}