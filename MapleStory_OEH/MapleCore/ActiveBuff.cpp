#include "PrecompileHeader.h"
#include "Player.h"
#include "Star.h"
#include "PlayerValue.h"
#include "ContentEnums.h"
#include "SkillActor.h"
#include "BuffList.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <ctime>
#include <functional>

void Player::Haste()
{
	if(isSwing == false && isGround == true)
	{
		if (MyBuffList->IsBuffOn("Haste") == false)
		{
			std::shared_ptr<SkillActor> Haste = GetLevel()->CreateActor<SkillActor>();
			Haste->SetSkillActor("Haste");

			std::function<void(Player&)> EndFunction = [this](Player&) {MoveSpeed = BasicMoveSpeed; };

			//지속시간은 나중에 따로 변수 만들어야함
			MyBuffList->BuffOn("Haste", EndFunction, 5.0f);

			MoveSpeed = BasicMoveSpeed + 30.0f;
		}

		else if (MyBuffList->IsBuffOn("Haste") == true)
		{
			std::shared_ptr<SkillActor> Haste = GetLevel()->CreateActor<SkillActor>();
			Haste->SetSkillActor("Haste");

			MyBuffList->Rebuff("Haste");
		}
	}
}
