#include "PrecompileHeader.h"
#include "ZakumRoad2.h"
#include "ContentRenderer.h"

ZakumRoad2::ZakumRoad2()
{
}

ZakumRoad2::~ZakumRoad2()
{
}

void ZakumRoad2::Start()
{
	BackGround = CreateComponent<ContentRenderer>();
	BackGround->SetTexture("ZakumLandScape0.png");
	BackGround->GetTransform()->SetLocalScale({ 200 * 22, 600 });
	BackGround->GetTransform()->SetLocalPosition({ 0, -5, 2 });
	BackGround->SetUVconstant({ 0, 0, 22, 1 });

	Tile = CreateComponent<GameEngineSpriteRenderer>();
	Tile->SetScaleToTexture("ZakumRoad2.png");
	Tile->GetTransform()->AddLocalPosition({ 0, 0, -10 });

	Layer = CreateComponent<GameEngineSpriteRenderer>();
	Layer->SetScaleToTexture("ZakumRoad2Layer.png");
	Layer->GetTransform()->AddLocalPosition({ 0, 0, -1000 });

	Magma = CreateComponent<ContentRenderer>();
	Magma->SetTexture("Magma.png");
	Magma->GetTransform()->SetLocalScale({ 264 * 17, 96 });
	Magma->GetTransform()->SetLocalPosition({ 0, -280, -115 });
	Magma->SetUVconstant({ 0, 0, 17, 1 });

	std::shared_ptr<GameEngineCollision> Rope1 = CreateComponent<GameEngineCollision>();
	Rope1->GetTransform()->SetLocalScale({ 10, 500 });
	Rope1->GetTransform()->SetLocalPosition({ 467, 100 });
	Rope1->SetColType(ColType::AABBBOX2D);
	Rope1->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));

	std::shared_ptr<GameEngineCollision> Rope2 = CreateComponent<GameEngineCollision>();
	Rope2->GetTransform()->SetLocalScale({ 10, 500 });
	Rope2->GetTransform()->SetLocalPosition({ 517, 150 });
	Rope2->SetColType(ColType::AABBBOX2D);
	Rope2->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));

	std::shared_ptr<GameEngineCollision> Rope3 = CreateComponent<GameEngineCollision>();
	Rope3->GetTransform()->SetLocalScale({ 10, 500 });
	Rope3->GetTransform()->SetLocalPosition({ 567, 200 });
	Rope3->SetColType(ColType::AABBBOX2D);
	Rope3->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));

	std::shared_ptr<GameEngineCollision> Rope4 = CreateComponent<GameEngineCollision>();
	Rope4->GetTransform()->SetLocalScale({ 10, 500 });
	Rope4->GetTransform()->SetLocalPosition({ 617, 250 });
	Rope4->SetColType(ColType::AABBBOX2D);
	Rope4->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));

	std::shared_ptr<GameEngineCollision> Rope5 = CreateComponent<GameEngineCollision>();
	Rope5->GetTransform()->SetLocalScale({ 10, 500 });
	Rope5->GetTransform()->SetLocalPosition({ 667, 200 });
	Rope5->SetColType(ColType::AABBBOX2D);
	Rope5->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));

	std::shared_ptr<GameEngineCollision> Rope6 = CreateComponent<GameEngineCollision>();
	Rope6->GetTransform()->SetLocalScale({ 10, 500 });
	Rope6->GetTransform()->SetLocalPosition({ 717, 250 });
	Rope6->SetColType(ColType::AABBBOX2D);
	Rope6->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));

	std::shared_ptr<GameEngineCollision> Rope7 = CreateComponent<GameEngineCollision>();
	Rope7->GetTransform()->SetLocalScale({ 10, 500 });
	Rope7->GetTransform()->SetLocalPosition({ 767, 200 });
	Rope7->SetColType(ColType::AABBBOX2D);
	Rope7->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));

	std::shared_ptr<GameEngineCollision> Rope8 = CreateComponent<GameEngineCollision>();
	Rope8->GetTransform()->SetLocalScale({ 10, 500 });
	Rope8->GetTransform()->SetLocalPosition({ 817, 300 });
	Rope8->SetColType(ColType::AABBBOX2D);
	Rope8->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));

	std::shared_ptr<GameEngineCollision> Rope9 = CreateComponent<GameEngineCollision>();
	Rope9->GetTransform()->SetLocalScale({ 10, 500 });
	Rope9->GetTransform()->SetLocalPosition({ 927, 200 });
	Rope9->SetColType(ColType::AABBBOX2D);
	Rope9->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));

	std::shared_ptr<GameEngineCollision> Rope10 = CreateComponent<GameEngineCollision>();
	Rope10->GetTransform()->SetLocalScale({ 10, 500 });
	Rope10->GetTransform()->SetLocalPosition({ 987, 300 });
	Rope10->SetColType(ColType::AABBBOX2D);
	Rope10->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));

	std::shared_ptr<GameEngineCollision> Rope11 = CreateComponent<GameEngineCollision>();
	Rope11->GetTransform()->SetLocalScale({ 10, 500 });
	Rope11->GetTransform()->SetLocalPosition({ 1047, 150 });
	Rope11->SetColType(ColType::AABBBOX2D);
	Rope11->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));

	std::shared_ptr<GameEngineCollision> Rope12 = CreateComponent<GameEngineCollision>();
	Rope12->GetTransform()->SetLocalScale({ 10, 500 });
	Rope12->GetTransform()->SetLocalPosition({ 1108, 250 });
	Rope12->SetColType(ColType::AABBBOX2D);
	Rope12->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));

	std::shared_ptr<GameEngineCollision> Rope13 = CreateComponent<GameEngineCollision>();
	Rope13->GetTransform()->SetLocalScale({ 10, 500 });
	Rope13->GetTransform()->SetLocalPosition({ 1202, 200 });
	Rope13->SetColType(ColType::AABBBOX2D);
	Rope13->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));

	std::shared_ptr<GameEngineCollision> Rope14 = CreateComponent<GameEngineCollision>();
	Rope14->GetTransform()->SetLocalScale({ 10, 500 });
	Rope14->GetTransform()->SetLocalPosition({ 1281, 278 });
	Rope14->SetColType(ColType::AABBBOX2D);
	Rope14->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));

	std::shared_ptr<GameEngineCollision> Rope15 = CreateComponent<GameEngineCollision>();
	Rope15->GetTransform()->SetLocalScale({ 10, 500 });
	Rope15->GetTransform()->SetLocalPosition({ 1339, 385 });
	Rope15->SetColType(ColType::AABBBOX2D);
	Rope15->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));

	std::shared_ptr<GameEngineCollision> Rope16 = CreateComponent<GameEngineCollision>();
	Rope16->GetTransform()->SetLocalScale({ 10, 500 });
	Rope16->GetTransform()->SetLocalPosition({ 1485, 100 });
	Rope16->SetColType(ColType::AABBBOX2D);
	Rope16->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));

	for (int i = 0; i < 12; i++)
	{
		//int Num = i % 2 + 1;

		//std::shared_ptr<GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>();
		//Renderer->SetScaleToTexture("ZakumLandScape" + std::to_string(Num) + ".png");
		//Renderer->GetTransform()->SetLocalPosition({ -2200 + 400.0f * i , 1 });

		//Num += 2;

		//std::shared_ptr<GameEngineSpriteRenderer> Renderer1 = CreateComponent<GameEngineSpriteRenderer>();
		//Renderer1->SetScaleToTexture("ZakumLandScape" + std::to_string(Num) + ".png");
		//Renderer1->GetTransform()->SetLocalPosition({ -2000 + 400.0f * i , -1 });
	}
}

void ZakumRoad2::Update(float _DeltaTime) 
{
	XUVCount += 0.05f * _DeltaTime;

	if (XUVCount >= 1.0f)
	{
		XUVCount -= 1.0f;
	}

	Magma->SetUVconstant({ XUVCount, 0, 11, 1 });
}

void ZakumRoad2::Render(float _DeltaTime) 
{

}
