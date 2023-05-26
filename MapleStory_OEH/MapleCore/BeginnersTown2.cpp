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

	std::shared_ptr<Rozar> npc = GetLevel()->CreateActor<Rozar>(static_cast<int>(RenderOrder::NPC));
	std::shared_ptr<Portal> Port = GetLevel()->CreateActor<Portal>(static_cast<int>(RenderOrder::UI));

	MyMiniMap = GetLevel()->CreateActor<MiniMap>(static_cast<int>(RenderOrder::UI));
	MyMiniMap->SetMap(MapName);
}

void BeginnersTown2::Update(float _DeltaTime)
{
	BackGroundMove(_DeltaTime);
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
