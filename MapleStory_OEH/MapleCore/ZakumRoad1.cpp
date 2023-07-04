#include "PrecompileHeader.h"
#include "ZakumRoad1.h"
#include "MiniMap.h"
#include "RingPortal.h"
#include "Player.h"
#include "Aura.h"

#include <GameEngineCore/GameEngineLevel.h>

ZakumRoad1::ZakumRoad1()
{
}

ZakumRoad1::~ZakumRoad1()
{
}

void ZakumRoad1::Start()
{
	BackGround = CreateComponent<GameEngineSpriteRenderer>();
	BackGround->SetScaleToTexture("ZakumRoad1BackGround.png");

	Tile = CreateComponent<GameEngineSpriteRenderer>();
	Tile->SetScaleToTexture("ZakumRoad1.png");

	MyMiniMap = GetLevel()->CreateActor<MiniMap>(static_cast<int>(RenderOrder::UI));
	MyMiniMap->SetMap(MapName);
	MyMiniMap->GetMap()->GetTransform()->AddLocalPosition({ 0, 28 });

	std::shared_ptr<GameEngineCollision> Rope1 = CreateComponent<GameEngineCollision>();
	Rope1->SetColType(ColType::AABBBOX2D);
	Rope1->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));
	Rope1->GetTransform()->SetLocalPosition({ -52.0f, -120.0f });
	Rope1->GetTransform()->SetLocalScale({ 20.0f, 264.0f });

	std::shared_ptr<GameEngineCollision> Rope2 = CreateComponent<GameEngineCollision>();
	Rope2->SetColType(ColType::AABBBOX2D);
	Rope2->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));
	Rope2->GetTransform()->SetLocalPosition({ -392.0f, -470.0f });
	Rope2->GetTransform()->SetLocalScale({ 20.0f, 264.0f });

	std::shared_ptr<GameEngineCollision> Rope3 = CreateComponent<GameEngineCollision>();
	Rope3->SetColType(ColType::AABBBOX2D);
	Rope3->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));
	Rope3->GetTransform()->SetLocalPosition({ 302.0f, -580.0f });
	Rope3->GetTransform()->SetLocalScale({ 20.0f, 354.0f });

	std::shared_ptr<GameEngineCollision> Rope4 = CreateComponent<GameEngineCollision>();
	Rope4->SetColType(ColType::AABBBOX2D);
	Rope4->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));
	Rope4->GetTransform()->SetLocalPosition({ -503.0f, 0.0f });
	Rope4->GetTransform()->SetLocalScale({ 20.0f, 274.0f });

	std::shared_ptr<GameEngineCollision> Rope5 = CreateComponent<GameEngineCollision>();
	Rope5->SetColType(ColType::AABBBOX2D);
	Rope5->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));
	Rope5->GetTransform()->SetLocalPosition({ -494.0f, 318.0f });
	Rope5->GetTransform()->SetLocalScale({ 20.0f, 244.0f });

	std::shared_ptr<GameEngineCollision> Rope6 = CreateComponent<GameEngineCollision>();
	Rope6->SetColType(ColType::AABBBOX2D);
	Rope6->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));
	Rope6->GetTransform()->SetLocalPosition({ -410.0f, 122.0f });
	Rope6->GetTransform()->SetLocalScale({ 20.0f, 144.0f });

	Port1 = GetLevel()->CreateActor<RingPortal>();
	Port1->SetPortalPos({ 540, -890, -10.0f});
	Port1->SetLinkedPos({ -700, 500 });
	
	Port2 = GetLevel()->CreateActor<RingPortal>();
	Port2->SetPortalPos({ -700, 490, -10.0f });
	Port2->SetLinkedPos({ 540, -800 });

	MyAura = GetLevel()->CreateActor<Aura>();
	MyAura->GetTransform()->SetWorldPosition({ -550, 470 });
}

void ZakumRoad1::Update(float _DeltaTime) 
{

}

void ZakumRoad1::Render(float _DeltaTime) 
{

}


void ZakumRoad1::ActorDeath()
{
	if (Port1 != nullptr)
	{
		Port1->Death();
		Port1 = nullptr;
	}

	if (Port2 != nullptr)
	{
		Port2->Death();
		Port2 = nullptr;
	}

	if (MyAura != nullptr)
	{
		MyAura->Death();
		MyAura = nullptr;
	}
}