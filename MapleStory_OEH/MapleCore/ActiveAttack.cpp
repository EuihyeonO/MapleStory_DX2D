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
#include <GameEnginePlatform/GameEngineSound.h>
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
	NewStar1->Set_IsRealAttack(false);

	std::shared_ptr<Star> NewStar2 = GetLevel()->CreateActor<Star>(static_cast<int>(RenderOrder::Weapon));
	NewStar2->SetStarName("shuriken");
	NewStar2->SetTimingTime(0.40f);
	NewStar2->SetUpdateFuction(UpdateFunction);
	NewStar2->SetTargetMonster(HitMonsterVector, PlayerPos);
	NewStar2->SetType("LuckySeven");

	if (isOnShadow == true)
	{
		NewStar2->Set_IsRealAttack(false);

		std::shared_ptr<Star> NewStar3 = GetLevel()->CreateActor<Star>(static_cast<int>(RenderOrder::Weapon));
		NewStar3->SetStarName("shuriken");
		NewStar3->SetTimingTime(0.55f);
		NewStar3->SetUpdateFuction(UpdateFunction);
		NewStar3->SetTargetMonster(HitMonsterVector, PlayerPos);
		NewStar3->SetType("LuckySeven");
		NewStar3->Set_IsRealAttack(false);

		std::shared_ptr<Star> NewStar4 = GetLevel()->CreateActor<Star>(static_cast<int>(RenderOrder::Weapon));
		NewStar4->SetStarName("shuriken");
		NewStar4->SetTimingTime(0.7f);
		NewStar4->SetUpdateFuction(UpdateFunction);
		NewStar4->SetTargetMonster(HitMonsterVector, PlayerPos);
		NewStar4->SetType("LuckySeven");
	}
}

void Player::TripleThrow()
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
	NewSkillActor->SetSkillActor("TripleThrow");

	std::shared_ptr<Star> NewStar0 = GetLevel()->CreateActor<Star>(static_cast<int>(RenderOrder::Weapon));
	NewStar0->SetStarName("shuriken");
	NewStar0->SetTimingTime(0.25f);
	NewStar0->SetUpdateFuction(UpdateFunction);
	NewStar0->SetTargetMonster(HitMonsterVector, PlayerPos);
	NewStar0->SetType("TripleThrow");
	NewStar0->Set_IsRealAttack(false);
	NewStar0->SetStarIndex(0);

	std::shared_ptr<Star> NewStar1 = GetLevel()->CreateActor<Star>(static_cast<int>(RenderOrder::Weapon));
	NewStar1->SetStarName("shuriken");
	NewStar1->SetTimingTime(0.325f);
	NewStar1->SetUpdateFuction(UpdateFunction);
	NewStar1->SetTargetMonster(HitMonsterVector, PlayerPos);
	NewStar1->SetType("TripleThrow");
	NewStar1->Set_IsRealAttack(false);
	NewStar1->SetStarIndex(1);

	std::shared_ptr<Star> NewStar2 = GetLevel()->CreateActor<Star>(static_cast<int>(RenderOrder::Weapon));
	NewStar2->SetStarName("shuriken");
	NewStar2->SetTimingTime(0.40f);
	NewStar2->SetUpdateFuction(UpdateFunction);
	NewStar2->SetTargetMonster(HitMonsterVector, PlayerPos);
	NewStar2->SetType("TripleThrow");
	NewStar2->SetStarIndex(2);

	if (isOnShadow == true)
	{
		NewStar2->Set_IsRealAttack(false);

		std::shared_ptr<Star> NewStar3 = GetLevel()->CreateActor<Star>(static_cast<int>(RenderOrder::Weapon));
		NewStar3->SetStarName("shuriken");
		NewStar3->SetTimingTime(0.475f);
		NewStar3->SetUpdateFuction(UpdateFunction);
		NewStar3->SetTargetMonster(HitMonsterVector, PlayerPos);
		NewStar3->SetType("TripleThrow");
		NewStar3->Set_IsRealAttack(false);
		NewStar3->SetStarIndex(3);

		std::shared_ptr<Star> NewStar4 = GetLevel()->CreateActor<Star>(static_cast<int>(RenderOrder::Weapon));
		NewStar4->SetStarName("shuriken");
		NewStar4->SetTimingTime(0.55f);
		NewStar4->SetUpdateFuction(UpdateFunction);
		NewStar4->SetTargetMonster(HitMonsterVector, PlayerPos);
		NewStar4->SetType("TripleThrow");
		NewStar4->Set_IsRealAttack(false);
		NewStar4->SetStarIndex(4);

		std::shared_ptr<Star> NewStar5 = GetLevel()->CreateActor<Star>(static_cast<int>(RenderOrder::Weapon));
		NewStar5->SetStarName("shuriken");
		NewStar5->SetTimingTime(0.625f);
		NewStar5->SetUpdateFuction(UpdateFunction);
		NewStar5->SetTargetMonster(HitMonsterVector, PlayerPos);
		NewStar5->SetType("TripleThrow");
		NewStar5->SetStarIndex(5);
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

	GameEngineSound::Play("Avenger.mp3");
	
	PlayerValue::Value.SetMp(CurMp - 10);

	std::shared_ptr<SkillActor> NewSkillActor = GetLevel()->CreateActor<SkillActor>(RenderOrder::Skill);
	NewSkillActor->SetSkillActor("Avenger");
	isSwing = true;
	isAvenger = true;

	MoveType = "Swing2";
	AniIndex = 0;
}

void Player::FlashJump()
{
	if (isKeyJump == false || isSwing == true || isFlashJump == true)
	{
		return;
	}

	int CurMp = PlayerValue::Value.GetMp();

	if (CurMp < 10)
	{
		return;
	}

	GameEngineSound::Play("FlashJump.mp3");

	//PlayerValue::Value.SetMp(CurMp - 10);
	std::shared_ptr<SkillActor> FlashJumpActor = GetLevel()->CreateActor<SkillActor>();
	FlashJumpActor->SetSkillActor("FlashJump");

	if (LeftRightDir == "Left")
	{
		JumpXMove = -400.0f;
	}
	else if (LeftRightDir == "Right")
	{
		JumpXMove = 400.0f;
	}

	isFlashJump = true;
}