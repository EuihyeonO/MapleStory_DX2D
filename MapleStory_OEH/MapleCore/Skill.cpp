#include "PrecompileHeader.h"
#include "Player.h"
#include "Star.h"
#include "PlayerValue.h"
#include "ContentEnums.h"
#include "SkillActor.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <ctime>

void Player::BuffUpdate()
{
	if (BuffList.size() == 0)
	{
		return;
	}

	std::list<std::function<bool(Player&)>>::iterator Start = BuffList.begin();
	std::list<std::function<bool(Player&)>>::iterator End = BuffList.end();

	for (; Start != End;)
	{
		std::function<bool(Player&)> Func = *Start;
		bool isEnd = Func(*this);

		if (isEnd == true)
		{
			Start = BuffList.erase(Start);
			continue;
		}
		else
		{
			Start++;
		}
	}
}

void Player::LuckySeven()
{
	if (MoveType == "Swing0" || MoveType == "Swing1" || MoveType == "Swing2")
	{
		return;
	}

	int SwingType = GameEngineRandom::MainRandom.RandomInt(0, 2);

	MoveType = "Swing" + std::to_string(SwingType);
	AniIndex = 0;
	isSwing = true;

	std::shared_ptr<Star> NewStar1 = GetLevel()->CreateActor<Star>(11);
	NewStar1->SetStarName("Wednes");
	NewStar1->SetTimingIndex(1);

	std::shared_ptr<Star> NewStar2 = GetLevel()->CreateActor<Star>(11);
	NewStar2->SetStarName("Wednes");
	NewStar2->SetTimingIndex(2);


	if (LeftRightDir == "Left")
	{
		NewStar1->SetDir({ -1, 0 });
		NewStar2->SetDir({ -1, 0 });
	}
	else
	{
		NewStar1->SetDir({ 1, 0 });
		NewStar2->SetDir({ 1, 0 });
	}
}

bool Player::Haste()
{
	if(isHaste == false)
	{
		isHaste = true;
		std::shared_ptr<SkillActor> Haste = GetLevel()->CreateActor<SkillActor>();
		Haste->SetSkillActor("Haste");
	}

	MoveSpeed = BasicMoveSpeed + 30.0f;
	HasteTime -= TimeCount;
	HasteAnimationCount += TimeCount;

	//버프 끝날 때
	if (HasteTime <= 0.0f)
	{
		HasteIndex = 0;
		HasteTime = 30.0f;
		MoveSpeed = BasicMoveSpeed;
		isHaste = false;
		return true;
	}
	else
	{
		return false;
	}
}