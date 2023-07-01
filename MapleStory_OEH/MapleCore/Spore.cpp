#include "PrecompileHeader.h"
#include "Spore.h"
#include "MonsterSpawnZone.h"
#include "ContentRenderer.h"
#include "DropItem.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>

Spore::Spore()
{
	MyName = static_cast<int>(MonsterName::Spore);
}

Spore::~Spore()
{
}

void Spore::Start()
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

void Spore::Update(float _DeltaTime)
{
	TimeCounting();
	StatusUpdate(_DeltaTime);

	float4 Scale = BasicRender->GetTransform()->GetLocalScale();
	BasicRender->GetTransform()->SetLocalPosition({ 0, Scale.hy(), 0 });
	BasicCollision->GetTransform()->SetLocalPosition({ 0, Scale.hy(), 0 });
}

void Spore::Render(float _DeltaTime)
{
}

void Spore::Spawn(float _DeltaTime)
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


void Spore::Hit(int _Damage, bool _isRealAttack)
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

void Spore::MonsterDeath(float _DeltaTime)
{
	if (BasicRender->GetCurrentFrame() < 3)
	{
		return;
	}

	BasicRender->ColorOptionValue.MulColor.a -= 1.0f * _DeltaTime;

	if (BasicRender->ColorOptionValue.MulColor.a <= 0.0f)
	{
		Death();
	}
}

void Spore::SetAnimation()
{
	BasicRender->CreateAnimation({ .AnimationName = "MOVE",.SpriteName = "SporeMove",.FrameInter = 0.18f ,.Loop = true,.ScaleToTexture = true });
	BasicRender->CreateAnimation({ .AnimationName = "STAND",.SpriteName = "SporeStand",.Loop = true,.ScaleToTexture = true,.FrameTime = {0.18f, 0.1f, 0.18f}});
	BasicRender->CreateAnimation({ .AnimationName = "HIT",.SpriteName = "SporeHit",.FrameInter = 0.6f ,.Loop = false,.ScaleToTexture = true });
	BasicRender->CreateAnimation({ .AnimationName = "DEATH",.SpriteName = "SporeDeath",.Loop = false,.ScaleToTexture = true,.FrameTime = {0.12f, 0.12f, 0.12f, 0.12f, 0.12f, 0.12f, 0.12f, 0.12f, 0.3f} });

	BasicRender->SetAnimationUpdateEvent("HIT", 0, [this] {if (BasicRender->IsAnimationEnd() == true) { DirUpdate(); }});
}

void Spore::SetDropItemList()
{
	DropItemList.reserve(4);

	DropItemList.push_back({ "MushRoomSpore", 75 });
	DropItemList.push_back({ "MushRoomSpore", 75 });
	DropItemList.push_back({ "MushRoomSpore", 75 });
	DropItemList.push_back({ "MushRoomSpore", 75 });
}