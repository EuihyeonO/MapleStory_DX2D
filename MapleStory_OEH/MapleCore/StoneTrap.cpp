#include "PrecompileHeader.h"
#include "StoneTrap.h"
#include "Player.h"

#include <GameEngineCore/GameEngineLevel.h>

StoneTrap::StoneTrap()
{
}

StoneTrap::~StoneTrap()
{
}

void StoneTrap::Start()
{
	TrapRender = CreateComponent<GameEngineSpriteRenderer>();
	TrapRender->CreateAnimation({ .AnimationName = "Trap",.SpriteName = "StoneTrap",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });

	TrapCol = CreateComponent<GameEngineCollision>();
	TrapCol->SetColType(ColType::AABBBOX2D);
	TrapCol->GetTransform()->SetLocalScale({ 30, 40 });
	TrapCol->Off();

	TrapRender->SetAnimationStartEvent("Trap", 0, [this] {TrapCol->On(); TrapCol->GetTransform()->SetLocalPosition({ 0, 150 }); });
	TrapRender->SetAnimationStartEvent("Trap", 1, [this] {TrapCol->GetTransform()->SetLocalPosition({ 0, 120 }); });
	TrapRender->SetAnimationStartEvent("Trap", 2, [this] {TrapCol->GetTransform()->SetLocalPosition({ 0, 30 }); });
	TrapRender->SetAnimationStartEvent("Trap", 3, [this] {TrapCol->GetTransform()->SetLocalPosition({ 0, -50 }); });
	TrapRender->SetAnimationStartEvent("Trap", 4, [this] {TrapCol->GetTransform()->SetLocalPosition({ 0, -110 }); });
	TrapRender->SetAnimationStartEvent("Trap", 5, [this] {TrapCol->GetTransform()->SetLocalPosition({ 0, -130 }); });
	TrapRender->SetAnimationStartEvent("Trap", 6, [this] {TrapCol->GetTransform()->SetLocalPosition({ 0, -150 }); });
	TrapRender->SetAnimationStartEvent("Trap", 7, [this] {TrapCol->GetTransform()->SetLocalPosition({ 0, -150 }); });
	TrapRender->SetAnimationStartEvent("Trap", 8, [this] {TrapCol->Off(); TrapRender->Off(); GetLevel()->TimeEvent.AddEvent(2.0f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {TrapRender->On(); TrapRender->ChangeAnimation("Trap"); }); });

	TrapRender->ChangeAnimation("Trap");
}

void StoneTrap::Update(float _DeltaTime) 
{
	if (TrapCol->IsUpdate() == true && TrapCol->Collision(static_cast<int>(CollisionOrder::Player), ColType::AABBBOX2D, ColType::AABBBOX2D) != nullptr)
	{
		float4 PlayerPos = Player::GetCurPlayer()->GetTransform()->GetWorldPosition();
		float4 TrapPos = TrapCol->GetTransform()->GetWorldPosition();

		float4 Dir;

		if (PlayerPos.x > TrapPos.x)
		{
			Dir = { 1, 1 };
		}
		else
		{
			Dir = { -1, 1 };
		}

		Dir.Normalize();

		float Time = 1.0f;

		Player::GetCurPlayer()->KnockBack(Dir, 100.0f, 10, 150.0f, Time);
		TrapCol->Off();
	}
}

void StoneTrap::Render(float _DeltaTime) 
{

}
