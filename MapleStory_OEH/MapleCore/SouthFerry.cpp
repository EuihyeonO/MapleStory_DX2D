#include "PrecompileHeader.h"
#include "Portal.h"
#include "SouthFerry.h"
#include "Shanks.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>

SouthFerry::SouthFerry()
{
}

SouthFerry::~SouthFerry()
{
}

void SouthFerry::Start()
{
	Map = CreateComponent<GameEngineSpriteRenderer>();
	Map->SetScaleToTexture(MapName);

	BackGround = CreateComponent<GameEngineSpriteRenderer>();
	BackGround->SetScaleToTexture("MapBackGround1.png");

	BackColor = CreateComponent<GameEngineSpriteRenderer>();
	BackColor->SetScaleToTexture("MapBackGround0.png");
	BackColor->GetTransform()->SetLocalScale({ 1000, 1000 });

	std::shared_ptr<GameEngineCollision> Radder1 = CreateComponent<GameEngineCollision>();
	Radder1->SetColType(ColType::AABBBOX2D);
	Radder1->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));
	Radder1->GetTransform()->SetLocalPosition({ -60.0f, -452.0f });
	Radder1->GetTransform()->SetLocalScale({ 40.0f, 340.0f });

	std::shared_ptr<GameEngineCollision> Radder2 = CreateComponent<GameEngineCollision>();
	Radder2->SetColType(ColType::AABBBOX2D);
	Radder2->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));
	Radder2->GetTransform()->SetLocalPosition({ -1304.0f, -283.0f });
	Radder2->GetTransform()->SetLocalScale({ 40.0f, 360.0f });

	std::shared_ptr<GameEngineCollision> Rope1 = CreateComponent<GameEngineCollision>();
	Rope1->SetColType(ColType::AABBBOX2D);
	Rope1->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));
	Rope1->GetTransform()->SetLocalPosition({ -1266.0f, -63.0f });
	Rope1->GetTransform()->SetLocalScale({ 10.0f, 220.0f });

	std::shared_ptr<GameEngineCollision> Rope2 = CreateComponent<GameEngineCollision>();
	Rope2->SetColType(ColType::AABBBOX2D);
	Rope2->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));
	Rope2->GetTransform()->SetLocalPosition({ -1346.0f, -630.0f });
	Rope2->GetTransform()->SetLocalScale({ 10.0f, 220.0f });

	MyShanks = GetLevel()->CreateActor<Shanks>();
	MyShanks->GetTransform()->SetLocalPosition({ 1575, -185 });

	Portal1 = GetLevel()->CreateActor<Portal>();
	Portal1->SetLinkedMap("Level_CrossRoad");
	Portal1->SetPortalPos({ -2250, -400, -10 });

	CloudList.reserve(20);

	for (int i = 0; i < 20; i++)
	{
		int Index = i % 4 + 1;
		float Speed = GameEngineRandom::MainRandom.RandomFloat(25, 100);

		CloudList.push_back({ CreateComponent<GameEngineSpriteRenderer>(), Speed });
		CloudList[i].first->SetScaleToTexture("Cloud" + std::to_string(Index) + ".PNG");

		float Xpos = GameEngineRandom::MainRandom.RandomFloat(-2300, 2300);
		float Ypos = (i / 2 - 5) * 100.0f;

		CloudList[i].first->GetTransform()->SetLocalPosition({ Xpos, Ypos, 1 });
	}
}

void SouthFerry::Update(float _DeltaTime)
{
	BackGroundUpdate(_DeltaTime);
}

void SouthFerry::Render(float _DeltaTime)
{

}

void SouthFerry::BackGroundUpdate(float _DeltaTime)
{
	float4 CamPos = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();
	CamPos.z = 0;

	BackGround->GetTransform()->SetLocalPosition(CamPos + float4{ 0, 0, 2 });
	BackColor->GetTransform()->SetLocalPosition(CamPos + float4{ 0, 0, 3 });

	for (int i = 0; i < 20; i++)
	{
		float Speed = CloudList[i].second;

		CloudList[i].first->GetTransform()->AddLocalPosition(float4{ Speed, 0 } * _DeltaTime);

		if (CloudList[i].first->GetTransform()->GetWorldPosition().x >= 2300)
		{
			float Ypos = (i / 2 - 5) * 100.0f;

			CloudList[i].first->GetTransform()->SetLocalPosition({ -3000, Ypos, 1 });
			CloudList[i].second = GameEngineRandom::MainRandom.RandomFloat(25, 100);
		}
	}
}void SouthFerry::ActorDeath()
{
	if (Portal1 != nullptr)
	{
		Portal1->Death();
	}

	if (MyShanks != nullptr)
	{
		MyShanks->Death();
	}
}