#include "PrecompileHeader.h"
#include "KerningCity.h"

#include <GameEngineCore/GameEngineLevel.h>

KerningCity::KerningCity()
{
}

KerningCity::~KerningCity()
{
}

void KerningCity::Start()
{
	Map = CreateComponent<GameEngineSpriteRenderer>();
	Map->SetScaleToTexture(MapName);

	BackGround1 = CreateComponent<GameEngineSpriteRenderer>();
	BackGround1->SetScaleToTexture("KerningCityBackGround0.png");

	BackGround2 = CreateComponent<GameEngineSpriteRenderer>();
	BackGround2->SetScaleToTexture("KerningCityBackGround1.png");

	BackGround3 = CreateComponent<GameEngineSpriteRenderer>();
	BackGround3->SetScaleToTexture("KerningCityBackGround2.png");

	std::shared_ptr<GameEngineCollision> Rope1 = CreateComponent<GameEngineCollision>();
	Rope1->SetColType(ColType::AABBBOX2D);
	Rope1->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));
	Rope1->GetTransform()->SetLocalPosition({ 416.0f, -256.0f });
	Rope1->GetTransform()->SetLocalScale({ 10.0f, 130.0f });
	
	std::shared_ptr<GameEngineCollision> Rope2 = CreateComponent<GameEngineCollision>();
	Rope2->SetColType(ColType::AABBBOX2D);
	Rope2->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));
	Rope2->GetTransform()->SetLocalPosition({ 6.0f, -462.0f });
	Rope2->GetTransform()->SetLocalScale({ 10.0f, 124.0f });
	
	GetLevel()->IsDebugSwitch();
}

void KerningCity::Update(float _DeltaTime)
{
	BackGroundUpdate(_DeltaTime);
}

void KerningCity::Render(float _DeltaTime) 
{

}

void KerningCity::BackGroundUpdate(float _DeltaTime)
{
	float4 MapScale = GameEngineTexture::Find("KerningCity.png")->GetScale();

	// -100 + CamPos ~ 100 + CamPos
	float4 CamPos = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();
	
	float Ratio = CamPos.x / MapScale.hx();

	BackGround1->GetTransform()->SetLocalPosition(CamPos + float4{ 0, 0, 3 });
	BackGround2->GetTransform()->SetLocalPosition(CamPos + float4::Lerp({30, 0}, {-30, 0}, abs(Ratio)) + float4{0, 150, 2});
	BackGround3->GetTransform()->SetLocalPosition(CamPos + float4::Lerp({ 50, 0 }, {-50, 0 }, abs(Ratio)) + float4{ 0, 50, 1 });
}