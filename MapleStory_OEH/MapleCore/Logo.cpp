#include "PrecompileHeader.h"
#include "Logo.h"
#include "Player.h"
#include "TitleObjects.h"
#include <gameEngineCore/GameEngineLevel.h>
#include <ctime>

Logo::Logo()
{
}

Logo::~Logo()
{
}

void Logo::Start()
{
	TimeCounting();

	Nexon = CreateComponent<GameEngineSpriteRenderer>();
	Nexon->SetTexture("scene0.png");
	Nexon->GetTransform()->SetLocalScale({ 800, 600 });

	Wizet = CreateComponent<GameEngineSpriteRenderer>();
}

void Logo::Update(float _DeltaTime)
{
	TimeCounting();
	NexonAnimation();
	WizetAnimation();

	if (isNexonEnd == true && isWizetEnd == true && isCreateObject == false)
	{
		DeathWaitingCount += TimeCount;

		if (DeathWaitingCount >= 1.0f)
		{
			GetLevel()->CreateActor<TitleObjects>();			
			isCreateObject = true;
			//이 때 Death 해야함
		}
	}
}

void Logo::Render(float _DeltaTime)
{
}

void Logo::NexonAnimation()
{
	NexonCount += TimeCount;
	Nexon->GetTransform()->SetLocalScale({ 800, 600 });
	if (NexonCount >= 0.03)
	{
		if (NexonIndex == 180)
		{
			isNexonEnd = true;
			return;
		}

		NexonIndex++;
		NexonCount = 0;

		std::string TextureName = "scene" + std::to_string(NexonIndex) + ".png";
		Nexon->SetTexture(TextureName);
	}
}

void Logo::WizetAnimation()
{
	if (isNexonEnd == false)
	{
		return;
	}

	WizetWaitingCount += TimeCount;

	if (WizetWaitingCount >= 1.0f)
	{
		if(isWizetSet == false)
		{
			Wizet->SetTexture("Wizet.0.png");
			Wizet->GetTransform()->SetLocalScale({ 550, 420 });
			Wizet->GetTransform()->SetLocalPosition({ -125, 90 });
			isWizetSet = true;
		}

		WizetCount += TimeCount;

		if (WizetCount >= 0.1)
		{
			if (WizetIndex == 61)
			{
				isWizetEnd = true;
				return;
			}

			WizetIndex++;
			WizetCount = 0;

			std::string TextureName = "Wizet." + std::to_string(WizetIndex) + ".png";
			Wizet->SetTexture(TextureName);
		}	
	}

}

