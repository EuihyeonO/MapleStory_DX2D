#include "PrecompileHeader.h"
#include "CrossRoad.h"
#include "ContentRenderer.h"
#include "Portal.h"
#include "MonsterSpawnZone.h"
#include "MiniMap.h"

#include <GameEngineCore/GameEngineLevel.h>

CrossRoad::CrossRoad()
{
}

CrossRoad::~CrossRoad()
{
}

void CrossRoad::Start()
{
	BasicBackGround = CreateComponent<ContentRenderer>();
	BasicBackGround->SetTexture("MapBackGround6.png");
	BasicBackGround->GetTransform()->SetLocalScale({ 3860, 1200 });

	LandScape0 = CreateComponent<ContentRenderer>();
	LandScape0->SetTexture("MapBackGround5.png");
	LandScape0->GetTransform()->SetLocalScale({ 635 * 6 , 718 });
	LandScape0->GetTransform()->SetLocalPosition({ 0 , 350.0f });
	LandScape0->SetUVconstant({0, 0, 6, 1});
	
	LandScape1 = CreateComponent<ContentRenderer>();
	LandScape1->SetTexture("MapBackGround4.png");
	LandScape1->GetTransform()->SetLocalScale({ 1024 * 3, 438 });
	LandScape1->GetTransform()->SetLocalPosition({ 0 , 250.0f });
	LandScape1->SetUVconstant({ 0, 0, 3, 1 });
	LandScape1->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.75f });

	LandScape2 = CreateComponent<ContentRenderer>();
	LandScape2->SetTexture("MapBackGround3.png");
	LandScape2->GetTransform()->SetLocalScale({ 2049 * 2, 502 });
	LandScape2->GetTransform()->SetLocalPosition({ 0 , 150.0f });
	LandScape2->SetUVconstant({ 0, 0, 2, 1 });

	BackGround = CreateComponent<GameEngineSpriteRenderer>();
	BackGround->SetScaleToTexture("CrossRoad.png");

	MyMiniMap = GetLevel()->CreateActor<MiniMap>(static_cast<int>(RenderOrder::UI));
	MyMiniMap->SetMap(MapName);
	MyMiniMap->SetPortalToMiniMap({ -1750, 45, -10 });
	MyMiniMap->SetPortalToMiniMap({ 1760, -70, -10 });
	MyMiniMap->SetMapMark("MushroomVillageMark.png");
	MyMiniMap->SetWorldName("메이플월드");
	MyMiniMap->SetMapName("두 갈래 길");

	Portal1 = GetLevel()->CreateActor<Portal>(static_cast<int>(RenderOrder::UI));
	Portal1->SetLinkedMap("Level_BeginnersTown2");
	Portal1->SetPortalPos({ -1750, 45, -10 });

	Portal2 = GetLevel()->CreateActor<Portal>(static_cast<int>(RenderOrder::UI));
	Portal2->SetLinkedMap("Level_SouthFerry");
	Portal2->SetPortalPos({ 1760, -70, -10 });

	std::shared_ptr<GameEngineCollision> Rope1 = CreateComponent<GameEngineCollision>();
	Rope1->SetColType(ColType::AABBBOX2D);
	Rope1->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));
	Rope1->GetTransform()->SetLocalPosition({ 92.0f, -70.0f });
	Rope1->GetTransform()->SetLocalScale({ 20.0f, 240.0f });

	std::shared_ptr<GameEngineCollision> Rope2 = CreateComponent<GameEngineCollision>();
	Rope2->SetColType(ColType::AABBBOX2D);
	Rope2->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));
	Rope2->GetTransform()->SetLocalPosition({ 198.0f, 144.0f });
	Rope2->GetTransform()->SetLocalScale({ 20.0f, 180.0f });

	std::shared_ptr<GameEngineCollision> Rope3 = CreateComponent<GameEngineCollision>();
	Rope3->SetColType(ColType::AABBBOX2D);
	Rope3->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));
	Rope3->GetTransform()->SetLocalPosition({ 706.0f, 170.0f });
	Rope3->GetTransform()->SetLocalScale({ 20.0f, 240.0f });

	std::shared_ptr<GameEngineCollision> Rope4 = CreateComponent<GameEngineCollision>();
	Rope4->SetColType(ColType::AABBBOX2D);
	Rope4->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));
	Rope4->GetTransform()->SetLocalPosition({ 1453.0f, 122.0f });
	Rope4->GetTransform()->SetLocalScale({ 20.0f, 100.0f });

	std::shared_ptr<GameEngineCollision> Rope5 = CreateComponent<GameEngineCollision>();
	Rope5->SetColType(ColType::AABBBOX2D);
	Rope5->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));
	Rope5->GetTransform()->SetLocalPosition({ 1360.0f, -38.0f });
	Rope5->GetTransform()->SetLocalScale({ 20.0f, 180.0f });
	
	std::shared_ptr<GameEngineCollision> Rope6 = CreateComponent<GameEngineCollision>();
	Rope6->SetColType(ColType::AABBBOX2D);
	Rope6->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));
	Rope6->GetTransform()->SetLocalPosition({ -803.0f, -60.0f });
	Rope6->GetTransform()->SetLocalScale({ 20.0f, 220.0f });
	
	std::shared_ptr<GameEngineCollision> Radder1 = CreateComponent<GameEngineCollision>();
	Radder1->SetColType(ColType::AABBBOX2D);
	Radder1->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));
	Radder1->GetTransform()->SetLocalPosition({ -1226.0f, 30.0f });
	Radder1->GetTransform()->SetLocalScale({ 40.0f, 160.0f });

	std::shared_ptr<GameEngineCollision> Radder2 = CreateComponent<GameEngineCollision>();
	Radder2->SetColType(ColType::AABBBOX2D);
	Radder2->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));
	Radder2->GetTransform()->SetLocalPosition({ 790.0f, -75.0f });
	Radder2->GetTransform()->SetLocalScale({ 40.0f, 130.0f });

	Zone1 = GetLevel()->CreateActor<MonsterSpawnZone>();
	Zone1->SetColMap(ColMapName);
	Zone1->SetMonsterToZone(MonsterName::Spore, 5);
	Zone1->SetMonsterToZone(MonsterName::GreenSnail, 5);
	Zone1->SetZonePosAndScale({ 200, -130.0f }, 1000.0f);

	Zone2 = GetLevel()->CreateActor<MonsterSpawnZone>();
	Zone2->SetColMap(ColMapName);
	Zone2->SetMonsterToZone(MonsterName::Spore, 5);
	Zone2->SetMonsterToZone(MonsterName::BlueSnail, 5);
	Zone2->SetZonePosAndScale({ 600, 600.0f }, 1000.0f);

}

