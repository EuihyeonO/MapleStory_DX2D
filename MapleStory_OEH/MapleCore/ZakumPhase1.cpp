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

#include "Boogie.h"
#include "SmallZakum0.h"
#include "SmallZakum1.h"
#include "SmallZakum2.h"

#include "Player.h"
#include "PlayerValue.h"

#include "ContentUIRenderer.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>

void Zakum::SetPhase1Attack()
{
	//Attack1
	BodyRender->CreateAnimation({ .AnimationName = "Phase1_1Attack",.SpriteName = "Phase1_1Attack",.Loop = false,.ScaleToTexture = true,.FrameTime = {0.13f, 0.13f, 0.13f, 0.92f, 0.13f, 0.13f, 0.13f, 0.13f} });

	BodyRender->SetAnimationUpdateEvent("Phase1_1Attack", 0, [this]
		{
			GetTransform()->SetLocalPosition({ 12.0f, 13.0f, -4.0f });

			if (isAttack == false)
			{
				std::weak_ptr<GameEngineSpriteRenderer> Eff0 = CreateComponent<GameEngineSpriteRenderer>();
				Eff0.lock()->CreateAnimation({ .AnimationName = "1AtEffect",.SpriteName = "1AtEffect0",.FrameInter = 0.09f,.Loop = false,.ScaleToTexture = true });
				Eff0.lock()->SetAnimationUpdateEvent("1AtEffect", 18, [Eff0] {if (Eff0.lock()->IsAnimationEnd() == true) { Eff0.lock()->Death(); }});
				Eff0.lock()->ChangeAnimation("1AtEffect");
			}

			isAttack = true;
			isBodyAttCoolTime = true;
		});

	BodyRender->SetAnimationStartEvent("Phase1_1Attack", 3, [this]
		{
			std::weak_ptr<GameEngineSpriteRenderer> Eff1 = CreateComponent<GameEngineSpriteRenderer>();
			Eff1.lock()->SetTexture("1AtEffect10.png");
			Eff1.lock()->GetTransform()->SetWorldScale({ 205, 271 });
			Eff1.lock()->ColorOptionValue.MulColor.a = 0.0f;

			UpdateFuncList.push_back([Eff1, this]
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
							return true;
						}
					}

					return false;

				});
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
				GetTransform()->SetLocalPosition({ 12.0f, 7.0f,-4.0f });
				isAttack = false;
				GetLevel()->TimeEvent.AddEvent(3.0f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {isBodyAttCoolTime = false; });
			}});

	//Attack2
	BodyRender->CreateAnimation({ .AnimationName = "Phase1_2Attack",.SpriteName = "Phase1_2Attack",.Loop = false,.ScaleToTexture = true,.FrameTime = {0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.2f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f} });

	BodyRender->SetAnimationUpdateEvent("Phase1_2Attack", 0, [this]
		{
			GetTransform()->SetLocalPosition({ 12.0f, 4.0f, -4.0f });

			if (isAttack == false)
			{
				std::weak_ptr<GameEngineSpriteRenderer> Eff0 = CreateComponent<GameEngineSpriteRenderer>();
				Eff0.lock()->GetTransform()->SetWorldPosition({ 0, -20.0f, -5.0f });
				Eff0.lock()->CreateAnimation({ .AnimationName = "2AtEffect",.SpriteName = "2AtEffect0",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
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

				std::string SpriteName = "2AtEffect" + std::to_string(Index);
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

				std::string SpriteName = "2AtEffect" + std::to_string(Index);
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

				std::string SpriteName = "2AtEffect" + std::to_string(Index);
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
				GetTransform()->SetLocalPosition({ 12.0f, 7.0f, -4.0f });
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
			GetTransform()->SetLocalPosition({ 12.0f, 22.0f, -4.0f });

			if (isAttack == false)
			{
				std::weak_ptr<GameEngineSpriteRenderer> Eff = CreateComponent<GameEngineSpriteRenderer>();
				Eff.lock()->GetTransform()->SetWorldPosition({ 20.0f, 0.0f, -4.0f });
				Eff.lock()->CreateAnimation({ .AnimationName = "3AtEffect",.SpriteName = "3AtEffect",.FrameInter = 0.08f,.Loop = false,.ScaleToTexture = true });
				Eff.lock()->SetAnimationUpdateEvent("3AtEffect", 18, [Eff] {if (Eff.lock()->IsAnimationEnd() == true) { Eff.lock()->Death(); }});
				Eff.lock()->ChangeAnimation("3AtEffect");
			}

			isAttack = true;
			isBodyAttCoolTime = true;
		});

	BodyRender->SetAnimationStartEvent("Phase1_3Attack", 10, [this]
		{
			int Count = 0;
			while (Count < 5)
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
				AtObj.lock()->CreateAnimation({ .AnimationName = "Phase1_3AtObj",.SpriteName = "3AtObj",.Loop = false,.ScaleToTexture = true,.FrameTime = {0.105f, 0.105f, 0.105f, 0.105f, 0.105f, 0.105f, 0.105f, 0.2f, 0.09f, 0.09f, 0.09f, 0.09f, 0.09f, 0.09f, 0.09f, 0.09f, 0.09f, 0.09f, 0.09f} });
				AtObj.lock()->ChangeAnimation("Phase1_3AtObj");

				std::weak_ptr<GameEngineCollision> AtObjCol = CreateComponent<GameEngineCollision>();
				AtObjCol.lock()->SetColType(ColType::AABBBOX2D);
				AtObjCol.lock()->GetTransform()->SetParent(AtObj.lock()->GetTransform());
				AtObjCol.lock()->GetTransform()->SetWorldScale({ 50, 220 });

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
				GetTransform()->SetLocalPosition({ 12.0f, 7.0f, -4.0f });
				isAttack = false;
				GetLevel()->TimeEvent.AddEvent(3.0f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {isBodyAttCoolTime = false; });
				BodyRender->ChangeAnimation("Phase1Stand");
			}
		});


	//1Skill

	BodyRender->CreateAnimation({ .AnimationName = "Phase1_1Skill",.SpriteName = "Phase1_1Skill",.FrameInter = 0.088f,.Loop = false,.ScaleToTexture = true });

	BodyRender->SetAnimationUpdateEvent("Phase1_1Skill", 0, [this]
		{
			GetTransform()->SetLocalPosition({ 12, 3, -4.0f });

			if (isAttack == false)
			{
				std::weak_ptr<GameEngineSpriteRenderer> Eff = CreateComponent<GameEngineSpriteRenderer>();
				Eff.lock()->GetTransform()->SetWorldPosition({ -20.0f, 10.0f, -4.0f });
				Eff.lock()->CreateAnimation({ .AnimationName = "1SkEffect",.SpriteName = "1SkEffect",.FrameInter = 0.088f,.Loop = false,.ScaleToTexture = true });
				Eff.lock()->SetAnimationUpdateEvent("1SkEffect", 14, [Eff] {if (Eff.lock()->IsAnimationEnd() == true) { Eff.lock()->Death(); }});
				Eff.lock()->ChangeAnimation("1SkEffect");
			}

			isAttack = true;
			isBodyAttCoolTime = true;
		});

	BodyRender->SetAnimationStartEvent("Phase1_1Skill", 13, [this]
		{
			GetTransform()->AddLocalPosition({ 0, 8, 0 });
		});

	BodyRender->SetAnimationUpdateEvent("Phase1_1Skill", 16, [this]
		{
			if (BodyRender->IsAnimationEnd() == true)
			{
				BodyRender->ChangeAnimation("Phase1Stand");
				GetTransform()->SetLocalPosition({ 12, 7, -4.0f });

				std::weak_ptr<GameEngineSpriteRenderer> Eff = CreateComponent<GameEngineSpriteRenderer>();
				Eff.lock()->SetScaleToTexture("ZakumPowerUp.png");
				Eff.lock()->GetTransform()->SetWorldPosition({ -20.0f, -100.0f, -4.0f });

				isBodyDefUp = true;
				isAttack = false;

				GetLevel()->TimeEvent.AddEvent(3.0f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {isBodyAttCoolTime = false; });
				GetLevel()->TimeEvent.AddEvent(10.0f, [Eff, this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {Eff.lock()->Death(); isBodyDefUp = false; });
			}
		});

	//2Skill

	BodyRender->CreateAnimation({ .AnimationName = "Phase1_2Skill",.SpriteName = "Phase1_2Skill",.FrameInter = 0.093f,.Loop = false,.ScaleToTexture = true });
	BodyRender->SetAnimationUpdateEvent("Phase1_2Skill", 0, [this]
		{
			GetTransform()->SetLocalPosition({ 12, 15, -4.0f });

			if (isAttack == false)
			{
				std::weak_ptr<GameEngineSpriteRenderer> Eff = CreateComponent<GameEngineSpriteRenderer>();
				Eff.lock()->GetTransform()->SetWorldPosition({ 0, 0, -4.0f });
				Eff.lock()->CreateAnimation({ .AnimationName = "2SkEffect",.SpriteName = "2SkEffect",.FrameInter = 0.093f,.Loop = false,.ScaleToTexture = true });
				Eff.lock()->SetAnimationUpdateEvent("2SkEffect", 14, [Eff] {if (Eff.lock()->IsAnimationEnd() == true) { Eff.lock()->Death(); }});
				Eff.lock()->ChangeAnimation("2SkEffect");
			}

			isAttack = true;
			isBodyAttCoolTime = true;
		});


	BodyRender->SetAnimationUpdateEvent("Phase1_2Skill", 15, [this]
		{
			if (BodyRender->IsAnimationEnd() == true)
			{
				BodyRender->ChangeAnimation("Phase1Stand");
				GetTransform()->SetLocalPosition({ 12, 7, -4.0f });

				isAttack = false;
				GetLevel()->TimeEvent.AddEvent(3.0f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {isBodyAttCoolTime = false; });
			}
		});

	//3Skill

	BodyRender->CreateAnimation({ .AnimationName = "Phase1_3Skill",.SpriteName = "Phase1_3Skill",.FrameInter = 0.094f,.Loop = false,.ScaleToTexture = true });

	BodyRender->SetAnimationUpdateEvent("Phase1_3Skill", 0, [this]
		{
			GetTransform()->SetLocalPosition({ 12, 12, -4.0f });

			if (isAttack == false)
			{
				std::weak_ptr<GameEngineSpriteRenderer> Eff = CreateComponent<GameEngineSpriteRenderer>();
				Eff.lock()->GetTransform()->SetWorldPosition({ 0, 0, -4.0f });
				Eff.lock()->CreateAnimation({ .AnimationName = "3SkEffect",.SpriteName = "3SkEffect",.FrameInter = 0.094f,.Loop = false,.ScaleToTexture = true });

				Eff.lock()->SetAnimationUpdateEvent("3SkEffect", 15, [Eff, this]
					{
						if (Eff.lock()->IsAnimationEnd() == true)
						{
							Eff.lock()->Death();

							int Num = GameEngineRandom::MainRandom.RandomInt(0, 3);

							if (Num == 0)
							{
								for (int i = 0; i < 5; i++)
								{
									std::shared_ptr<SmallZakum0> Mob = GetLevel()->CreateActor<SmallZakum0>();
									Mob->SetColMap("ColAlterOfZakum.png");

								}
							}
							else if (Num == 1)
							{
								for (int i = 0; i < 5; i++)
								{
									std::shared_ptr<Boogie> NewBoogie = GetLevel()->CreateActor<Boogie>();
									NewBoogie->SetColMap("ColAlterOfZakum.png");
								}
							}
							else if (Num == 2)
							{
								for (int i = 0; i < 5; i++)
								{
									std::shared_ptr<SmallZakum1> Mob = GetLevel()->CreateActor<SmallZakum1>();
									Mob->SetColMap("ColAlterOfZakum.png");

								}
							}
							else if (Num == 3)
							{
								for (int i = 0; i < 5; i++)
								{
									std::shared_ptr<SmallZakum2> Mob = GetLevel()->CreateActor<SmallZakum2>();
									Mob->SetColMap("ColAlterOfZakum.png");

								}
							}
						}
					});

				Eff.lock()->ChangeAnimation("3SkEffect");
			}

			isAttack = true;
			isBodyAttCoolTime = true;
		});

	BodyRender->SetAnimationUpdateEvent("Phase1_3Skill", 15, [this]
		{
			if (BodyRender->IsAnimationEnd() == true)
			{
				BodyRender->ChangeAnimation("Phase1Stand");
				GetTransform()->SetLocalPosition({ 12, 7, -4.0f });

				isAttack = false;
				GetLevel()->TimeEvent.AddEvent(3.0f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {isBodyAttCoolTime = false; });
			}
		});
}