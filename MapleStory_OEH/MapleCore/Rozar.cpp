#include "PrecompileHeader.h"
#include "Rozar.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

Rozar::Rozar()
{
}

Rozar::~Rozar()
{
}

void Rozar::Start()
{
	TimeCounting();

	RozarRender = CreateComponent<GameEngineSpriteRenderer>();
	Status = "STAND";

	GetTransform()->SetLocalPosition({ -20, 220 });
}

void Rozar::Update(float _DeltaTime) 
{
	TimeCounting();
	TextureUpdate();
}

void Rozar::Render(float _DeltaTime) 
{
}

void Rozar::TextureUpdate()
{
	if (Status == "STAND")
	{
		if (AniIndex == 0)
		{
			RozarRender->SetScaleToTexture("RozarStand0.png");
			AniIndex++;
		}

		AnimationCount += TimeCount;

		if (AnimationCount >= 5.0f)
		{
			AnimationCount = 0.0f;
			AniIndex = 0;
			StatusUpdate();
		}
	}
	else if (Status == "FINGER")
	{
		if (AniIndex == 0)
		{
			RozarRender->SetScaleToTexture("RozarFinger0.png");
			AniIndex++;
		}

		AnimationCount += TimeCount;

		if (AnimationCount >= 5.0f)
		{
			AnimationCount = 0.0f;
			AniIndex = 0;
			StatusUpdate();
		}
	}
	else if (Status == "WINK")
	{
		if (AniIndex == 0)
		{
			RozarRender->SetScaleToTexture("RozarWink0.png");
			AniIndex++;
		}

		AnimationCount += TimeCount;

		if (AnimationCount >= WinkFrame[0] && AniIndex == 1)
		{
			RozarRender->SetScaleToTexture("RozarWink1.png");
			AniIndex++;
			AnimationCount = 0.0f;
		}

		if (AnimationCount >= WinkFrame[1])
		{
			AnimationCount = 0.0f;
			AniIndex = 0;
			StatusUpdate();
		}
	}
}

void Rozar::StatusUpdate()
{
	int StatusType = GameEngineRandom::MainRandom.RandomInt(0, 5);

	if (StatusType > 3)
	{
		StatusType = 0;
	}

	switch (StatusType)
	{
	case 0:
		Status = "STAND";
		break;
	case 1:
		Status = "FINGER";
		break;
	case 2:
		Status = "WINK";
		break;
	}
}