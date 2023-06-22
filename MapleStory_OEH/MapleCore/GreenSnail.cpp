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
	//TimeCounting();
	//SetAnimationList();

	//SetMoveSpeed(20.0f);

	//BasicRender = CreateComponent<ContentRenderer>();
	//BasicRender->SetScaleToTexture("GreenSnailStand0.png");
	//BasicRender->SetMulColor({ 1, 1, 1, 0.0f });
	//
	//TransformData RenderData = BasicRender->GetTransform()->GetTransDataRef();
	//BasicRender->GetTransform()->SetLocalPosition({ 0, RenderData.LocalScale.hy() });

	//BasicCollision = CreateComponent<GameEngineCollision>();
	//BasicCollision->GetTransform()->SetLocalScale({ abs(RenderData.LocalScale.x), abs(RenderData.LocalScale.y) });
	//BasicCollision->GetTransform()->SetLocalPosition(RenderData.LocalPosition);
	//BasicCollision->SetOrder(static_cast<int>(CollisionOrder::Monster));
	//BasicCollision->Off();

	//SetDropItemList();

}

void GreenSnail::Update(float _DeltaTime)
{
	//TransformData Data = GetTransform()->GetTransDataRef();

	//TimeCounting();
	//Spawn(_DeltaTime);

	//GravityUpdate(_DeltaTime);

	//if(isSpawnAnimationEnd == true && isDeathStart == false)
	//{
	//	if(MoveType != "Hit" && MoveType != "Death")
	//	{
	//		DirUpdate();
	//		Move(_DeltaTime);
	//	}

	//	TextureUpdate();
	//}

	//MonsterDeath(_DeltaTime);
}

void GreenSnail::Render(float _DeltaTime)
{
}

void GreenSnail::Spawn(float _DeltaTime)
{
	//if (isSpawnAnimationEnd == true || IsGround() == false)
	//{
	//	return;
	//}

	//RenderAlpha += 2.5f * _DeltaTime;

	//if (RenderAlpha >= 1.0f)
	//{
	//	RenderAlpha = 1.0f;
	//	isSpawnAnimationEnd = true;
	//	BasicCollision->On();
	//}

	//BasicRender->SetMulColor({ 1,1,1, RenderAlpha });
}


void GreenSnail::TextureUpdate()
{
	//AnimationCount += TimeCount;

	//if (AnimationCount >= FrameList[MoveType][AniIndex])
	//{
	//	AnimationCount = 0.0f;

	//	AniIndex++;

	//	if (AniIndex >= FrameList[MoveType].size())
	//	{
	//		if (MoveType == "Hit")
	//		{
	//			MoveType = "Move";
	//		}

	//		AniIndex = 0;
	//	}
	//	
	//	std::string TextureName = "GreenSnail" + MoveType + std::to_string(AniIndex) + ".png";
	//	BasicRender->SetScaleToTexture(TextureName);

	//	TransformData RenderData = BasicRender->GetTransform()->GetTransDataRef();
	//	BasicRender->GetTransform()->SetLocalPosition({ 0, RenderData.LocalScale.hy() });

	//	BasicCollision->GetTransform()->SetLocalScale({ abs(RenderData.LocalScale.x), abs(RenderData.LocalScale.y) });
	//	BasicCollision->GetTransform()->SetLocalPosition(RenderData.LocalPosition);
	//}
}

void GreenSnail::Hit(int _Damage, bool _isRealAttack)
{
	//MoveType = "Hit";
	//AniIndex = 0;

	//std::string TextureName = "GreenSnail" + MoveType + std::to_string(AniIndex) + ".png";
	//BasicRender->SetScaleToTexture(TextureName);

	//TransformData RenderData = BasicRender->GetTransform()->GetTransDataRef();
	//BasicRender->GetTransform()->SetLocalPosition({ 0, RenderData.LocalScale.hy() });

	//BasicCollision->GetTransform()->SetLocalScale({ abs(RenderData.LocalScale.x), abs(RenderData.LocalScale.y) });
	//BasicCollision->GetTransform()->SetLocalPosition(RenderData.LocalPosition);
	//
	//if(_isRealAttack == true)
	//{
	//	Hp -= _Damage;
	//}

	//if (Hp <= 0)
	//{
	//	MoveType = "Death";
	//	AniIndex = 0;
	//	BasicCollision->Off();

	//	size_t Size = DropItemList.size();
	//	std::vector<int> ItemVector;
	//	ItemVector.reserve(Size);

	//	for (size_t i = 0; i < Size; i++)
	//	{
	//		int Num = GameEngineRandom::MainRandom.RandomInt(0, 99);

	//		if (Num < DropItemList[i].second)
	//		{
	//			ItemVector.push_back(static_cast<int>(i));
	//		}
	//	}

	//	size_t DropItemSize = ItemVector.size();

	//	for (size_t i = 0; i < DropItemSize; i++)
	//	{
	//		std::shared_ptr<DropItem> NewItem = GetLevel()->CreateActor<DropItem>();
	//		NewItem->SetQuadraticFunction((DropItemSize / -2.0f) * 15.0f + (15.0f * i) + 7.5f, GetTransform()->GetWorldPosition() + float4{ 0, 5.0f });
	//		NewItem->SetDropItemInfo(DropItemList[ItemVector[i]].first);
	//	}

	//	isDeathStart = true;
	//}
}

void GreenSnail::MonsterDeath(float _DeltaTime)
{
	//if (isDeathStart == false)
	//{
	//	return;
	//}

	//if (AniIndex < 8)
	//{
	//	TextureUpdate();
	//	return;
	//}

	//float Alpha = BasicRender->ColorOptionValue.MulColor.a;

	//if (Alpha <= 0)
	//{	
	//	GetMyZone()->NumOfMonsterDown(static_cast<int>(MonsterName::GreenSnail));
	//	Death();
	//}

	//BasicRender->SetMulColor({ 1.0f, 1.0f, 1.0f, Alpha - (5.0f * _DeltaTime) });
}

void GreenSnail::SetAnimationList()
{
	//{
	//	FrameList["Stand"].push_back(0.0f);
	//}

	//{
	//	FrameList["Move"].reserve(8);

	//	FrameList["Move"].push_back(0.18f);
	//	FrameList["Move"].push_back(0.18f);
	//	FrameList["Move"].push_back(0.18f);
	//	FrameList["Move"].push_back(0.18f);
	//	FrameList["Move"].push_back(0.18f);
	//	FrameList["Move"].push_back(0.18f);
	//	FrameList["Move"].push_back(0.18f);
	//	FrameList["Move"].push_back(0.18f);
	//}

	//{
	//	FrameList["Hit"].push_back(0.6f);
	//}

	//{
	//	FrameList["Death"].push_back(0.09f);
	//	FrameList["Death"].push_back(0.09f);
	//	FrameList["Death"].push_back(0.09f);
	//	FrameList["Death"].push_back(0.09f);
	//	FrameList["Death"].push_back(0.09f);
	//	FrameList["Death"].push_back(0.09f);
	//	FrameList["Death"].push_back(0.09f);
	//	FrameList["Death"].push_back(0.09f);
	//	FrameList["Death"].push_back(0.09f);
	//}
}

void GreenSnail::SetDropItemList()
{
	//DropItemList.reserve(4);

	//DropItemList.push_back({ "GreenShell", 75 });
	//DropItemList.push_back({ "GreenShell", 75 });
	//DropItemList.push_back({ "GreenShell", 75 });
	//DropItemList.push_back({ "GreenShell", 75 });
}