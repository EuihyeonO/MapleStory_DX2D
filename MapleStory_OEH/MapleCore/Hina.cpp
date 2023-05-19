#include "PrecompileHeader.h"
#include "Hina.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <ctime>

Hina::Hina()
{
}

Hina::~Hina()
{
}

void Hina::Start()
{
	TimeCounting();
	SetFrameList();

	HinaRender = CreateComponent<GameEngineSpriteRenderer>();
	Status = "NORMAL";

	GetTransform()->SetLocalScale({ -1, 1 });
	GetTransform()->SetLocalPosition({ -541, 244 });
}

void Hina::Update(float _DeltaTime)
{
	TimeCounting();
	TextureUpdate();
}

void Hina::Render(float _DeltaTime) 
{

}

void Hina::TextureUpdate()
{
	if(Status != "CRY")
	{
		std::string TextureName = "HINA" + Status + std::to_string(AniIndex) + ".png";
		HinaRender->SetScaleToTexture(TextureName);
	}
	else
	{
		int Index = AniIndex % 5;
		std::string TextureName = "HINA" + Status + std::to_string(Index) + ".png";
		HinaRender->SetScaleToTexture(TextureName);
	}

	AnimationCount += TimeCount;
	
	if (AnimationCount >= FrameList[Status][AniIndex])
	{
		AniIndex++;
		AnimationCount = 0.0f;

		if (AniIndex >= FrameList[Status].size())
		{
			AniIndex = 0;

			if(Status != "NORMAL")
			{
				Status = "NORMAL";
			}
			else
			{
				StatusUpdate();
			}
		}
	}
}

void Hina::StatusUpdate()
{
	int StatusType = GameEngineRandom::MainRandom.RandomInt(0, 8);
	
	if (StatusType > 4)
	{
		//NORMAL ÀÌ »ÌÈú È®·üÀ» ´õ ¿Ã¸²
		StatusType = 0;
	}

	switch (StatusType)
	{
	case 0:
		Status = "NORMAL";
		break;
	case 1:
		Status = "SMILE0";
		break;
	case 2:
		Status = "SMILE1";
		break;
	case 3:
		Status = "BEWILDERED";
		break;
	case 4:
		Status = "CRY";
		break;
	}
}

void Hina::SetFrameList()
{
	FrameList["NORMAL"].push_back(1.5f);
	FrameList["NORMAL"].push_back(0.1f);
	FrameList["NORMAL"].push_back(0.1f);
	FrameList["NORMAL"].push_back(1.0f);

	FrameList["SMILE0"].push_back(5.0f);

	FrameList["SMILE1"].push_back(5.0f);

	FrameList["BEWILDERED"].push_back(0.15f);
	FrameList["BEWILDERED"].push_back(0.15f);
	FrameList["BEWILDERED"].push_back(0.15f);
	FrameList["BEWILDERED"].push_back(0.15f);
	FrameList["BEWILDERED"].push_back(4.4f);


	for (int i = 0; i < 10; i++) 
	{
		FrameList["CRY"].push_back(0.1f);
		FrameList["CRY"].push_back(0.1f);
		FrameList["CRY"].push_back(0.1f);
		FrameList["CRY"].push_back(0.1f);
		FrameList["CRY"].push_back(0.1f);
	}

}
