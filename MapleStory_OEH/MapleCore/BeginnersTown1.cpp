#include "PrecompileHeader.h"
#include "BeginnersTown1.h"
#include "MiniMap.h"
#include "Hina.h"
#include "ContentEnums.h"
#include "ContentRenderer.h"
#include "GreenSnail.h"
#include "MonsterSpawnZone.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <ctime>

BeginnersTown1::BeginnersTown1()
{
}

BeginnersTown1::~BeginnersTown1()
{
}

void BeginnersTown1::Start()
{
	//std::shared_ptr<MonsterSpawnZone> Zone = GetLevel()->CreateActor<MonsterSpawnZone>();
	//Zone->SetColMap(ColMapName);
	//Zone->SetMonsterToZone(MonsterName::GreenSnail, 5);
	//Zone->SetZonePosAndScale({ 200,0 }, 200.0f);

	LandScape0 = CreateComponent<GameEngineSpriteRenderer>();
	LandScape0->SetTexture("MapBackGround0.png");
	LandScape0->GetTransform()->SetLocalScale({2000, 2000});
	LandScape0->GetTransform()->SetLocalPosition({ 0, 0, static_cast<float>(RenderOrder::BasicMap) });

	Cloud = CreateComponent<ContentRenderer>();
	Cloud->SetScaleToTexture("MapBackGround1.png");

	float4 CloudScale = Cloud->GetTransform()->GetLocalScale();
	Cloud->GetTransform()->SetLocalPosition({ 0, 250, static_cast<float>(RenderOrder::BasicMap) });
	Cloud->GetTransform()->AddLocalScale({ CloudScale.x * 2.0f, 0 });

	LandScape2 = CreateComponent<GameEngineSpriteRenderer>();
	LandScape2->SetScaleToTexture("MapBackGround2.png");
	LandScape2->GetTransform()->SetLocalPosition({ 0, 200, static_cast<float>(RenderOrder::BasicMap) });

	BackGroundLayer = CreateComponent<GameEngineSpriteRenderer>();
	BackGroundLayer->SetScaleToTexture("BeginnersTown1Layer.png");
	BackGroundLayer->GetTransform()->SetLocalPosition({ 0, 0, static_cast<float>(RenderOrder::BasicMap) });

	BackGround = CreateComponent<GameEngineSpriteRenderer>();
	BackGround->SetScaleToTexture("BeginnersTown1.png");
	BackGround->GetTransform()->SetLocalPosition({ 0, 0, static_cast<float>(RenderOrder::BasicMap) });

	Rope = CreateComponent<GameEngineSpriteRenderer>();
	Rope->SetScaleToTexture("BeginnersTown1Rope.png");
	Rope->GetTransform()->SetLocalPosition({ 0, 0, static_cast<float>(RenderOrder::BasicMap) });

	RopeCol = CreateComponent<GameEngineCollision>();
	RopeCol->GetTransform()->SetLocalScale({ 25, 200 });
	RopeCol->GetTransform()->SetLocalPosition({ 482, 60 });
	RopeCol->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));

	std::shared_ptr<Hina> npc = GetLevel()->CreateActor<Hina>(static_cast<int>(RenderOrder::NPC));

	MyMiniMap = GetLevel()->CreateActor<MiniMap>(static_cast<int>(RenderOrder::UI));
	MyMiniMap->SetMap(MapName);
}

void BeginnersTown1::Update(float _DeltaTime)
{
	//PosUpdate();
	BackGroundMove(_DeltaTime);
}

void BeginnersTown1::Render(float _DeltaTime) 
{
}

void BeginnersTown1::BackGroundMove(float _DeltaTime)
{
	XMoveConstant += 0.06f * _DeltaTime;

	if (XMoveConstant > 3.0f)
	{
		XMoveConstant -= 3.0f;
	}

	Cloud->SetUVconstant({ XMoveConstant, 0, 3, 1});

	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();
	LandScape2->GetTransform()->SetLocalPosition({ CameraPos.x * 0.5f , 200, static_cast<float>(RenderOrder::BasicMap) });
}
