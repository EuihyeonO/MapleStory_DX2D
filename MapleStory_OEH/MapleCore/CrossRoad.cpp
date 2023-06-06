#include "PrecompileHeader.h"
#include "CrossRoad.h"
#include "ContentRenderer.h"
#include "Portal.h"

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
	LandScape0->GetTransform()->SetLocalScale({ 635 * 6 , 719 });
	LandScape0->GetTransform()->SetLocalPosition({ 0 , 350.0f });
	LandScape0->SetUVconstant({0, 0, 6, 1});
	
	LandScape1 = CreateComponent<ContentRenderer>();
	LandScape1->SetTexture("MapBackGround4.png");
	LandScape1->GetTransform()->SetLocalScale({ 1024 * 3, 439 });
	LandScape1->GetTransform()->SetLocalPosition({ 0 , 250.0f });
	LandScape1->SetUVconstant({ 0, 0, 3, 1 });
	LandScape1->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.75f });

	LandScape2 = CreateComponent<ContentRenderer>();
	LandScape2->SetTexture("MapBackGround3.png");
	LandScape2->GetTransform()->SetLocalScale({ 2049 * 2, 503 });
	LandScape2->GetTransform()->SetLocalPosition({ 0 , 150.0f });
	LandScape2->SetUVconstant({ 0, 0, 2, 1 });

	BackGround = CreateComponent<GameEngineSpriteRenderer>();
	BackGround->SetScaleToTexture("CrossRoad.png");

	std::shared_ptr<Portal> Port1 = GetLevel()->CreateActor<Portal>(static_cast<int>(RenderOrder::UI));
	Port1->SetLinkedMap("Level_BeginnersTown2");
	Port1->SetPortalPos({ -1750, 45, -10 });


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

	LandScape0->GetTransform()->SetLocalPosition(float4{ (800.0f * CameraPosPerMapScaleRatio.x * 0.5f), (600.0f * CameraPosPerMapScaleRatio.y * 1.5f + 250.0f) });

	LandScape1->GetTransform()->SetLocalPosition(float4{ (800.0f * CameraPosPerMapScaleRatio.x - 100.0f) , (600.0f * CameraPosPerMapScaleRatio.y * 1.5f + 200.0f) });

	LandScape2->GetTransform()->SetLocalPosition(float4{ (800.0f * CameraPosPerMapScaleRatio.x * 1.25f) - 100.0f, (600.0f * CameraPosPerMapScaleRatio.y * 1.5f  + 50.0f) });
}