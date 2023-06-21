#include "PrecompileHeader.h"
#include "Boogie.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>

Boogie::Boogie()
{
}

Boogie::~Boogie()
{
}

void Boogie::Start()
{

	BasicRender = CreateComponent<GameEngineSpriteRenderer>();

	SetAnimation();

	BasicRender->ChangeAnimation("MOVE");
	BasicRender->ColorOptionValue.MulColor.a = 0.0f;

	MoveType = "SPAWN";
	
	BasicCollision = CreateComponent<GameEngineCollision>();
	BasicCollision->GetTransform()->SetLocalScale({ 20, 60 });
	BasicCollision->SetColType(ColType::AABBBOX2D);
	BasicCollision->SetOrder(static_cast<int>(CollisionOrder::Monster));

	GetTransform()->SetLocalPosition({ 0, 0, -6.0f });
	SetMoveSpeed(75.0f);


	if (GameEngineRandom::MainRandom.RandomInt(0, 1) == 1)
	{
		SetRight();
	}
}

void Boogie::Update(float _DeltaTime) 
{
	TimeCounting();
	StatusUpdate(_DeltaTime);

	float4 Scale = BasicRender->GetTransform()->GetLocalScale();
	BasicRender->GetTransform()->SetLocalPosition({ 0, Scale.hy(), 0 });
	BasicCollision->GetTransform()->SetLocalPosition({ 0, Scale.hy(), 0 });
}

void Boogie::Render(float _DeltaTime) 
{

}

void Boogie::Spawn(float _DeltaTime) 
{
	GravityUpdate(_DeltaTime);

	if (IsGround() == true)
	{
		BasicRender->ColorOptionValue.MulColor.a += 1.0f * _DeltaTime;

		if (BasicRender->ColorOptionValue.MulColor.a >= 1.0f)
		{
			BasicRender->ColorOptionValue.MulColor.a = 1.0f;
			BasicRender->ChangeAnimation("MOVE");
			MoveType = "MOVE";
		}
	}
}

void Boogie::MonsterDeath(float _DeltaTime) 
{
	BasicRender->ColorOptionValue.MulColor.a -= 1.0f * _DeltaTime;

	if (BasicRender->ColorOptionValue.MulColor.a <= 0.0f)
	{
		Death();
	}
}

void Boogie::Hit(int _Damage, bool _isRealAttack) 
{
	if (_isRealAttack == true)
	{
		Hp -= _Damage;
	}

	if (Hp <= 0)
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

void Boogie::SetAnimation()
{
	BasicRender->CreateAnimation({ .AnimationName = "MOVE",.SpriteName = "BoogieMove",.FrameInter = 0.11f ,.Loop = true,.ScaleToTexture = true });
	BasicRender->CreateAnimation({ .AnimationName = "STAND",.SpriteName = "BoogieStand",.FrameInter = 0.11f ,.Loop = true,.ScaleToTexture = true });
	BasicRender->CreateAnimation({ .AnimationName = "HIT",.SpriteName = "BoogieHit",.FrameInter = 0.6f ,.Loop = false,.ScaleToTexture = true });
	BasicRender->CreateAnimation({ .AnimationName = "DEATH",.SpriteName = "BoogieDeath",.Loop = false,.ScaleToTexture = true,.FrameTime = {0.12f, 0.12f, 0.12f, 0.12f, 0.3f} });
	
	BasicRender->SetAnimationUpdateEvent("HIT", 0, [this] {if (BasicRender->IsAnimationEnd() == true) { DirUpdate(); }});
}

