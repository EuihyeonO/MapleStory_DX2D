#include "PrecompileHeader.h"
#include "SmallZakum0.h"

#include <GameEngineBase/GameEngineRandom.h>

SmallZakum0::SmallZakum0()
{
}

SmallZakum0::~SmallZakum0()
{
}


void SmallZakum0::Start()
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


	if (GameEngineRandom::MainRandom.RandomInt(0, 1) == 1)
	{
		SetRight();
	}
}

void SmallZakum0::Update(float _DeltaTime) 
{
	StatusUpdate(_DeltaTime);
}

void SmallZakum0::Render(float _DeltaTime) 
{

}

void SmallZakum0::Spawn(float _DeltaTime) 
{
	BasicRender->ColorOptionValue.MulColor.a += 1.5f * _DeltaTime;

	if (BasicRender->ColorOptionValue.MulColor.a >= 1.0f)
	{
		BasicRender->ColorOptionValue.MulColor.a = 1.0f;
		MoveType = "FLY";

		SetMoveDir();
	}
}

void SmallZakum0::SetAnimation()
{
	BasicRender->CreateAnimation({ .AnimationName = "FLY",.SpriteName = "SmallZakum0Fly",.FrameInter = 0.15f ,.Loop = true,.ScaleToTexture = true });
	BasicRender->CreateAnimation({ .AnimationName = "HIT",.SpriteName = "SmallZakum0Hit",.FrameInter = 0.6f ,.Loop = false,.ScaleToTexture = true });
	BasicRender->CreateAnimation({ .AnimationName = "DEATH",.SpriteName = "SmallZakum0Death",.FrameInter = 0.15f ,.Loop = false,.ScaleToTexture = true });

	BasicRender->SetAnimationUpdateEvent("HIT", 0, [this] {if (BasicRender->IsAnimationEnd() == true) { BasicRender->ChangeAnimation("FLY"); MoveType = "FLY"; }});
}

void SmallZakum0::SetMoveDir()
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

void SmallZakum0::Fly(float _DeltaTime)
{
	float Num = GameEngineRandom::MainRandom.RandomFloat(-4, 4);
	MoveDir += {0, Num * _DeltaTime};
	MoveDir.Normalize();


	float4 PrevPos = GetTransform()->GetLocalPosition();
	float4 NextPos = GetTransform()->GetLocalPosition() + MoveDir * MoveSpeed * _DeltaTime;

	std::shared_ptr<GameEngineTexture> ColMap = GetColMap();

	if (ColMap->GetWidth() / 2 - 100 < abs(NextPos.x) || ColMap->GetHeight() / 2 - 220 < NextPos.y || -(ColMap->GetHeight() / 2 - 400) > NextPos.y)
	{
		SetMoveDir();
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

void SmallZakum0::Hit(int _Damage, bool _isRealAttack)
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

void SmallZakum0::MonsterDeath(float _DeltaTime)
{
	if (BasicRender->IsAnimationEnd() == true)
	{
		Death();
	}
}
