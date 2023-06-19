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
#include "PlayerValue.h"

#include "ContentRenderer.h"

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
	SetAttack();

	BodyRender->ChangeAnimation("Spawn");

	BlackOut = CreateComponent<ContentRenderer>();
}

void Zakum::Update(float _DeltaTime)
{
	if (GameEngineInput::IsKey("MyTest") == false)
	{
		GameEngineInput::CreateKey("MyTest", 'B');
	}

	if (GameEngineInput::IsDown("MyTest") == true)
	{
		//float4 Dir = Player::GetCurPlayer()->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();
		//Dir.Normalize();

		//Player::GetCurPlayer()->KnockBack(Dir, 1000.0f, 10);
		//BodyRender->ChangeAnimation("Phase1_1Attack");
	}

	float4 PlayerPos = Player::GetCurPlayer()->GetTransform()->GetWorldPosition();

	BlackOut->SetTexture("MouseTest.png");
	BlackOut->GetTransform()->SetWorldScale({ 800, 600 });
	BlackOut->GetTransform()->SetWorldPosition(GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition() + float4{0, 0, -100.0f});
	BlackOut->SetCircleMulColor({ 400, 300, 50.0f, 0.0f});

	DeltaTime = _DeltaTime;

	if(UpdateFunc != nullptr)
	{
		UpdateFunc();
	}

	//Attack();
}

void Zakum::Attack()
{
	if (BodyAttackStart == true)
	{
		BodyAttack();
	}
	else
	{
		ArmAttack();
	}
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

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase1_1Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase1_1AtEffect0").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase1_2Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase1_2AtEffect0").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase1_2AtEffect1").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase1_2AtEffect2").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase1_2AtEffect3").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase1_2AtEffect4").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase1_3Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase1_3AtEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase1_3AtObj").GetFullPath());

		NewDir.Move("Phase1_1AtEffect1");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}

		NewDir.MoveParent();

		NewDir.MoveParent();
		NewDir.Move("Phase2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase2Stand").GetFullPath());
	}

	BodyRender->CreateAnimation({ .AnimationName = "Spawn",.SpriteName = "ZakumSpawn",.FrameInter = 0.11f,.Loop = false,.ScaleToTexture = true });
	BodyRender->CreateAnimation({ .AnimationName = "Phase1Die",.SpriteName = "Phase1Die",.FrameInter = 0.11f,.Loop = false,.ScaleToTexture = true });
	BodyRender->CreateAnimation({ .AnimationName = "Phase1Stand",.SpriteName = "Phase1Stand",.FrameInter = 0.09f,.Loop = true,.ScaleToTexture = true });
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
	if (isArmAttCoolTime == true)
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

	isArmAttCoolTime = true;

	GetLevel()->TimeEvent.AddEvent(1.0f, [this](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager){isArmAttCoolTime = false; }, false);
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

