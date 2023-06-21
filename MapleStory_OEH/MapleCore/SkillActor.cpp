#include "PrecompileHeader.h"
#include "SkillActor.h"
#include "Player.h"
#include "PlayerValue.h"
#include "Star.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <ctime>

SkillActor::SkillActor()
{
}

SkillActor::~SkillActor()
{
}

void SkillActor::Start()
{

	TimeCounting();

	GetTransform()->AddLocalPosition({ 0, 0,  -10.0f });
}

void SkillActor::Update(float _DeltaTime)
{
	if (UpdateFunc != nullptr)
	{
		UpdateFunc(*this);
	}
}

void SkillActor::Render(float _DeltaTime)
{
}

void SkillActor::SetSkillActor(const std::string_view& _SkillName, bool _isRePlay)
{
	SkillName = _SkillName.data();
	isRePlay = _isRePlay;
	
	AnimationRender = CreateComponent<GameEngineSpriteRenderer>();	

	SetSkillAnimation();
	SetUpdateFunc();
}

void SkillActor::SetSkillAnimation()
{	
	if(SkillName == "Haste")
	{
		AniFrameList[SkillName].push_back(0.09f);
		SkillOriginPosVector[SkillName].push_back({ 0,  45 });	
		LastIndex = 9;
	}

	else if (SkillName == "LuckySeven")
	{
		AniFrameList[SkillName].push_back(0.08f);
		LastIndex = 6;
	}

	else if (SkillName == "Avenger")
	{
		AniFrameList[SkillName].push_back(0.045f);
		LastIndex = 14;
	}

	else if (SkillName == "JavelinBooster")
	{
		AniFrameList[SkillName].push_back(0.09f);
		SkillOriginPosVector[SkillName].push_back({ 0,20 });
		LastIndex = 8;
	}

	else if (SkillName == "ShadowPartner")
	{
		AniFrameList[SkillName].push_back(0.085f);
		AniFrameList[SkillName].push_back(0.085f);
		AniFrameList[SkillName].push_back(0.085f);
		AniFrameList[SkillName].push_back(0.085f);
		AniFrameList[SkillName].push_back(0.085f);
		AniFrameList[SkillName].push_back(0.085f);
		AniFrameList[SkillName].push_back(0.085f);
		AniFrameList[SkillName].push_back(0.085f);
		AniFrameList[SkillName].push_back(0.085f);
		AniFrameList[SkillName].push_back(0.085f);
		AniFrameList[SkillName].push_back(0.085f);
		AniFrameList[SkillName].push_back(0.095f);
		AniFrameList[SkillName].push_back(0.13f);
		AniFrameList[SkillName].push_back(0.1f);
		AniFrameList[SkillName].push_back(0.12f);
		AniFrameList[SkillName].push_back(0.12f);

		SkillOriginPosVector[SkillName].push_back({ 0,58 });

		LastIndex = 15;
	}
	else if (SkillName == "FlashJump")
	{
		AniFrameList[SkillName].push_back(0.08f);
		AniFrameList[SkillName].push_back(0.08f);
		AniFrameList[SkillName].push_back(0.08f);
		AniFrameList[SkillName].push_back(0.08f);
		AniFrameList[SkillName].push_back(0.08f);

		LastIndex = 4;
	}
}

void SkillActor::SetUpdateFunc()
{
	if (SkillName == "Haste")
	{
		UpdateFunc = &SkillActor::Haste;
	}
	else if (SkillName == "LuckySeven")
	{
		UpdateFunc = &SkillActor::LuckySeven;
	}
	else if (SkillName == "Avenger")
	{
		UpdateFunc = &SkillActor::Avenger;
	}
	else if (SkillName == "JavelinBooster")
	{
		UpdateFunc = &SkillActor::JavelinBooster;
	}
	else if (SkillName == "ShadowPartner")
	{
		UpdateFunc = &SkillActor::ShadowPartner;
	}
	else if (SkillName == "FlashJump")
	{
		UpdateFunc = &SkillActor::FlashJump;
	}
}

