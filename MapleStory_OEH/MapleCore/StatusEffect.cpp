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

bool Player::FindStatusRender(const std::string_view& _StatusName)
{
	if (StatusRenderList.size() == 0)
	{
		return false;
	}

	std::map<std::string, std::shared_ptr<GameEngineSpriteRenderer>>::iterator Start = StatusRenderList.begin();
	std::map<std::string, std::shared_ptr<GameEngineSpriteRenderer>>::iterator End = StatusRenderList.end();

	for (; Start != End; Start++)
	{
		if (Start->first == _StatusName)
		{
			return true;
		}
	}

	return false;
}

void Player::DeleteStatusRender(const std::string_view& _StatusName)
{
	if (StatusRenderList.size() == 0)
	{
		return;
	}

	std::map<std::string, std::shared_ptr<GameEngineSpriteRenderer>>::iterator Start = StatusRenderList.begin();
	std::map<std::string, std::shared_ptr<GameEngineSpriteRenderer>>::iterator End = StatusRenderList.end();

	for (; Start != End;)
	{
		if (Start->first == _StatusName)
		{
			Start->second->Death();
			Start = StatusRenderList.erase(Start);
			return;
		}
		Start++;
	}
}

void Player::SortStatusRender()
{
	if (StatusRenderList.size() == 0)
	{
		return;
	}


	std::map<std::string, std::shared_ptr<GameEngineSpriteRenderer>>::iterator Start = StatusRenderList.begin();
	std::map<std::string, std::shared_ptr<GameEngineSpriteRenderer>>::iterator End = StatusRenderList.end();

	std::vector<std::string> SortRenderName;
	SortRenderName.reserve(4);

	for (; Start != End; Start++)
	{
		if (Start->first == "DAMAGEDDOUBLE")
		{
			Start->second->GetTransform()->SetLocalPosition({ 0, 40.0f, -5.0f });
		}
		else if (Start->first == "CANNOTJUMP")
		{
			Start->second->GetTransform()->SetLocalPosition({ -4.0f, 60.0f, -5.0f });
		}
		else if (Start->first == "MOREMISS" || Start->first == "SKILLLOCK")
		{
			SortRenderName.push_back(Start->first);
		}
		else if (Start->first == "POISON")
		{
			Start->second->GetTransform()->SetLocalPosition({ 0, 90.0f, -5.0f });
		}
	}

	size_t Size = SortRenderName.size();

	if (Size == 0)
	{
		return;
	}

	if (Size == 1)
	{
		float Xpos = 0.0f;

		StatusRenderList[SortRenderName[0]]->GetTransform()->SetLocalPosition({ -7.0f, 80.0f, -4.0f });
	}
	else if(Size == 2)
	{
		StatusRenderList[SortRenderName[0]]->GetTransform()->SetLocalPosition({ -15.0f, 80.0f, -4.0f });
		StatusRenderList[SortRenderName[1]]->GetTransform()->SetLocalPosition({ 15.0f, 80.0f, -4.0f });
	}
}

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
			DeleteStatusRender(Start->first);
			Start = StatusEffectList.erase(Start);
			continue;
		}
		Start++;
	}

	SortStatusRender();
}

