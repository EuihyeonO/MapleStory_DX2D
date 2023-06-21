#include "PrecompileHeader.h"
#include "SmallZakum2.h"
#include "Player.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>

SmallZakum2::SmallZakum2()
{
}

SmallZakum2::~SmallZakum2()
{
}


void SmallZakum2::Start()
{

	BasicRender = CreateComponent<GameEngineSpriteRenderer>();

	SetAnimation();

	BasicRender->ChangeAnimation("FLY");
	BasicRender->ColorOptionValue.MulColor.a = 0.0f;

	MoveType = "SPAWN";

	BasicCollision = CreateComponent<GameEngineCollision>();
	BasicCollision->GetTransform()->SetLocalScale({ 20, 60 });
	BasicCollision->SetColType(ColType::AABBBOX2D);
	BasicCollision->SetOrder(static_cast<int>(CollisionOrder::Monster));

	GetTransform()->SetLocalPosition({ 0, 0, -6.0f });
	SetMoveSpeed(220.0f);

	AttackCollision = CreateComponent<GameEngineCollision>();
	AttackCollision->SetColType(ColType::AABBBOX2D);
	AttackCollision->SetOrder(static_cast<int>(CollisionOrder::Range));
	AttackCollision->GetTransform()->SetLocalScale({ 200, 80 });

	Att = 10;

	if (GameEngineRandom::MainRandom.RandomInt(0, 1) == 1)
	{
		SetRight();
	}
}

void SmallZakum2::Update(float _DeltaTime)
{
	StatusUpdate(_DeltaTime);
	AttackRangeCheck();
}

void SmallZakum2::Render(float _DeltaTime)
{

}

void SmallZakum2::Spawn(float _DeltaTime)
{
	BasicRender->ColorOptionValue.MulColor.a += 1.5f * _DeltaTime;

	if (BasicRender->ColorOptionValue.MulColor.a >= 1.0f)
	{
		BasicRender->ColorOptionValue.MulColor.a = 1.0f;
		MoveType = "FLY";

		SetMoveDir();
	}
}

void SmallZakum2::AttackRangeCheck()
{
	if (isDeathStart == true)
	{
		return;
	}

	if (AttackCollision->Collision(static_cast<int>(CollisionOrder::Player), ColType::AABBBOX2D, ColType::AABBBOX2D) != nullptr)
	{
		AttackCollision->Off();
		MoveType = "ATTACK";

		if (Player::GetCurPlayer()->GetTransform()->GetWorldPosition().x > GetTransform()->GetWorldPosition().x)
		{
			SetRight();
		}
		else
		{
			SetLeft();
		}

		GetLevel()->TimeEvent.AddEvent(3.0f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {AttackCollision->On(); isAttCoolTime = false; });
	}
}

void SmallZakum2::SetAnimation()
{
	BasicRender->CreateAnimation({ .AnimationName = "FLY",.SpriteName = "SmallZakum2Fly",.FrameInter = 0.1f ,.Loop = true,.ScaleToTexture = true });
	BasicRender->CreateAnimation({ .AnimationName = "HIT",.SpriteName = "SmallZakum2Hit",.FrameInter = 0.6f ,.Loop = false,.ScaleToTexture = true });
	BasicRender->CreateAnimation({ .AnimationName = "DEATH",.SpriteName = "SmallZakum2Death",.FrameInter = 0.15f ,.Loop = false,.ScaleToTexture = true });

	BasicRender->SetAnimationUpdateEvent("HIT", 0, [this] {if (BasicRender->IsAnimationEnd() == true) { BasicRender->ChangeAnimation("FLY"); MoveType = "FLY"; }});
}

void SmallZakum2::SetMoveDir()
{
	float Xdir = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
	float Ydir = GameEngineRandom::MainRandom.RandomFloat(-1, 1);

	MoveDir += { Xdir, Ydir };
	MoveDir.Normalize();

	if (MoveDir.x >= 0.0f)
	{
		SetRight();
	}
	else
	{
		SetLeft();
	}

	MaxMoveDistance = GameEngineRandom::MainRandom.RandomFloat(100, 300);
}