void SkillActor::Haste()
{
	std::shared_ptr<Player> CurPlayer = Player::GetCurPlayer();

	CurPlayer->SetMovable(false);
	CurPlayer->SetMoveType("Alert");

	TimeCounting();

	AnimationCount += TimeCount;

	if (AnimationIndex < LastIndex && AniFrameList["Haste"][0] <= AnimationCount)
	{
		std::string TextureName = "Haste" + std::to_string(AnimationIndex) + ".png";

		float4 Pos = CurPlayer->GetTransform()->GetWorldPosition();
		
		AnimationRender->SetScaleToTexture(TextureName);
		AnimationRender->GetTransform()->SetLocalPosition(Pos +  SkillOriginPosVector["Haste"][0]);
		
		if (CurPlayer->GetLeftRightDir() == "Right")
		{
			AnimationRender->GetTransform()->AddLocalPosition({ 5,0 });
		}

		AnimationCount = 0.0f;
		AnimationIndex++;
	}
	else if (AnimationIndex >= LastIndex)
	{
		Player::GetCurPlayer()->SetMovable(true);

		AnimationRender->Death();
		AnimationRender = nullptr;
		UpdateFunc = nullptr;
		Death();
	}
}


void SkillActor::LuckySeven()
{

	if (AnimationIndex == 0 && TimeCount == 0)
	{
		std::string TextureName = "LuckySevenShoot" + std::to_string(AnimationIndex) + ".png";

		std::shared_ptr<Player> CurPlayer = Player::GetCurPlayer();
		float4 Pos = CurPlayer->GetTransform()->GetWorldPosition();

		AnimationRender->SetScaleToTexture(TextureName);

		AnimationRender->GetTransform()->SetLocalPosition(Pos + float4{ 0, 25 });

		if (Player::GetCurPlayer()->GetLeftRightDir() == "Right")
		{
			AnimationRender->GetTransform()->SetLocalNegativeScaleX();
			AnimationRender->GetTransform()->AddLocalPosition({ 60, 0 });
		}
		else if (Player::GetCurPlayer()->GetLeftRightDir() == "Left")
		{
			AnimationRender->GetTransform()->SetLocalPositiveScaleX();
			AnimationRender->GetTransform()->AddLocalPosition({ -60, 0 });
		}

		TimeCounting();
		AnimationCount += TimeCount;
		return;
	}

	TimeCounting();
	AnimationCount += TimeCount;

	if (AnimationIndex >= LastIndex)
	{
		Death();
		return;
	}

	else if (AniFrameList["LuckySeven"][0] <= AnimationCount)
	{
		std::string TextureName = "LuckySevenShoot" + std::to_string(AnimationIndex) + ".png";

		std::shared_ptr<Player> CurPlayer = Player::GetCurPlayer();
		float4 Pos = CurPlayer->GetTransform()->GetWorldPosition();

		AnimationRender->SetScaleToTexture(TextureName);

		AnimationRender->GetTransform()->SetLocalPosition(Pos + float4{0, 25});

		if (Player::GetCurPlayer()->GetLeftRightDir() == "Right")
		{
			AnimationRender->GetTransform()->SetLocalNegativeScaleX();
			AnimationRender->GetTransform()->AddLocalPosition({ 60, 0 });
		}
		else if (Player::GetCurPlayer()->GetLeftRightDir() == "Left")
		{
			AnimationRender->GetTransform()->SetLocalPositiveScaleX();
			AnimationRender->GetTransform()->AddLocalPosition({ -60, 0 });
		}

		AnimationCount = 0.0f;
		AnimationIndex++;
	}
}

