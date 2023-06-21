#include "PrecompileHeader.h"
#include "ZakumRArm_1.h"
#include "Zakum.h"
#include "Player.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>

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

void ZakumRArm_1::Attack()
{
	if (isAtCoolTime == true)
	{
		return;
	}

	if (isStartDeath == true)
	{
		return;
	}


	int Num = GameEngineRandom::MainRandom.RandomInt(0, 1);

	switch (Num)
	{
	case 0:
		ArmRender->ChangeAnimation("1Attack");
		break;
	case 1:
		ArmRender->ChangeAnimation("2Attack");
		break;

	}
}

void ZakumRArm_1::SetAnimation()
{
	//1Attack
	ArmRender->CreateAnimation({ .AnimationName = "1Attack",.SpriteName = "RArm1_1Attack",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("1Attack", 0, [this] {GetTransform()->SetLocalPosition({ 210, 50, -4.0f }); ArmCollision->GetTransform()->SetLocalPosition({ -40, -20 });  isAttack = true; isAtCoolTime = true;  });

	ArmRender->SetAnimationStartEvent("1Attack", 9, [this]
		{
			IceHorn();
		});

	ArmRender->SetAnimationUpdateEvent("1Attack", 14, [this]
		{
			if (ArmRender->IsAnimationEnd() == true)
			{
				isAttack = false;
				GetLevel()->TimeEvent.AddEvent(3.0f, [this](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager) {isAtCoolTime = false; }, false);
				GetTransform()->SetLocalPosition({ 160, 60, -4.0f });
				ArmCollision->GetTransform()->SetLocalPosition({ 10, -30 });
				ArmRender->ChangeAnimation("Stand");
			}
		});

	//2Attack

	ArmRender->CreateAnimation({ .AnimationName = "2Attack",.SpriteName = "RArm1_2Attack",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ArmRender->SetAnimationUpdateEvent("2Attack", 0, [this] {GetTransform()->SetLocalPosition({ 200, 50, -4.0f }); ArmCollision->GetTransform()->SetLocalPosition({ -30, -20 }); isAttack = true; isAtCoolTime = true; });

	ArmRender->SetAnimationStartEvent("2Attack", 9, [this]
		{
			ElectricAttack();
		});

	ArmRender->SetAnimationUpdateEvent("2Attack", 14, [this]
		{
			if (ArmRender->IsAnimationEnd() == true)
			{
				isAttack = false;
				GetLevel()->TimeEvent.AddEvent(3.0f, [this](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager) {isAtCoolTime = false; }, false);
				GetTransform()->SetLocalPosition({ 160, 60, -4.0f });
				ArmCollision->GetTransform()->SetLocalPosition({ 10, -30 });
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
				GetTransform()->SetLocalPosition({ 160, 60, -4.0f });
				ArmRender->ChangeAnimation("Stand");
			}
		});

	//Death
	std::vector<float> FrameVec;
	FrameVec.reserve(20);

	for (int i = 0; i < 20; i++)
	{
		FrameVec.push_back(0.11f);
	}

	FrameVec[19] = 1.0f;

	ArmRender->CreateAnimation({ .AnimationName = "Death",.SpriteName = "RArm1_Death",.Loop = false,.ScaleToTexture = true,.FrameTime = FrameVec });
	ArmRender->SetAnimationUpdateEvent("Death", 19, [this]
		{
			if (isArmDeath == true)
			{
				return;
			}

			ArmRender->ColorOptionValue.MulColor.a -= 4.0f * DeltaTime;

			if (ArmRender->ColorOptionValue.MulColor.a <= 0.0f)
			{
				ArmRender->ColorOptionValue.MulColor.a = 0.0f;

				Zakum::GetZakum()->ArmDeath(isLeft, ArmIndex);
				Zakum::GetZakum()->SubArmCount();
				Zakum::GetZakum()->BodyStart();

				isArmDeath = true;
			}
		});

	ArmRender->SetAnimationUpdateEvent("Death", 0, [this]
		{
			isStartDeath = true;
			GetTransform()->SetLocalPosition({ 200, 70, -4.0f });
			ArmCollision->Off();
		});
}

void ZakumRArm_1::IceHorn()
{
	std::vector<float> FrameVec;
	FrameVec.reserve(20);

	for (int i = 0; i < 20; i++)
	{
		FrameVec.push_back(0.09f);
	}
	FrameVec[0] = 1.3f;

	int NumOfHorn = GameEngineRandom::MainRandom.RandomInt(2,4);

	for(int i = 0; i < NumOfHorn; i++)
	{
		float Xpos = GameEngineRandom::MainRandom.RandomFloat(-400, 400);

		std::weak_ptr<GameEngineSpriteRenderer> Effect = CreateComponent<GameEngineSpriteRenderer>();
		Effect.lock()->GetTransform()->SetWorldPosition({ Xpos , -40.0f, -5.0f});
		Effect.lock()->CreateAnimation({ .AnimationName = "1Attack",.SpriteName = "RArm1_1AtObj",.Loop = false,.ScaleToTexture = true,.FrameTime = FrameVec });
		Effect.lock()->ChangeAnimation("1Attack");

		std::weak_ptr<GameEngineCollision> EffCol = CreateComponent<GameEngineCollision>();
		EffCol.lock()->SetOrder(static_cast<int>(CollisionOrder::Monster));
		EffCol.lock()->Off();
		EffCol.lock()->GetTransform()->SetWorldPosition({ Xpos , -40.0f, -5.0f });
		
		for (int i = 11; i < 14; i++)
		{
			Effect.lock()->SetAnimationUpdateEvent("1Attack", i, [Effect, EffCol, this]
				{
					EffCol.lock()->On();
					EffCol.lock()->GetTransform()->SetWorldScale({ Effect.lock()->GetTransform()->GetWorldScale().x * 0.6f, Effect.lock()->GetTransform()->GetWorldScale().y });
					if (EffCol.lock()->Collision(static_cast<int>(CollisionOrder::Player), ColType::AABBBOX2D, ColType::AABBBOX2D) != nullptr)
					{
						if(Player::GetCurPlayer()->GetisHit() == false)
						{
							int RealAtt = Att;

							if (Zakum::GetZakum()->GetIsAtPowerUp() == true)
							{
								RealAtt *= 2;
							}

							Player::GetCurPlayer()->Hit(RealAtt);
							std::weak_ptr<GameEngineSpriteRenderer> AtEff = CreateComponent<GameEngineSpriteRenderer>();
							AtEff.lock()->CreateAnimation({ .AnimationName = "AtEffect",.SpriteName = "RArm1_1AtEffect",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
							AtEff.lock()->SetAnimationUpdateEvent("AtEffect", 3, [AtEff] {if (AtEff.lock()->IsAnimationEnd() == true) { AtEff.lock()->Death(); }});
							AtEff.lock()->GetTransform()->SetWorldPosition(Player::GetCurPlayer()->GetTransform()->GetWorldPosition() + float4{0, 15.0f});
							AtEff.lock()->ChangeAnimation("AtEffect");
						}
					}
				});
		}

		Effect.lock()->SetAnimationUpdateEvent("1Attack", 19, [Effect, EffCol]
			{
				if (Effect.lock()->IsAnimationEnd() == true)
				{
					EffCol.lock()->Death();
					Effect.lock()->Death();
				}
			});
	}
}


void ZakumRArm_1::ElectricAttack()
{	
	int FalseCount = 0;

	for (int i = 0; i < 6; i++)
	{
		int OnOff = GameEngineRandom::MainRandom.RandomInt(0, 1);

		if (OnOff == 0 && FalseCount < 2)
		{
			FalseCount++;
			continue;
		}
		else if (OnOff == 1 || (OnOff == 0 && FalseCount >= 2))
		{
			int SparkType = GameEngineRandom::MainRandom.RandomInt(0, 5);

			std::weak_ptr<GameEngineSpriteRenderer> Spark = CreateComponent<GameEngineSpriteRenderer>();
			std::string SpriteName = "RArm1_2AtObj" + std::to_string(SparkType);
			
			int LastIndex = 0;

			if (SparkType == 0 || SparkType == 2 || SparkType == 4 || SparkType == 5)
			{
				LastIndex = 3;
			}
			else if (SparkType == 1)
			{
				LastIndex = 4;
			}
			else if (SparkType == 3)
			{
				LastIndex = 5;
			}

			std::weak_ptr<GameEngineCollision> SparkCol = CreateComponent<GameEngineCollision>();
			SparkCol.lock()->GetTransform()->SetWorldScale({ 200, 130 });
			SparkCol.lock()->SetColType(ColType::AABBBOX2D);
			SparkCol.lock()->SetOrder(static_cast<int>(CollisionOrder::Monster));

			Spark.lock()->CreateAnimation({ .AnimationName = "Spark",.SpriteName = SpriteName,.FrameInter = 0.13f,.Loop = false,.ScaleToTexture = true});
			Spark.lock()->ChangeAnimation("Spark");
			Spark.lock()->GetTransform()->SetWorldPosition({ -400.0f + 160.0f * i, -120.0f, -5.0f });
			Spark.lock()->SetAnimationUpdateEvent("Spark", LastIndex, [Spark, SparkCol] {if (Spark.lock()->IsAnimationEnd() == true) { Spark.lock()->Death(); SparkCol.lock()->Death(); }});

			SparkCol.lock()->GetTransform()->SetWorldPosition({ -400.0f + 160.0f * i, -120.0f});

			for (int i = 0; i < LastIndex - 1; i++)
			{
				Spark.lock()->SetAnimationUpdateEvent("Spark", i, [Spark, SparkCol, this]
					{
						if (SparkCol.lock()->Collision(static_cast<int>(CollisionOrder::Player), ColType::AABBBOX2D, ColType::AABBBOX2D) != nullptr)
						{
							if(Player::GetCurPlayer()->GetisHit() == false)
							{
								std::weak_ptr<GameEngineSpriteRenderer> HitEff = CreateComponent<GameEngineSpriteRenderer>();
								HitEff.lock()->GetTransform()->SetWorldPosition(Player::GetCurPlayer()->GetTransform()->GetWorldPosition() + float4{0, 40.0f});
								HitEff.lock()->CreateAnimation({ .AnimationName = "AtEffect",.SpriteName = "RArm1_2AtEffect",.FrameInter = 0.13f,.Loop = false,.ScaleToTexture = true });
								HitEff.lock()->SetAnimationUpdateEvent("AtEffect", 5, [HitEff] {if (HitEff.lock()->IsAnimationEnd() == true) { HitEff.lock()->Death();}});
								HitEff.lock()->ChangeAnimation("AtEffect");
								
								int RealAtt = Att;

								if (Zakum::GetZakum()->GetIsAtPowerUp() == true)
								{
									RealAtt *= 2;
								}

								Player::GetCurPlayer()->Hit(RealAtt);
							}
						}
					});
			}
		}
	}

	FalseCount = 0;

	for (int i = 0; i < 4; i++)
	{
		int OnOff = GameEngineRandom::MainRandom.RandomInt(0, 1);

		if (OnOff == 0 && FalseCount < 2)
		{
			FalseCount++;
			continue;
		}
		else if (OnOff == 1 || (OnOff == 0 && FalseCount >= 2))
		{
			int SparkType = GameEngineRandom::MainRandom.RandomInt(0, 5);

			std::weak_ptr<GameEngineSpriteRenderer> Spark = CreateComponent<GameEngineSpriteRenderer>();
			std::string SpriteName = "RArm1_2AtObj" + std::to_string(SparkType);

			int LastIndex = 0;

			if (SparkType == 0 || SparkType == 2 || SparkType == 4 || SparkType == 5)
			{
				LastIndex = 3;
			}
			else if (SparkType == 1)
			{
				LastIndex = 4;
			}
			else if (SparkType == 3)
			{
				LastIndex = 5;
			}

			std::weak_ptr<GameEngineCollision> SparkCol = CreateComponent<GameEngineCollision>();
			SparkCol.lock()->GetTransform()->SetWorldScale({ 200, 130 });
			SparkCol.lock()->SetColType(ColType::AABBBOX2D);
			SparkCol.lock()->SetOrder(static_cast<int>(CollisionOrder::Monster));

			Spark.lock()->CreateAnimation({ .AnimationName = "Spark",.SpriteName = SpriteName,.FrameInter = 0.13f,.Loop = false,.ScaleToTexture = true });
			Spark.lock()->ChangeAnimation("Spark");
			Spark.lock()->SetAnimationUpdateEvent("Spark", LastIndex, [Spark, SparkCol] {if (Spark.lock()->IsAnimationEnd() == true) { Spark.lock()->Death(); SparkCol.lock()->Death(); }});

			float4 Pos = { 0, 0 };

			switch (i)
			{
			case 0:
				Pos = { -430, 70.0f, -5.0f };
				break;
			case 1:
				Pos = { -430, 200.0f, -5.0f };
				break;
			case 2:
				Pos = { 360, 0.0f, -5.0f };
				break;
			case 3:
				Pos = { 380, 210.0f, -5.0f };
				break;
			}

			Spark.lock()->GetTransform()->SetWorldPosition(Pos);
			SparkCol.lock()->GetTransform()->SetWorldPosition(Pos);

			for (int i = 0; i < LastIndex - 1; i++)
			{
				Spark.lock()->SetAnimationUpdateEvent("Spark", i, [Spark, SparkCol, this]
					{
						if (SparkCol.lock()->Collision(static_cast<int>(CollisionOrder::Player), ColType::AABBBOX2D, ColType::AABBBOX2D) != nullptr)
						{
							if (Player::GetCurPlayer()->GetisHit() == false)
							{
								std::weak_ptr<GameEngineSpriteRenderer> HitEff = CreateComponent<GameEngineSpriteRenderer>();
								HitEff.lock()->GetTransform()->SetWorldPosition(Player::GetCurPlayer()->GetTransform()->GetWorldPosition() + float4{ 0, 40.0f });
								HitEff.lock()->CreateAnimation({ .AnimationName = "AtEffect",.SpriteName = "RArm1_2AtEffect",.FrameInter = 0.13f,.Loop = false,.ScaleToTexture = true });
								HitEff.lock()->SetAnimationUpdateEvent("AtEffect", 5, [HitEff] {if (HitEff.lock()->IsAnimationEnd() == true) { HitEff.lock()->Death(); }});
								HitEff.lock()->ChangeAnimation("AtEffect");
								Player::GetCurPlayer()->Hit(10);
							}
						}
					});
			}
		}
	}
}