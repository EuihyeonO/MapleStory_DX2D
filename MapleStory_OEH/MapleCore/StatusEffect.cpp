#include "PrecompileHeader.h"
#include "Player.h"
#include "PlayerValue.h"
#include "ContentEnums.h"
#include "Star.h"
#include "BuffList.h"
#include "DropItem.h"
#include "UIController.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineBase/GameEngineRandom.h>

#include <ctime>

void Player::StatusFuncUpdate()
{
	if (StatusEffectList.size() == 0)
	{
		return;
	}

	std::map<std::string, std::function<bool()>>::iterator Start = StatusEffectList.begin();
	std::map<std::string, std::function<bool()>>::iterator End = StatusEffectList.end();

	for (; Start != End; )
	{
		if (Start->second() == true)
		{
			PoisonRender->Death();
			PoisonRender = nullptr;
			
			Start = StatusEffectList.erase(Start);
			continue;
		}

		Start++;
	}
}
void Player::Poison(float _Duration)
{
	PoisonDuration = _Duration;
	
	if (PoisonRender == nullptr)
	{
		PoisonRender = CreateComponent<GameEngineSpriteRenderer>();
		PoisonRender->CreateAnimation({ .AnimationName = "Poison",.SpriteName = "Poison",.FrameInter = 0.08f,.Loop = true,.ScaleToTexture = true });
		PoisonRender->GetTransform()->SetLocalPosition({ 0, 90.0f, -5.0f });
		PoisonRender->ChangeAnimation("Poison");
	}

	std::map<std::string, std::function<bool()>>::iterator Start = StatusEffectList.begin();
	std::map<std::string, std::function<bool()>>::iterator End = StatusEffectList.end();

	for (; Start != End; Start++)
	{
		if (Start->first == "POISON")
		{
			return;
		}
	}

	StatusEffectList["POISON"] = [this]
	{
		PoisonDuration -= TimeCount;
		PoisonCount += TimeCount;

		if (PoisonCount > 1.0f)
		{
			PoisonCount = 0.0f;
			PlayerValue::GetValue()->SubHp(5);
		}

		if (PoisonDuration < 0)
		{
			return true;
		}

		return false;
	};
}