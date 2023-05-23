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

void SkillActor::SetSkillActor(const std::string_view& _SkillName)
{
	SkillName = _SkillName.data();
	
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
}

void SkillActor::Haste()
{
	Player::GetCurPlayer()->SetMovable(false);
	Player::GetCurPlayer()->SetMoveType("Alert");

	TimeCounting();

	AnimationCount += TimeCount;

	if (AnimationIndex < LastIndex && AniFrameList["Haste"][0] <= AnimationCount)
	{
		std::string TextureName = "Haste" + std::to_string(AnimationIndex) + ".png";

		Player* CurPlayer = Player::GetCurPlayer();
		float4 Pos = CurPlayer->GetTransform()->GetWorldPosition();
		
		AnimationRender->SetScaleToTexture(TextureName);
		AnimationRender->GetTransform()->SetLocalPosition(Pos +  SkillOriginPosVector["Haste"][0]);
		
		if (Player::GetCurPlayer()->GetLeftRightDir() == "Right")
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

		Player* CurPlayer = Player::GetCurPlayer();
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
		AnimationRender->Death();
		AnimationRender = nullptr;
		UpdateFunc = nullptr;
		Death();

		return;
	}

	else if (AniFrameList["LuckySeven"][0] <= AnimationCount)
	{
		std::string TextureName = "LuckySevenShoot" + std::to_string(AnimationIndex) + ".png";

		Player* CurPlayer = Player::GetCurPlayer();
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
	Player* CurPlayer = Player::GetCurPlayer();

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
		Player* CurPlayer = Player::GetCurPlayer();

		AnimationIndex++;
		AnimationCount = 0.0f;

		if (AnimationIndex > 13)
		{
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