void CrossRoad::Update(float _DeltaTime)
{
	LandScapeMove(_DeltaTime);
}

void CrossRoad::Render(float _DeltaTime)
{
}

void CrossRoad::LandScapeMove(float _DeltaTime)
{
	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();
	
	float4 MapScale = GameEngineTexture::Find(MapName)->GetScale();
	float4 CameraPosPerMapScaleRatio = { CameraPos.x / MapScale.x, CameraPos.y / MapScale.y };

	LandScape0->GetTransform()->SetLocalPosition(float4{ (800.0f * CameraPosPerMapScaleRatio.x * 0.5f), (600.0f * CameraPosPerMapScaleRatio.y * 1.5f + 225.0f) });

	LandScape1->GetTransform()->SetLocalPosition(float4{ (800.0f * CameraPosPerMapScaleRatio.x - 100.0f) , (600.0f * CameraPosPerMapScaleRatio.y * 1.5f + 175.0f) });

	LandScape2->GetTransform()->SetLocalPosition(float4{ (800.0f * CameraPosPerMapScaleRatio.x * 1.25f) - 100.0f, (600.0f * CameraPosPerMapScaleRatio.y * 1.5f  + 25.0f) });
}

void CrossRoad::ActorDeath()
{
	if(MyMiniMap != nullptr)
	{
		MyMiniMap->Death();
		MyMiniMap = nullptr;
	}

	if (Portal1 != nullptr)
	{
		Portal1->Death();
		Portal1 = nullptr;
	}

	if (Portal2 != nullptr)
	{
		Portal2->Death();
		Portal2 = nullptr;
	}

	if (Zone1 != nullptr)
	{
		Zone1->AllMonsterDeath();
		Zone1->Death();
		Zone1 = nullptr;
	}

	if (Zone2 != nullptr)
	{
		Zone2->AllMonsterDeath();
		Zone2->Death();
		Zone2 = nullptr;
	}
}