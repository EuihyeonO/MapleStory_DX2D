#include "PrecompileHeader.h"
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
	TimeCounting();

	StarRender = CreateComponent<GameEngineSpriteRenderer>();	
}

void Star::Update(float _DeltaTime)
{
	TimeCounting();
	Move(_DeltaTime);
	AnimationUpdate();

	if (UpdateFuction != nullptr)
	{
		UpdateFuction(_DeltaTime);
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


void Star::Move(float _DeltaTime)
{
	GetTransform()->AddLocalPosition({ 400.0f * _DeltaTime, 0});
}