void SmallZakum2::Fly(float _DeltaTime)
{
	float Num = GameEngineRandom::MainRandom.RandomFloat(-4, 4);
	MoveDir += {0, Num* _DeltaTime};
	MoveDir.Normalize();


	float4 PrevPos = GetTransform()->GetLocalPosition();
	float4 NextPos = GetTransform()->GetLocalPosition() + MoveDir * MoveSpeed * _DeltaTime;

	std::shared_ptr<GameEngineTexture> ColMap = GetColMap();

	if (ColMap->GetWidth() / 2 - 100 < abs(NextPos.x) || ColMap->GetHeight() / 2 - 220 < NextPos.y || -(ColMap->GetHeight() / 2 - 400) > NextPos.y)
	{
		while (ColMap->GetWidth() / 2 - 100 < abs(NextPos.x) || ColMap->GetHeight() / 2 - 220 < NextPos.y || -(ColMap->GetHeight() / 2 - 400) > NextPos.y)
		{
			SetMoveDir();
			NextPos = GetTransform()->GetLocalPosition() + MoveDir * MoveSpeed * _DeltaTime;
		}

		MoveDistance = 0.0f;
		return;
	}

	GetTransform()->AddLocalPosition(MoveDir * MoveSpeed * _DeltaTime);

	MoveDistance += sqrt((NextPos.x - PrevPos.x) * (NextPos.x - PrevPos.x) + (NextPos.y - PrevPos.y) * (NextPos.y - PrevPos.y));

	if (MoveDistance >= MaxMoveDistance)
	{
		SetMoveDir();
		MoveDistance = 0.0f;
	}
}

void SmallZakum2::Hit(int _Damage, bool _isRealAttack)
{
	Hp -= _Damage;

	if (Hp <= 0 && _isRealAttack == true)
	{
		BasicRender->ChangeAnimation("DEATH");
		MoveType = "DEATH";

		if (LeftRightDir == "Left")
		{
			SetLeft();
		}
		else if (LeftRightDir == "Right")
		{
			SetRight();
		}

		BasicCollision->Off();
		isDeathStart = true;
		return;
	}

	if (isAttack == false)
	{
		BasicRender->ChangeAnimation("HIT");
		MoveType = "HIT";

		if (LeftRightDir == "Left")
		{
			SetLeft();
		}
		else if (LeftRightDir == "Right")
		{
			SetRight();
		}
	}

}

void SmallZakum2::MonsterDeath(float _DeltaTime)
{
	if (BasicRender->IsAnimationEnd() == true)
	{
		BasicRender->ColorOptionValue.MulColor.a = 0.0f;
		GetLevel()->TimeEvent.AddEvent(3.0f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {Death(); });
	}
}


void SmallZakum2::Attack()
{
	if (isAttack == false)
	{
		std::weak_ptr<GameEngineSpriteRenderer> NewEff = CreateComponent<GameEngineSpriteRenderer>();
		NewEff.lock()->CreateAnimation({ .AnimationName = "Attack",.SpriteName = "SmallZakum2Attack",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
		NewEff.lock()->SetAnimationUpdateEvent("Attack", 14, [NewEff, this] {if (NewEff.lock()->IsAnimationEnd() == true) { Player::GetCurPlayer()->Hit(Att); NewEff.lock()->Death(); isAttack = false; MoveType = "FLY"; }});
		NewEff.lock()->ChangeAnimation("Attack");

		if (LeftRightDir == "Right")
		{
			float4 Scale = NewEff.lock()->GetTransform()->GetLocalScale();
			NewEff.lock()->GetTransform()->SetLocalScale({ -Scale.x, Scale.y });
		}

		isAttack = true;
		isAttCoolTime = true;
	}
}