void SkillActor::Avenger()
{
	std::shared_ptr<Player> CurPlayer = Player::GetCurPlayer();
	CurPlayer->SetMovable(false);

	float4 Pos = CurPlayer->GetTransform()->GetWorldPosition();
	AnimationRender->GetTransform()->SetLocalPosition(Pos);

	if (Player::GetCurPlayer()->GetLeftRightDir() == "Right")
	{
		AnimationRender->GetTransform()->AddLocalPosition({ 7, 27 });
	}
	else if (Player::GetCurPlayer()->GetLeftRightDir() == "Left")
	{
		AnimationRender->GetTransform()->AddLocalPosition({ -7, 27 });
	}

	if (AnimationIndex == 0 && TimeCount == 0)
	{		

		std::string TextureName = "AvengerShoot" + std::to_string(AnimationIndex) + ".png";
		AnimationRender->SetScaleToTexture(TextureName);

		TimeCounting();
		AnimationCount += TimeCount;

		if (Player::GetCurPlayer()->GetLeftRightDir() == "Right")
		{
			AnimationRender->GetTransform()->SetLocalNegativeScaleX();
		}
		else if (Player::GetCurPlayer()->GetLeftRightDir() == "Left")
		{
			AnimationRender->GetTransform()->SetLocalPositiveScaleX();
		}

		return;
	}

	TimeCounting();

	float Speed = PlayerValue::GetValue()->GetAttackSpeed();
	AnimationCount += TimeCount * Speed;

	if (AnimationCount >= AniFrameList["Avenger"][0])
	{
		std::shared_ptr<Player> CurPlayer = Player::GetCurPlayer();

		AnimationIndex++;
		AnimationCount = 0.0f;

		if (AnimationIndex > 13)
		{
			CurPlayer->isSwing = false;
			CurPlayer->SetMovable(true);
			Death();
			return;
		}
		else if (AnimationIndex == 11)
		{
			CurPlayer->AniIndex = 1;
			CurPlayer->AnimationCount = 0;

			std::shared_ptr<Star> NewStar1 = GetLevel()->CreateActor<Star>(static_cast<int>(RenderOrder::Weapon));
			NewStar1->SetStarName("Avenger");
			NewStar1->SetTimingTime(0.0f);
			NewStar1->SetUpdateFuction(&Star::AvengerMove);
			NewStar1->SetTargetMonster(nullptr);
			NewStar1->SetType("Avenger");
			NewStar1->Set_IsRealAttack(false);

			if (Player::CurPlayer->isOnShadow == true)
			{
				std::shared_ptr<Star> NewStar2 = GetLevel()->CreateActor<Star>(static_cast<int>(RenderOrder::Weapon));
				NewStar2->SetStarName("Avenger");
				NewStar2->SetTimingTime(0.09f);
				NewStar2->SetUpdateFuction(&Star::AvengerMove);
				NewStar2->SetTargetMonster(nullptr);
				NewStar2->SetType("Avenger");
			}

			CurPlayer->isAvenger = false;
		}

		std::string TextureName = "AvengerShoot" + std::to_string(AnimationIndex) + ".png";
		AnimationRender->SetScaleToTexture(TextureName);

		if (Player::GetCurPlayer()->GetLeftRightDir() == "Right")
		{
			AnimationRender->GetTransform()->SetLocalNegativeScaleX();
		}
		else if (Player::GetCurPlayer()->GetLeftRightDir() == "Left")
		{
			AnimationRender->GetTransform()->SetLocalPositiveScaleX();
		}
	}
}

void SkillActor::JavelinBooster()
{
	std::shared_ptr<Player> CurPlayer = Player::GetCurPlayer();
	CurPlayer->SetMovable(false);
	CurPlayer->SetMoveType("Alert");

	TimeCounting();

	AnimationCount += TimeCount;

	if (AnimationIndex < LastIndex && AniFrameList["JavelinBooster"][0] <= AnimationCount)
	{
		std::string TextureName = "JavelinBooster" + std::to_string(AnimationIndex) + ".png";

		float4 Pos = CurPlayer->GetTransform()->GetWorldPosition();

		AnimationRender->SetScaleToTexture(TextureName);

		AnimationRender->GetTransform()->SetLocalPosition(Pos + SkillOriginPosVector["JavelinBooster"][0]);
		
		if (CurPlayer->GetLeftRightDir() == "Right")
		{
			float4 scale = AnimationRender->GetTransform()->GetLocalScale();
			AnimationRender->GetTransform()->SetLocalScale({ -scale.x, scale.y });
		}

		AnimationCount = 0.0f;
		AnimationIndex++;
	}
	else if (AnimationIndex >= LastIndex)
	{
		Player::GetCurPlayer()->SetMovable(true);
		Death();
		return;
	}
}

