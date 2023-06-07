#include "PrecompileHeader.h"
#include "AlterOfZakum.h"
#include "Zakum.h"

#include "ContentRenderer.h"
#include <GameEngineCore/GameEngineLevel.h>

AlterOfZakum::AlterOfZakum()
{
}

AlterOfZakum::~AlterOfZakum()
{
}

void AlterOfZakum::Start()
{
	LandScape0 = CreateComponent<ContentRenderer>();
	LandScape0->SetTexture("ZakumLandScape0.png");
	LandScape0->GetTransform()->SetLocalScale({ 200 * 6, 600 });
	LandScape0->GetTransform()->SetLocalPosition({ 0, 100.0f });
	LandScape0->SetUVconstant({ 0, 0, 6, 1 });

	LandScape1 = CreateComponent<GameEngineSpriteRenderer>();
	LandScape1->SetScaleToTexture("ZakumLandScape1.png");

	LandScape2 = CreateComponent<GameEngineSpriteRenderer>();
	LandScape2->SetScaleToTexture("ZakumLandScape1.png");

	LandScape3 = CreateComponent<GameEngineSpriteRenderer>();
	LandScape3->SetScaleToTexture("ZakumLandScape3.png");
	LandScape3->GetTransform()->SetLocalPosition({ 530, 80.0f, -2.0f });

	LandScape4 = CreateComponent<GameEngineSpriteRenderer>();
	LandScape4->SetScaleToTexture("ZakumLandScape4.png");
	LandScape4->GetTransform()->SetLocalPosition({ -400, 80.0f, -2.0f });

	BackGround = CreateComponent<GameEngineSpriteRenderer>();
	BackGround->SetScaleToTexture("AlterOfZakum.png");
	BackGround->GetTransform()->AddLocalPosition({ 0, 0, -3.0f });

	AlterBack = CreateComponent<GameEngineSpriteRenderer>();
	AlterBack->SetScaleToTexture("Alter1.png");
	AlterBack->GetTransform()->SetLocalPosition({ 50.0f, 70.0f , -1.0f });

	Alter = CreateComponent<GameEngineSpriteRenderer>();
	Alter->SetScaleToTexture("Alter0.png");
	Alter->GetTransform()->SetLocalPosition({ 0, -180.0f , -5.0f });

	Layer = CreateComponent<GameEngineSpriteRenderer>();
	Layer->SetScaleToTexture("AlterOfZakumLayer.png");
	Layer->GetTransform()->SetLocalPosition({ 0, 0, -10.0f });

	Magma = CreateComponent<ContentRenderer>();
	Magma->SetTexture("Magma.png");
	Magma->GetTransform()->SetLocalScale({ 264 * 5, 96 });
	Magma->GetTransform()->SetLocalPosition({ 0, -220, -6.0f });
	Magma->SetUVconstant({ 0, 0, 5, 1 });

	std::shared_ptr<GameEngineSpriteRenderer> FootHold0 = CreateComponent<GameEngineSpriteRenderer>();
	FootHold0->SetScaleToTexture("FootHold0.png");
	FootHold0->GetTransform()->SetLocalPosition({ 450.0f, -150.0f, -4.0f });

	std::shared_ptr<GameEngineSpriteRenderer> FootHold1 = CreateComponent<GameEngineSpriteRenderer>();
	FootHold1->SetScaleToTexture("FootHold1.png");
	FootHold1->GetTransform()->SetLocalPosition({ 380.0f, -80.0f, -4.0f });

	std::shared_ptr<GameEngineSpriteRenderer> FootHold2 = CreateComponent<GameEngineSpriteRenderer>();
	FootHold2->SetScaleToTexture("FootHold0.png");
	FootHold2->GetTransform()->SetLocalPosition({ 460.0f, -10.0f, -4.0f });

	std::shared_ptr<GameEngineSpriteRenderer> FootHold3 = CreateComponent<GameEngineSpriteRenderer>();
	FootHold3->SetScaleToTexture("FootHold1.png");
	FootHold3->GetTransform()->SetLocalPosition({ 410.0f, 140.0f, -4.0f });

	std::shared_ptr<GameEngineSpriteRenderer> Rope1 = CreateComponent<GameEngineSpriteRenderer>();
	Rope1->SetScaleToTexture("ZakumRope1.png");
	Rope1->GetTransform()->SetLocalPosition({ 370.0f, 95.0f, -4.0f });

	TransformData Rope1Data = Rope1->GetTransform()->GetTransDataRef();

	std::shared_ptr<GameEngineCollision> RopeCol = CreateComponent<GameEngineCollision>();
	RopeCol->GetTransform()->SetLocalScale(Rope1Data.LocalScale);
	RopeCol->GetTransform()->SetLocalPosition(Rope1Data.LocalPosition);
	RopeCol->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));

	std::shared_ptr<Zakum> NewZakum = GetLevel()->CreateActor<Zakum>();
	NewZakum->GetTransform()->AddLocalPosition({ 0, 0.0f, -5.0f });
}

void AlterOfZakum::Update(float _DeltaTime) 
{
	MagmaMove(_DeltaTime);
	LandScapeMove();
}

void AlterOfZakum::Render(float _DeltaTime)
{
}

void AlterOfZakum::LandScapeMove()
{
	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();
	float4 MapSize = GameEngineTexture::Find("AlterOfZakum.png")->GetScale();

	float4 CameraPosPerMapScaleRatio = { CameraPos.x / MapSize.x, CameraPos.y / MapSize.y };

	LandScape1->GetTransform()->SetLocalPosition({ 100.0f * CameraPosPerMapScaleRatio.x - 200.0f , 600.0f * CameraPosPerMapScaleRatio.y + 60.0f , -1.0f});
	LandScape2->GetTransform()->SetLocalPosition({ 100.0f * CameraPosPerMapScaleRatio.x + 300.0f , 600.0f * CameraPosPerMapScaleRatio.y + 50.0f , -1.0f });

}

void AlterOfZakum::MagmaMove(float _DeltaTime)
{
	Magma_UVXMove += 0.025f * _DeltaTime;

	if (Magma_UVXMove >= 5)
	{
		Magma_UVXMove -= 5.0f;
	}

	Magma->SetUVconstant({ Magma_UVXMove, 0, 5, 1 });
}