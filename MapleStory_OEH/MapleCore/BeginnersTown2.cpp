#include "PrecompileHeader.h"
#include "BeginnersTown2.h"
#include "MiniMap.h"
#include "ContentRenderer.h"
#include "Rozar.h"
#include "Portal.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

BeginnersTown2::BeginnersTown2()
{
}

BeginnersTown2::~BeginnersTown2()
{
}

void BeginnersTown2::Start()
{
	LandScape0 = CreateComponent<GameEngineSpriteRenderer>();
	LandScape0->SetTexture("MapBackGround0.png");
	LandScape0->GetTransform()->SetLocalScale({ 2000, 2000 });
	LandScape0->GetTransform()->SetLocalPosition({ 0, 0, static_cast<float>(RenderOrder::BasicMap) });

	Cloud = CreateComponent<ContentRenderer>();
	Cloud->SetScaleToTexture("MapBackGround1.png");

	float4 CloudScale = Cloud->GetTransform()->GetLocalScale();
	Cloud->GetTransform()->SetLocalPosition({ 0, 250, -static_cast<float>(RenderOrder::BasicMap) });
	Cloud->GetTransform()->AddLocalScale({ CloudScale.x * 2.0f, 0 });

	LandScape2 = CreateComponent<GameEngineSpriteRenderer>();
	LandScape2->SetScaleToTexture("MapBackGround2.png");
	LandScape2->GetTransform()->SetLocalPosition({ 0, 200, static_cast<float>(RenderOrder::BasicMap) });

	BackGround = CreateComponent<GameEngineSpriteRenderer>();
	BackGround->SetScaleToTexture("BeginnersTown2.png");

	MyRozar = GetLevel()->CreateActor<Rozar>(static_cast<int>(RenderOrder::NPC));
	
	MyPortal1 = GetLevel()->CreateActor<Portal>(static_cast<int>(RenderOrder::UI));
	MyPortal1->SetLinkedMap("Level_BeginnersTown1");
	MyPortal1->SetPortalPos({ -460, 95, -10 });

	MyPortal2 = GetLevel()->CreateActor<Portal>(static_cast<int>(RenderOrder::UI));
	MyPortal2->SetLinkedMap("Level_CrossRoad");
	MyPortal2->SetPortalPos({ 465, 155, -10 });

	MyMiniMap = GetLevel()->CreateActor<MiniMap>(static_cast<int>(RenderOrder::UI));
	MyMiniMap->SetMap(MapName);
	MyMiniMap->SetNPCToMiniMap({ -20, 220 });
	MyMiniMap->SetPortalToMiniMap({ -460, 95, -10 });
	MyMiniMap->SetPortalToMiniMap({ 465, 155, -10 });
	MyMiniMap->SetMapMark("MushroomVillageMark.png");
	MyMiniMap->SetWorldName("메이플월드");
	MyMiniMap->SetMapName("버섯마을");

	Black = CreateComponent<GameEngineUIRenderer>();
	Black->GetTransform()->SetWorldScale({ 800, 600 });
	Black->GetTransform()->SetWorldPosition({ 0, 0 });
	Black->ColorOptionValue.MulColor = { 0.0f, 0.0f, 0.0f, 1.0f };

	FadeInUpdate = &BeginnersTown2::FadeIn;
}

void BeginnersTown2::Update(float _DeltaTime)
{
	BackGroundMove(_DeltaTime);

	if (FadeInUpdate != nullptr)
	{
		FadeInUpdate(*this, _DeltaTime);
	}
}

void BeginnersTown2::Render(float _DeltaTime) 
{
}

void BeginnersTown2::BackGroundMove(float _DeltaTime)
{
	XMoveConstant += 0.06f * _DeltaTime;

	if (XMoveConstant > 3.0f)
	{
		XMoveConstant -= 3.0f;
	}

	Cloud->SetUVconstant({ XMoveConstant, 0, 3, 1 });

	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();
	LandScape2->GetTransform()->SetLocalPosition({ CameraPos.x * 0.5f , 200, static_cast<float>(RenderOrder::BasicMap) });
}


void BeginnersTown2::ActorDeath()
{
	if(MyPortal1 != nullptr)
	{
		MyPortal1->Death();
		MyPortal1 = nullptr;
	}

	if(MyPortal2 != nullptr)
	{
		MyPortal2->Death();
		MyPortal2 = nullptr;
	}

	if(MyMiniMap != nullptr)
	{
		MyMiniMap->Death();
		MyMiniMap = nullptr;
	}

	if(MyRozar != nullptr)
	{
		MyRozar->ActorDeath();
		MyRozar->Death();
		MyRozar = nullptr;
	}
}

void BeginnersTown2::FadeIn(float _DeltaTime)
{
	Black->ColorOptionValue.MulColor.a -= 1.0F * _DeltaTime;

	if (Black->ColorOptionValue.MulColor.a <= 0)
	{
		Black->Death();
		Black = nullptr;
		FadeInUpdate = nullptr;
	}
}