void SkillActor::ShadowPartner()
{
	std::shared_ptr<Player> CurPlayer = Player::GetCurPlayer();
	CurPlayer->SetMovable(false);
	CurPlayer->SetMoveType("Alert");

	TimeCounting();

	AnimationCount += TimeCount;

	if (AnimationIndex < LastIndex && AniFrameList["ShadowPartner"][AnimationIndex] <= AnimationCount)
	{
		std::string TextureName = "ShadowPartner" + std::to_string(AnimationIndex) + ".png";

		float4 Pos = CurPlayer->GetTransform()->GetWorldPosition();

		AnimationRender->SetScaleToTexture(TextureName);

		AnimationRender->GetTransform()->SetLocalPosition(Pos + SkillOriginPosVector["ShadowPartner"][0]);

		if (CurPlayer->GetLeftRightDir() == "Right")
		{
			float4 scale = AnimationRender->GetTransform()->GetLocalScale();
			AnimationRender->GetTransform()->SetLocalScale({ -scale.x, scale.y });
			AnimationRender->GetTransform()->AddLocalPosition({ -35, 0 });
		}
		else if (CurPlayer->GetLeftRightDir() == "Left")
		{
			AnimationRender->GetTransform()->AddLocalPosition({ 30, 0 });
		}

		AnimationCount = 0.0f;
		AnimationIndex++;
	}
	else if (AnimationIndex >= LastIndex)
	{
		AnimationCount = 0.0f;
		AnimationIndex = 0;

		CurPlayer->SetMovable(true);

		if (isRePlay == false)
		{
			Death();
			return;
		}

		UpdateFunc = [this](SkillActor&)
		{
			std::shared_ptr<Player> CurPlayer = Player::GetCurPlayer();

			float4 Dir;
			if (CurPlayer->GetLeftRightDir() == "Right")
			{
				Dir = { -1, 1 };
			}
			else if (CurPlayer->GetLeftRightDir() == "Left")
			{
				Dir = { 1, 1 };
			}

			if (CurPlayer->isBuffOn("ShadowPartner") == false)
			{
				AnimationCount += TimeCount;

				if (AnimationCount >= 0.05f)
				{
					if (AnimationIndex == 2)
					{
						Death();
						return;
					}

					std::string TextureName = "ShadowDead"+ std::to_string(AnimationIndex) + ".png";
					AnimationRender->SetScaleToTexture(TextureName);
					AnimationIndex++;
					AnimationCount = 0.0f;
				}

				AnimationRender->GetTransform()->SetLocalPosition(CurPlayer->GetTransform()->GetWorldPosition() + float4{ Dir.x * 20.0f, 35.0f });
			}
			else
			{
				std::string MoveType = CurPlayer->GetMoveType().data();
				int AniIndex = CurPlayer->GetAniIndex();

				std::string TextureName = "Shadow" + MoveType + std::to_string(AniIndex) + ".png";
				AnimationRender->SetScaleToTexture(TextureName);

				float4 Scale = AnimationRender->GetTransform()->GetLocalScale();

				AnimationRender->GetTransform()->SetLocalScale({ Dir.x * Scale.x, Scale.y });
				AnimationRender->GetTransform()->SetLocalPosition(CurPlayer->GetTransform()->GetWorldPosition() + float4{ Dir.x * 20.0f, 35.0f});
				GetTransform()->SetLocalPosition({ 0, 0, 1.0f });
			}
		};

		return;
	}
}

void SkillActor::FlashJump()
{
	std::shared_ptr<Player> CurPlayer = Player::GetCurPlayer();
	TimeCounting();

	if (AnimationIndex == 0 && AnimationCount == 0.0f)
	{
		float4 Pos = Player::GetCurPlayer()->GetTransform()->GetWorldPosition();

		GetTransform()->SetLocalPosition(Pos + float4{-30, 30.0f, 1.0f});

		if (Player::GetCurPlayer()->GetLeftRightDir() == "Left")
		{
			GetTransform()->SetLocalPosition(Pos + float4{ 35.0f, 30.0f, 1.0f });
		}
		else
		{
			GetTransform()->SetLocalScale({ -1, 1 });
		}

		AnimationRender->SetScaleToTexture("FlashJump0.png");
	}

	AnimationCount += TimeCount;

	if (AnimationCount >= AniFrameList["FlashJump"][0])
	{
		AnimationCount = 0.0f;
		AnimationIndex++;

		if (AnimationIndex > LastIndex)
		{
			Death();
			return;
		}

		std::string TexName = "FlashJump" + std::to_string(AnimationIndex) + ".png";
		AnimationRender->SetScaleToTexture(TexName);
	}
}