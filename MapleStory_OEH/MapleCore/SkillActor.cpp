#include "PrecompileHeader.h"
#include "SkillActor.h"
#include "Player.h"

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
		SkillOriginPosVector[SkillName].push_back({ 0,  45 });
		SkillOriginPosVector[SkillName].push_back({ 0,  45 });
		SkillOriginPosVector[SkillName].push_back({ 0,  45 });
		SkillOriginPosVector[SkillName].push_back({ 0,  45 });
		SkillOriginPosVector[SkillName].push_back({ 0,  45 });
		SkillOriginPosVector[SkillName].push_back({ 0,  45 });
		SkillOriginPosVector[SkillName].push_back({ 0,  45 });
		SkillOriginPosVector[SkillName].push_back({ 0,  45 });
	}

	else if (SkillName == "LuckySeven")
	{
		AniFrameList[SkillName].push_back(0.12f);
		AniFrameList[SkillName].push_back(0.12f);
		AniFrameList[SkillName].push_back(0.12f);
		AniFrameList[SkillName].push_back(0.12f);
		AniFrameList[SkillName].push_back(0.12f);
		AniFrameList[SkillName].push_back(0.12f);
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
}

void SkillActor::Haste()
{
	Player::GetCurPlayer()->SetMovable(false);
	Player::GetCurPlayer()->SetMoveType("Alert");
	TimeCounting();

	AnimationCount += TimeCount;

	if (AnimationIndex < SkillOriginPosVector["Haste"].size() && AniFrameList["Haste"][0] <= AnimationCount)
	{
		std::string TextureName = "Haste" + std::to_string(AnimationIndex) + ".png";

		Player* CurPlayer = Player::GetCurPlayer();
		float4 Pos = CurPlayer->GetTransform()->GetWorldPosition();
		
		AnimationRender->SetScaleToTexture(TextureName);

		AnimationRender->GetTransform()->SetLocalPosition(Pos +  SkillOriginPosVector["Haste"][AnimationIndex]);
		
		if (Player::GetCurPlayer()->GetLeftRightDir() == "Right")
		{
			AnimationRender->GetTransform()->AddLocalPosition({ 5,0 });
		}

		AnimationCount = 0.0f;
		AnimationIndex++;
	}
	else if (AnimationIndex >= SkillOriginPosVector["Haste"].size())
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

	TimeCounting();
	AnimationCount += TimeCount;


	if (AnimationIndex >= AniFrameList["LuckySeven"].size())
	{
		AnimationRender->Death();
		AnimationRender = nullptr;
		UpdateFunc = nullptr;
		Death();

		return;
	}

	else if (AniFrameList["LuckySeven"][AnimationIndex] <= AnimationCount)
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

void SkillActor::TimeCounting()
{	
	CurTime = static_cast<float>(clock());

	TimeCount = (CurTime - PrevTime) / 1000.0f;

	PrevTime = CurTime;	
}