void Player::Poison(float _Duration)
{
	if (PoisonDuration <= _Duration)
	{
		PoisonDuration = _Duration;
	}

	if (FindStatusRender("POISON") == false)
	{
		std::shared_ptr<GameEngineSpriteRenderer> PoisonRender = CreateComponent<GameEngineSpriteRenderer>();
		PoisonRender->CreateAnimation({ .AnimationName = "Poison",.SpriteName = "Poison",.FrameInter = 0.08f,.Loop = true,.ScaleToTexture = true });
		PoisonRender->GetTransform()->SetLocalPosition({ 0, 90.0f, -5.0f });
		PoisonRender->ChangeAnimation("Poison");

		StatusRenderList["POISON"] = PoisonRender;
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

void Player::SkillLock(float _Duration)
{
	isLockSkill = true;

	if (SkillLockDuration <= _Duration)
	{
		SkillLockDuration = _Duration;
	}

	if (FindStatusRender("SKILLLOCK") == false)
	{
		std::shared_ptr<GameEngineSpriteRenderer> SkillLockRender = CreateComponent<GameEngineSpriteRenderer>();
		SkillLockRender->CreateAnimation({ .AnimationName = "SKILLLOCK",.SpriteName = "SKILLLOCK",.FrameInter = 0.1f,.Loop = true,.ScaleToTexture = true });
		SkillLockRender->GetTransform()->SetLocalPosition({ 0, 90.0f, -5.0f });
		SkillLockRender->ChangeAnimation("SKILLLOCK");

		StatusRenderList["SKILLLOCK"] = SkillLockRender;
	}

	std::map<std::string, std::function<bool()>>::iterator Start = StatusEffectList.begin();
	std::map<std::string, std::function<bool()>>::iterator End = StatusEffectList.end();

	for (; Start != End; Start++)
	{
		if (Start->first == "SKILLLOCK")
		{
			return;
		}
	}

	StatusEffectList["SKILLLOCK"] = [this]
	{
		SkillLockDuration -= TimeCount;

		if (SkillLockDuration < 0)
		{
			isLockSkill = false;
			return true;
		}

		return false;
	};
}

void Player::MoreMiss(float _Duration)
{
	if (MoreMissDuration <= _Duration)
	{
		MoreMissDuration = _Duration;
	}

	if (FindStatusRender("MOREMISS") == false)
	{
		std::shared_ptr<GameEngineSpriteRenderer> MoreMissRender = CreateComponent<GameEngineSpriteRenderer>();
		MoreMissRender->CreateAnimation({ .AnimationName = "MoreMiss",.SpriteName = "MoreMiss",.FrameInter = 0.1f,.Loop = true,.ScaleToTexture = true });
		MoreMissRender->GetTransform()->SetLocalPosition({ 0, 90.0f, -5.0f });
		MoreMissRender->ChangeAnimation("MoreMiss");

		StatusRenderList["MOREMISS"] = MoreMissRender;
	}

	std::map<std::string, std::function<bool()>>::iterator Start = StatusEffectList.begin();
	std::map<std::string, std::function<bool()>>::iterator End = StatusEffectList.end();

	for (; Start != End; Start++)
	{
		if (Start->first == "MOREMISS")
		{
			return;
		}
	}

	StatusEffectList["MOREMISS"] = [this]
	{
		MoreMissDuration -= TimeCount;

		if (MoreMissDuration < 0)
		{
			return true;
		}

		return false;
	};
}

void Player::DamagedDouble(float _Duration)
{
	isDamagedDouble = true;

	if (DamagedDoubleDuration <= _Duration)
	{
		DamagedDoubleDuration = _Duration;
	}

	if (FindStatusRender("DAMAGEDDOUBLE") == false)
	{
		std::shared_ptr<GameEngineSpriteRenderer> DamagedDoubleRender = CreateComponent<GameEngineSpriteRenderer>();
		DamagedDoubleRender->CreateAnimation({ .AnimationName = "DAMAGEDDOUBLE",.SpriteName = "DamagedDouble",.FrameInter = 0.1f,.Loop = true,.ScaleToTexture = true });
		DamagedDoubleRender->ChangeAnimation("DAMAGEDDOUBLE");

		StatusRenderList["DAMAGEDDOUBLE"] = DamagedDoubleRender;
	}

	std::map<std::string, std::function<bool()>>::iterator Start = StatusEffectList.begin();
	std::map<std::string, std::function<bool()>>::iterator End = StatusEffectList.end();

	for (; Start != End; Start++)
	{
		if (Start->first == "DAMAGEDDOUBLE")
		{
			return;
		}
	}

	StatusEffectList["DAMAGEDDOUBLE"] = [this]
	{
		DamagedDoubleDuration -= TimeCount;

		if (DamagedDoubleDuration < 0)
		{
			isDamagedDouble = false;
			return true;
		}

		return false;
	};
}

void Player::CannotJump(float _Duration)
{
	isCannotJump = true;

	if (CannotJumpDuration <= _Duration)
	{
		CannotJumpDuration = _Duration;
	}

	if (FindStatusRender("CANNOTJUMP") == false)
	{
		std::shared_ptr<GameEngineSpriteRenderer> CannotJumpRender = CreateComponent<GameEngineSpriteRenderer>();
		CannotJumpRender->CreateAnimation({ .AnimationName = "CANNOTJUMP",.SpriteName = "CannotJump",.FrameInter = 0.1f,.Loop = true,.ScaleToTexture = true });
		CannotJumpRender->ChangeAnimation("CANNOTJUMP");

		StatusRenderList["CANNOTJUMP"] = CannotJumpRender;
	}

	std::map<std::string, std::function<bool()>>::iterator Start = StatusEffectList.begin();
	std::map<std::string, std::function<bool()>>::iterator End = StatusEffectList.end();

	for (; Start != End; Start++)
	{
		if (Start->first == "CANNOTJUMP")
		{
			return;
		}
	}

	StatusEffectList["CANNOTJUMP"] = [this]
	{
		CannotJumpDuration -= TimeCount;

		if (CannotJumpDuration < 0)
		{
			isCannotJump = false;
			return true;
		}

		return false;
	};
}