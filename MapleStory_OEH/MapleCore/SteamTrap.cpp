#include "PrecompileHeader.h"
#include "SteamTrap.h"
#include "Player.h"

#include <GameEngineCore/GameEngineLevel.h>

SteamTrap::SteamTrap()
{
}

SteamTrap::~SteamTrap()
{
}

void SteamTrap::Start()
{
	Trap = CreateComponent<GameEngineSpriteRenderer>();
	Trap->SetScaleToTexture("SteamTrap.png");
	Trap->GetTransform()->SetLocalPosition({ 0, -50 });

	TrapRender = CreateComponent<GameEngineSpriteRenderer>();
	TrapRender->CreateAnimation({ .AnimationName = "Trap",.SpriteName = "SteamTrap",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });

	TrapCol = CreateComponent<GameEngineCollision>();
	TrapCol->SetColType(ColType::AABBBOX2D);
	TrapCol->GetTransform()->SetLocalScale({ 30, 60 });
	TrapCol->Off();

	TrapRender->SetAnimationStartEvent("Trap", 0, [this] {TrapCol->On(); });
	TrapRender->SetAnimationStartEvent("Trap", 6, [this] {TrapCol->Off(); TrapRender->Off(); GetLevel()->TimeEvent.AddEvent(2.0f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {TrapRender->On(); TrapRender->ChangeAnimation("Trap"); }); });

	TrapRender->ChangeAnimation("Trap");
}

void SteamTrap::Update(float _DeltaTime) 
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

void SteamTrap::Render(float _DeltaTime) 
{

}
