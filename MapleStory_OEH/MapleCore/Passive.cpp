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

void Player::KeenEyes()
{
	int Level = PlayerValue::Value.GetKeenEyesLv();
	
	if(Level < 20)
	{ 
		PlayerValue::Value.KeenEyesLvUp();
	}

	RangeCheck->GetTransform()->SetLocalScale({ PlayerValue::Value.GetAttackDistance() , 100.0f });
	RangeCheck->GetTransform()->AddLocalPosition({ -5.0f , 0  });
}