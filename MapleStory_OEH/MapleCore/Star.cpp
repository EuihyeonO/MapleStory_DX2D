#include "PrecompileHeader.h"
#include "Player.h"
#include "PlayerValue.h"
#include "Star.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <ctime>

Star::Star()
{
}

Star::~Star()
{
}

void Star::Start()
{
	MoveDistance = PlayerValue::GetValue()->GetMoveDistance();
	TimeCounting();

	StarRender = CreateComponent<GameEngineSpriteRenderer>();	
	StarRender->Off();
}

void Star::Update(float _DeltaTime)
{

	if(UpdateFuction == nullptr)
	{
		TimeCounting();
		StartTimingCheck(_DeltaTime);
	}
	else
	{
		UpdateFuction(*this, _DeltaTime);
		AnimationUpdate();
	}

}

void Star::Render(float _DeltaTime)
{

}

void Star::TimeCounting()
{
	CurTime = static_cast<float>(clock());

	TimeCount = (CurTime - PrevTime) / 1000.0f;

	PrevTime = CurTime;
}

void Star::AnimationUpdate()
{	
	AnimationCount += TimeCount;

	if (AnimationCount >= 0.03f)
	{
		AniIndex++;

		if (AniIndex > 1)
		{
			AniIndex = 0;
		}

		std::string TextureName = StarName + "Move" + std::to_string(AniIndex) + ".png";

		StarRender->SetScaleToTexture(TextureName);
		float4 Scale = StarRender->GetTransform()->GetLocalScale();
	}
}

void Star::StartTimingCheck(float _DeltaTime)
{
	std::string MoveType = Player::GetCurPlayer()->GetMoveType().data();
	
	if (MoveType != "Swing0" &&
		MoveType != "Swing1" &&
		MoveType != "Swing2")
	{
		return;
	}

	if (Player::GetCurPlayer()->GetAniIndex() < TimingIndex)
	{
		return;
	}

	if(isSet == false)
	{
		SetStartPos();

		StarRender->On();
		UpdateFuction = &Star::Move;

		isSet = true;
	}
}

void Star::SetStartPos()
{
	StartPos = Player::GetCurPlayer()->GetWeaponPos();
	GetTransform()->SetLocalPosition(StartPos);
}

void Star::Move(float _DeltaTime)
{
	float4 MoveDis = { Dir.x * 400.0f * _DeltaTime, 0 };

	GetTransform()->AddLocalPosition(MoveDis);
	float4 Pos = GetTransform()->GetLocalPosition();

	MoveDistance -= MoveDis;

	if (MoveDistance.x <= 0.0f)
	{
		Death();
	}	
}