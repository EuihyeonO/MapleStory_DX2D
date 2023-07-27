#include "PrecompileHeader.h"
#include "GreenSnail.h"
#include "MonsterSpawnZone.h"
#include "ContentRenderer.h"
#include "DropItem.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>

GreenSnail::GreenSnail()
{
	MyName = static_cast<int>(MonsterName::GreenSnail);
}

GreenSnail::~GreenSnail()
{
}

void GreenSnail::Start()
{
	TimeCounting();


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
	SetMoveSpeed(20.0f);


	if (GameEngineRandom::MainRandom.RandomInt(0, 1) == 1)
	{
		SetRight();
	}

	SetDropItemList();
}

void GreenSnail::Update(float _DeltaTime)
{
	TimeCounting();
	StatusUpdate(_DeltaTime);

	float4 Scale = BasicRender->GetTransform()->GetLocalScale();
	BasicRender->GetTransform()->SetLocalPosition({ 0, Scale.hy(), 0 });
	BasicCollision->GetTransform()->SetLocalPosition({ 0, Scale.hy(), 0 });
}

void GreenSnail::Render(float _DeltaTime)
{
}

void GreenSnail::Spawn(float _DeltaTime)
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


void GreenSnail::Hit(int _Damage, bool _isRealAttack)
{
	BasicRender->ChangeAnimation("HIT");

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

		size_t Size = DropItemList.size();
		std::vector<int> ItemVector;
		ItemVector.reserve(Size);

		for (size_t i = 0; i < Size; i++)
		{
			int Num = GameEngineRandom::MainRandom.RandomInt(0, 99);

			if (Num < DropItemList[i].second)
			{
				ItemVector.push_back(static_cast<int>(i));
			}
		}

		size_t DropItemSize = ItemVector.size();

		for (size_t i = 0; i < DropItemSize; i++)
		{
			std::shared_ptr<DropItem> NewItem = GetLevel()->CreateActor<DropItem>();
			NewItem->SetQuadraticFunction((DropItemSize / -2.0f) * 15.0f + (15.0f * i) + 7.5f, GetTransform()->GetWorldPosition() + float4{ 0, 5.0f });
			NewItem->SetDropItemInfo(DropItemList[ItemVector[i]].first, static_cast<int>(ItemType::Etc));
		}

		return;
	}
}

void GreenSnail::MonsterDeath(float _DeltaTime)
{
	if (BasicRender->GetCurrentFrame() < 8)
	{
		return;
	}

	BasicRender->ColorOptionValue.MulColor.a -= 1.0f * _DeltaTime;

	if (BasicRender->ColorOptionValue.MulColor.a <= 0.0f)
	{
		Death();
	}
}

void GreenSnail::SetAnimation()
{
	BasicRender->CreateAnimation({ .AnimationName = "MOVE",.SpriteName = "GreenSnailMove",.FrameInter = 0.18f ,.Loop = true,.ScaleToTexture = true });
	BasicRender->CreateAnimation({ .AnimationName = "STAND",.SpriteName = "GreenSnailStand",.FrameInter = 1.0f ,.Loop = true,.ScaleToTexture = true });
	BasicRender->CreateAnimation({ .AnimationName = "HIT",.SpriteName = "GreenSnailHit",.FrameInter = 0.6f ,.Loop = false,.ScaleToTexture = true });
	BasicRender->CreateAnimation({ .AnimationName = "DEATH",.SpriteName = "GreenSnailDeath",.Loop = false,.ScaleToTexture = true,.FrameTime = {0.12f, 0.12f, 0.12f, 0.12f, 0.12f, 0.12f, 0.12f, 0.12f, 0.3f} });

	BasicRender->SetAnimationUpdateEvent("HIT", 0, [this] {if (BasicRender->IsAnimationEnd() == true) { DirUpdate(); }});
}

void GreenSnail::SetDropItemList()
{
	DropItemList.reserve(4);

	DropItemList.push_back({ "GreenShell", 75 });
	DropItemList.push_back({ "GreenShell", 75 });
	DropItemList.push_back({ "GreenShell", 75 });
	DropItemList.push_back({ "GreenShell", 75 });
}