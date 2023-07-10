#include "PrecompileHeader.h"
#include "BeginnersTown1.h"
#include "MiniMap.h"
#include "Hina.h"
#include "ContentEnums.h"
#include "ContentRenderer.h"
#include "GreenSnail.h"
#include "MonsterSpawnZone.h"
#include "Portal.h"

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
	RopeCol->GetTransform()->SetLocalPosition({ 482, 62 });
	RopeCol->SetColType(ColType::AABBBOX2D);
	RopeCol->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));

	std::shared_ptr<Hina> npc = GetLevel()->CreateActor<Hina>(static_cast<int>(RenderOrder::NPC));
	npc->GetTransform()->SetLocalPosition({ -541, 244 });

	MyPortal = GetLevel()->CreateActor<Portal>();
	MyPortal->SetLinkedMap("Level_BeginnersTown2");
	MyPortal->SetPortalPos({ 625, 45, -10 });

	Black = CreateComponent<GameEngineUIRenderer>();
	Black->GetTransform()->SetWorldScale({ 800, 600 });
	Black->GetTransform()->SetWorldPosition({ 0, 0 });
	Black->ColorOptionValue.MulColor = { 0.0f, 0.0f, 0.0f, 1.0f };
	
	MyMiniMap = GetLevel()->CreateActor<MiniMap>(static_cast<int>(RenderOrder::UI));
	MyMiniMap->SetMap(MapName);
	MyMiniMap->SetNPCToMiniMap({ -541, 244 });
	MyMiniMap->SetPortalToMiniMap({ 625, 45 });

	FadeInUpdate = &BeginnersTown1::FadeIn;
}

void BeginnersTown1::Update(float _DeltaTime)
{
	BackGroundMove(_DeltaTime);

	if (FadeInUpdate != nullptr)
	{
		FadeInUpdate(*this, _DeltaTime);
	}
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


void BeginnersTown1::ActorDeath()
{
	MyPortal->Death();
	MyPortal = nullptr;

	MyMiniMap->Death();
	MyMiniMap = nullptr;
}


void BeginnersTown1::FadeIn(float _DeltaTime)
{
	Black->ColorOptionValue.MulColor.a -= 1.0F * _DeltaTime;

	if (Black->ColorOptionValue.MulColor.a <= 0)
	{
		Black->Death();
		Black = nullptr;
		FadeInUpdate = nullptr;
	}
}