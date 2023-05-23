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
	int Level = PlayerValue::Value.GetKeenEyesLevel();
	
	if(Level < 20)
	{ 
		PlayerValue::Value.KeenEyesLevelUp();
	}
}