#include "PrecompileHeader.h"
#include "JazzBar.h"
#include "DarkLord.h"

#include <GameEngineCore/GameEngineLevel.h>

JazzBar::JazzBar()
{
}

JazzBar::~JazzBar()
{
}

void JazzBar::Start()
{
	Map = CreateComponent<GameEngineSpriteRenderer>();
	Map->SetScaleToTexture(MapName);

	Layer = CreateComponent<GameEngineSpriteRenderer>();
	Layer->SetScaleToTexture("JazzBarLayer.png");
	Layer->GetTransform()->AddLocalPosition({ 0, 0, -100.0f });

	std::shared_ptr<GameEngineCollision> Radder1 = CreateComponent<GameEngineCollision>();
	Radder1->SetColType(ColType::AABBBOX2D);
	Radder1->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));
	Radder1->GetTransform()->SetLocalPosition({ -304.0f, -170.0f });
	Radder1->GetTransform()->SetLocalScale({ 40.0f, 300.0f });

	MyDarkLord = GetLevel()->CreateActor<DarkLord>();
	MyDarkLord->GetTransform()->SetLocalPosition({ 135, -235 });
}

void JazzBar::Update(float _DeltaTime) 
{

}

void JazzBar::Render(float _DeltaTime) 
{

}

void JazzBar::ActorDeath()
{
	if (MyDarkLord != nullptr)
	{
		MyDarkLord->ActorDeath();
		MyDarkLord->Death();
		MyDarkLord = nullptr;
	}
}