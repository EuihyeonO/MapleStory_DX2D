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


void Player::LuckySeven()
{
	if (isSwing == true)
	{
		return;
	}

	int CurMp = PlayerValue::Value.GetMp();

	if (CurMp < 10)
	{
		return;
	}

	PlayerValue::Value.SetMp(CurMp - 10);

	int SwingType = GameEngineRandom::MainRandom.RandomInt(0, 2);

	MoveType = "Swing" + std::to_string(SwingType);
	AniIndex = 0;
	isSwing = true;

	std::vector<std::shared_ptr<GameEngineCollision>> HitMonsterVector;
	RangeCheck->CollisionAll(static_cast<int>(CollisionOrder::Monster), HitMonsterVector, ColType::AABBBOX2D, ColType::AABBBOX2D);
	float4 PlayerPos = GetTransform()->GetWorldPosition();

	std::function<void(Star&, float)> UpdateFunction = &Star::Move;

	std::shared_ptr<SkillActor> NewSkillActor = GetLevel()->CreateActor<SkillActor>(RenderOrder::Skill);
	NewSkillActor->SetSkillActor("LuckySeven");
		
	std::shared_ptr<Star> NewStar1 = GetLevel()->CreateActor<Star>(static_cast<int>(RenderOrder::Weapon));
	NewStar1->SetStarName("shuriken");
	NewStar1->SetTimingTime(0.25f);
	NewStar1->SetUpdateFuction(UpdateFunction);
	NewStar1->SetTargetMonster(HitMonsterVector, PlayerPos);
	NewStar1->SetType("LuckySeven");

	std::shared_ptr<Star> NewStar2 = GetLevel()->CreateActor<Star>(static_cast<int>(RenderOrder::Weapon));
	NewStar2->SetStarName("shuriken");
	NewStar2->SetTimingTime(0.40f);
	NewStar2->SetUpdateFuction(UpdateFunction);
	NewStar2->SetTargetMonster(HitMonsterVector, PlayerPos);
	NewStar2->SetType("LuckySeven");

	if (isOnShadow == true)
	{
		std::shared_ptr<Star> NewStar1 = GetLevel()->CreateActor<Star>(static_cast<int>(RenderOrder::Weapon));
		NewStar1->SetStarName("shuriken");
		NewStar1->SetTimingTime(0.55f);
		NewStar1->SetUpdateFuction(UpdateFunction);
		NewStar1->SetTargetMonster(HitMonsterVector, PlayerPos);
		NewStar1->SetType("LuckySeven");

		std::shared_ptr<Star> NewStar2 = GetLevel()->CreateActor<Star>(static_cast<int>(RenderOrder::Weapon));
		NewStar2->SetStarName("shuriken");
		NewStar2->SetTimingTime(0.7f);
		NewStar2->SetUpdateFuction(UpdateFunction);
		NewStar2->SetTargetMonster(HitMonsterVector, PlayerPos);
		NewStar2->SetType("LuckySeven");
	}

}

void Player::Avenger()
{
	if (isSwing == true)
	{
		return;
	}

	int CurMp = PlayerValue::Value.GetMp();

	if (CurMp < 10)
	{
		return;
	}

	PlayerValue::Value.SetMp(CurMp - 10);

	std::shared_ptr<SkillActor> NewSkillActor = GetLevel()->CreateActor<SkillActor>(RenderOrder::Skill);
	NewSkillActor->SetSkillActor("Avenger");
	isSwing = true;
	isAvenger = true;

	MoveType = "Swing2";
	AniIndex = 0;

}