void Zakum::SetAttack()
{
	//Attack1
	BodyRender->CreateAnimation({ .AnimationName = "Phase1_1Attack",.SpriteName = "Phase1_1Attack",.Loop = false,.ScaleToTexture = true,.FrameTime = {0.13f, 0.13f, 0.13f, 0.92f, 0.13f, 0.13f, 0.13f, 0.13f} });

	BodyRender->SetAnimationUpdateEvent("Phase1_1Attack", 0, [this]
		{
			GetTransform()->SetLocalPosition({ 12.0f, 14.0f, -4.0f });

			if (isAttack == false)
			{
				std::weak_ptr<GameEngineSpriteRenderer> Eff0 = CreateComponent<GameEngineSpriteRenderer>();
				Eff0.lock()->CreateAnimation({ .AnimationName = "1AtEffect",.SpriteName = "Phase1_1AtEffect0",.FrameInter = 0.09f,.Loop = false,.ScaleToTexture = true });
				Eff0.lock()->SetAnimationUpdateEvent("1AtEffect", 18, [Eff0] {if (Eff0.lock()->IsAnimationEnd() == true) { Eff0.lock()->Death(); }});
				Eff0.lock()->ChangeAnimation("1AtEffect");
			}

			isAttack = true;
			isBodyAttCoolTime = true;
		});

	BodyRender->SetAnimationStartEvent("Phase1_1Attack", 3, [this]
		{
			std::weak_ptr<GameEngineSpriteRenderer> Eff1 = CreateComponent<GameEngineSpriteRenderer>();
			Eff1.lock()->SetTexture("Phase1_1AtEffect10.png");
			Eff1.lock()->GetTransform()->SetWorldScale({ 205, 271 });
			Eff1.lock()->ColorOptionValue.MulColor.a = 0.0f;

			UpdateFunc = [Eff1, this]
			{
				if (BodyRender->GetCurrentFrame() == 3)
				{
					Eff1.lock()->ColorOptionValue.MulColor.a += 1.5f * DeltaTime;

					if (Eff1.lock()->ColorOptionValue.MulColor.a >= 1.0f)
					{
						Eff1.lock()->ColorOptionValue.MulColor.a = 1.0f;
					}

					Eff1.lock()->GetTransform()->SetWorldScale({ 205, 187 });
					Eff1.lock()->GetTransform()->SetWorldPosition({ 20, 10.0f, -6.0f });
				}

				if (BodyRender->GetCurrentFrame() >= 4)
				{
					float4 PrevScale = Eff1.lock()->GetTransform()->GetWorldScale();
					Eff1.lock()->GetTransform()->AddWorldScale({ 205.0f * 10.0f * DeltaTime, 187 * 10.0f * DeltaTime });
					Eff1.lock()->GetTransform()->SetWorldPosition({ 20, 10.0f, -6.0f });

					Eff1.lock()->ColorOptionValue.MulColor.a -= 3.0f * DeltaTime;

					if (Eff1.lock()->ColorOptionValue.MulColor.a <= 0.0f)
					{
						Eff1.lock()->Death();
						UpdateFunc = nullptr;
						return;
					}
				}
			};
		});

	BodyRender->SetAnimationStartEvent("Phase1_1Attack", 4, [this]
		{
			float4 Pos = GetTransform()->GetWorldPosition();
			float4 PlayerPos = Player::GetCurPlayer()->GetTransform()->GetWorldPosition();
			float4 Dir = PlayerPos - Pos;
			Dir.Normalize();

			int CurHp = PlayerValue::GetValue()->GetHp();

			Player::GetCurPlayer()->KnockBack(Dir, 1000.0f, CurHp - 1);
		});

	BodyRender->SetAnimationUpdateEvent("Phase1_1Attack", 7,
		[this] {
			if (BodyRender->IsAnimationEnd() == true)
			{
				BodyRender->ChangeAnimation("Phase1Stand");
				GetTransform()->AddLocalPosition({ 0.0f, -7.0f });
				isAttack = false;
				GetLevel()->TimeEvent.AddEvent(3.0f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {isBodyAttCoolTime = false; });
			}});

	//Attack2
	BodyRender->CreateAnimation({ .AnimationName = "Phase1_2Attack",.SpriteName = "Phase1_2Attack",.Loop = false,.ScaleToTexture = true,.FrameTime = {0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.2f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f} });

	BodyRender->SetAnimationUpdateEvent("Phase1_2Attack", 0, [this]
		{
			//GetTransform()->SetLocalPosition({ 12.0f, 14.0f, -4.0f });

			if (isAttack == false)
			{
				std::weak_ptr<GameEngineSpriteRenderer> Eff0 = CreateComponent<GameEngineSpriteRenderer>();
				Eff0.lock()->GetTransform()->SetWorldPosition({ 0, -20.0f, -5.0f });
				Eff0.lock()->CreateAnimation({ .AnimationName = "2AtEffect",.SpriteName = "Phase1_2AtEffect0",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
				Eff0.lock()->SetAnimationUpdateEvent("2AtEffect", 16, [Eff0] {if (Eff0.lock()->IsAnimationEnd() == true) { Eff0.lock()->Death(); }});

				Eff0.lock()->ChangeAnimation("2AtEffect");
			}

			isAttack = true;
			isBodyAttCoolTime = true;
		});

	BodyRender->SetAnimationStartEvent("Phase1_2Attack", 9, [this]
		{
			for (int i = 0; i < 5; i++)
			{
				std::weak_ptr<GameEngineSpriteRenderer> Eff1 = CreateComponent<GameEngineSpriteRenderer>();
				std::weak_ptr<GameEngineCollision> EffCol = CreateComponent<GameEngineCollision>();

				int Index = GameEngineRandom::MainRandom.RandomInt(1, 4);
				int LastIndex = 5;

				if (Index == 2 || Index == 4)
				{
					LastIndex = 4;
				}

				std::string SpriteName = "Phase1_2AtEffect" + std::to_string(Index);
				Eff1.lock()->GetTransform()->SetWorldPosition({ -500.0f + i * 200.0f , 75.0f, -5.0f });
				Eff1.lock()->CreateAnimation({ .AnimationName = "2AtEffect",.SpriteName = SpriteName,.FrameInter = 0.09f,.Loop = false,.ScaleToTexture = true });
				Eff1.lock()->SetAnimationUpdateEvent("2AtEffect", LastIndex, [Eff1, EffCol] {if (Eff1.lock()->IsAnimationEnd() == true) { Eff1.lock()->Death(); EffCol.lock()->Death(); }});

				EffCol.lock()->SetColType(ColType::AABBBOX2D);

				for (int i = 0; i < LastIndex - 1; i++)
				{
					Eff1.lock()->SetAnimationUpdateEvent("2AtEffect", i, [Eff1, EffCol, this]
						{
							if (Player::GetCurPlayer()->GetisHit() == false)
							{
								EffCol.lock()->GetTransform()->SetWorldScale(Eff1.lock()->GetTransform()->GetWorldScale() * 0.5f);
								EffCol.lock()->GetTransform()->SetWorldPosition(Eff1.lock()->GetTransform()->GetWorldPosition() - float4{ 0, 120.0f });

								if (EffCol.lock()->Collision(static_cast<int>(CollisionOrder::Player), ColType::AABBBOX2D, ColType::AABBBOX2D) != nullptr)
								{
									Player::GetCurPlayer()->Hit(Att);
								}
							}
						});
				}

				Eff1.lock()->ChangeAnimation("2AtEffect");
			}
		});

	BodyRender->SetAnimationStartEvent("Phase1_2Attack", 11, [this]
		{
			for (int i = 0; i < 5; i++)
			{
				std::weak_ptr<GameEngineSpriteRenderer> Eff1 = CreateComponent<GameEngineSpriteRenderer>();
				std::weak_ptr<GameEngineCollision> EffCol = CreateComponent<GameEngineCollision>();

				int Index = GameEngineRandom::MainRandom.RandomInt(1, 4);
				int LastIndex = 5;

				if (Index == 2 || Index == 4)
				{
					LastIndex = 4;
				}

				std::string SpriteName = "Phase1_2AtEffect" + std::to_string(Index);
				Eff1.lock()->GetTransform()->SetWorldPosition({ -300.0f + i * 200.0f , 75.0f, -5.0f });
				Eff1.lock()->CreateAnimation({ .AnimationName = "2AtEffect",.SpriteName = SpriteName,.FrameInter = 0.09f,.Loop = false,.ScaleToTexture = true });
				Eff1.lock()->SetAnimationUpdateEvent("2AtEffect", LastIndex, [Eff1, EffCol] {if (Eff1.lock()->IsAnimationEnd() == true) {
					Eff1.lock()->Death(); EffCol.lock()->Death();
				}});

				EffCol.lock()->SetColType(ColType::AABBBOX2D);

				for (int i = 0; i < LastIndex - 1; i++)
				{
					Eff1.lock()->SetAnimationUpdateEvent("2AtEffect", i, [Eff1, EffCol, this]
						{
							if (Player::GetCurPlayer()->GetisHit() == false)
							{
								EffCol.lock()->GetTransform()->SetWorldScale(Eff1.lock()->GetTransform()->GetWorldScale() * 0.5f);
								EffCol.lock()->GetTransform()->SetWorldPosition(Eff1.lock()->GetTransform()->GetWorldPosition() - float4{ 0, 120.0f });

								if (EffCol.lock()->Collision(static_cast<int>(CollisionOrder::Player), ColType::AABBBOX2D, ColType::AABBBOX2D) != nullptr)
								{
									Player::GetCurPlayer()->Hit(Att);
								}
							}
						});
				}

				Eff1.lock()->ChangeAnimation("2AtEffect");
			}
		});

	BodyRender->SetAnimationStartEvent("Phase1_2Attack", 13, [this]
		{
			for (int i = 0; i < 5; i++)
			{
				std::weak_ptr<GameEngineSpriteRenderer> Eff1 = CreateComponent<GameEngineSpriteRenderer>();
				std::weak_ptr<GameEngineCollision> EffCol = CreateComponent<GameEngineCollision>();

				int Index = GameEngineRandom::MainRandom.RandomInt(1, 4);
				int LastIndex = 5;

				if (Index == 2 || Index == 4)
				{
					LastIndex = 4;
				}

				std::string SpriteName = "Phase1_2AtEffect" + std::to_string(Index);
				Eff1.lock()->GetTransform()->SetLocalPosition({ -400.0f + i * 200.0f , 75.0f, -5.0f });
				Eff1.lock()->CreateAnimation({ .AnimationName = "2AtEffect",.SpriteName = SpriteName,.FrameInter = 0.09f,.Loop = false,.ScaleToTexture = true });
				Eff1.lock()->SetAnimationUpdateEvent("2AtEffect", LastIndex, [Eff1, EffCol] {if (Eff1.lock()->IsAnimationEnd() == true) { Eff1.lock()->Death(); EffCol.lock()->Death(); }});
				Eff1.lock()->ChangeAnimation("2AtEffect");

				EffCol.lock()->SetColType(ColType::AABBBOX2D);

				for (int i = 0; i < LastIndex - 1; i++)
				{
					Eff1.lock()->SetAnimationUpdateEvent("2AtEffect", i, [Eff1, EffCol, this]
						{
							if (Player::GetCurPlayer()->GetisHit() == false)
							{
								EffCol.lock()->GetTransform()->SetWorldScale(Eff1.lock()->GetTransform()->GetWorldScale() * 0.5f);
								EffCol.lock()->GetTransform()->SetWorldPosition(Eff1.lock()->GetTransform()->GetWorldPosition() - float4{ 0, 120.0f });

								if (EffCol.lock()->Collision(static_cast<int>(CollisionOrder::Player), ColType::AABBBOX2D, ColType::AABBBOX2D) != nullptr)
								{
									Player::GetCurPlayer()->Hit(Att);
								}
							}
						});
				}
			}
		});

	BodyRender->SetAnimationUpdateEvent("Phase1_2Attack", 16, [this]
		{
			if (BodyRender->IsAnimationEnd() == true)
			{
				BodyRender->ChangeAnimation("Phase1Stand");
				isAttack = false;
				GetLevel()->TimeEvent.AddEvent(3.0f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {isBodyAttCoolTime = false; });
			}
		});


	//3Attack

	BodyRender->CreateAnimation({ .AnimationName = "Phase1_3Attack",.SpriteName = "Phase1_3Attack",.Loop = false,.ScaleToTexture = true,.FrameTime = {0.08f, 0.08f, 0.08f, 0.08f, 0.08f, 0.08f, 0.08f, 0.08f, 0.08f,0.56f, 0.08f, 0.08f, 0.12f } });
	BodyRender->SetAnimationUpdateEvent("Phase1_3Attack", 0,
		[this]
		{
			GetTransform()->SetLocalPosition({ 12.0f, 23.0f, -4.0f });

			if (isAttack == false)
			{
				std::weak_ptr<GameEngineSpriteRenderer> Eff = CreateComponent<GameEngineSpriteRenderer>();
				Eff.lock()->GetTransform()->SetWorldPosition({ 20.0f, 0.0f, -4.0f});
				Eff.lock()->CreateAnimation({ .AnimationName = "3AtEffect",.SpriteName = "Phase1_3AtEffect",.FrameInter = 0.08f,.Loop = false,.ScaleToTexture = true });
				Eff.lock()->SetAnimationUpdateEvent("3AtEffect", 18, [Eff] {if (Eff.lock()->IsAnimationEnd() == true) { Eff.lock()->Death(); }});
				Eff.lock()->ChangeAnimation("3AtEffect");
			}

			isAttack = true;
			isBodyAttCoolTime = true;
		});

	BodyRender->SetAnimationStartEvent("Phase1_3Attack", 10, [this]
		{
			int Count = 0;
			while(Count < 5)
			{
				std::weak_ptr<GameEngineSpriteRenderer> AtObj = CreateComponent<GameEngineSpriteRenderer>();
				float Xpos = GameEngineRandom::MainRandom.RandomFloat(-450.0f, 450.0f);
				float Ypos = 0.0f;
			
				if (Xpos > -450.0f && Xpos < -220.0f)
				{
					Ypos = 160.0f;
				}
				else if (Xpos > -130.0f && Xpos < -90.0f)
				{
					Ypos = 166.0f;
				}
				else if (Xpos > -60.0f && Xpos < 0.0f)
				{
					Ypos = 180.0f;
				}
				else if (Xpos > 45.0f && Xpos < 100.0f)
				{
					Ypos = 168.0f;
				}
				else if (Xpos > 130.0f && Xpos < 180.0f)
				{
					Ypos = 176.0f;
				}
				else if (Xpos > 220.0f && Xpos < 450.0f)
				{
					Ypos = 160.0f;
				}
				else
				{
					continue;
				}
			
				AtObj.lock()->GetTransform()->SetWorldPosition({ Xpos, Ypos, -5.0f });
				AtObj.lock()->CreateAnimation({ .AnimationName = "Phase1_3AtObj",.SpriteName = "Phase1_3AtObj",.Loop = false,.ScaleToTexture = true,.FrameTime = {0.105f, 0.105f, 0.105f, 0.105f, 0.105f, 0.105f, 0.105f, 0.2f, 0.09f, 0.09f, 0.09f, 0.09f, 0.09f, 0.09f, 0.09f, 0.09f, 0.09f, 0.09f, 0.09f} });
				AtObj.lock()->ChangeAnimation("Phase1_3AtObj");
				
				std::weak_ptr<GameEngineCollision> AtObjCol = CreateComponent<GameEngineCollision>();
				AtObjCol.lock()->SetColType(ColType::AABBBOX2D);
				AtObjCol.lock()->GetTransform()->SetParent(AtObj.lock()->GetTransform());
				AtObjCol.lock()->GetTransform()->SetWorldScale({50, 220});
				
				for (int i = 0; i < 5; i++)
				{
					AtObj.lock()->SetAnimationUpdateEvent("Phase1_3AtObj", i + 8, [AtObj, AtObjCol, i]
						{
							AtObjCol.lock()->GetTransform()->SetLocalPosition({ 0, 165.0f + i * -95.0f });

							if (AtObjCol.lock()->Collision(static_cast<int>(CollisionOrder::Player), ColType::AABBBOX2D, ColType::AABBBOX2D) != nullptr)
							{
								Player::GetCurPlayer()->Hit(10);
								AtObjCol.lock()->Off();
							}
						}
					);
				}

				AtObj.lock()->SetAnimationUpdateEvent("Phase1_3AtObj", 14, [AtObjCol] {AtObjCol.lock()->Off(); });
				AtObj.lock()->SetAnimationUpdateEvent("Phase1_3AtObj", 18, [AtObj, AtObjCol] {if (AtObj.lock()->IsAnimationEnd() == true) { AtObjCol.lock()->Death(); AtObj.lock()->Death(); }});

				Count++;
			}
		});

	BodyRender->SetAnimationUpdateEvent("Phase1_3Attack", 12, [this]
		{
			if (BodyRender->IsAnimationEnd() == true)
			{
				GetTransform()->AddLocalPosition({ 0, -13.0f, 0 });
				isAttack = false;
				GetLevel()->TimeEvent.AddEvent(3.0f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {isBodyAttCoolTime = false; });
				BodyRender->ChangeAnimation("Phase1Stand");
			}
		});
}

void Zakum::BodyAttack()
{
	if (isBodyAttCoolTime == true)
	{
		return;
	}

	int Num = GameEngineRandom::MainRandom.RandomInt(0, 2);

	switch (Num)
	{
	case 0:
		BodyRender->ChangeAnimation("Phase1_1Attack");
		break;
	case 1:
		BodyRender->ChangeAnimation("Phase1_2Attack");
		break;
	case 2:
		BodyRender->ChangeAnimation("Phase1_3Attack");
		break;
	}
}