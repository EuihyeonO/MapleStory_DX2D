#include "PrecompileHeader.h"
#include "AlterOfZakumEnt.h"
#include "ContentRenderer.h"

#include <GameEngineBase/GameEngineRandom.h>

AlterOfZakumEnt::AlterOfZakumEnt()
{
}

AlterOfZakumEnt::~AlterOfZakumEnt()
{
}

void AlterOfZakumEnt::Start()
{
	Map = CreateComponent<GameEngineSpriteRenderer>();
	Map->SetScaleToTexture("AlterOfZakumEnt.png");

	BackGround = CreateComponent<ContentRenderer>();
	BackGround->SetTexture("ZakumLandScape0.png");
	BackGround->GetTransform()->SetLocalScale({ 200 * 14, 600 });
	BackGround->GetTransform()->SetLocalPosition({ 0, 0, 1 });
	BackGround->SetUVconstant({ 0, 0, 14, 1 });

	Layer = CreateComponent<GameEngineSpriteRenderer>();
	Layer->SetScaleToTexture("AlterOfZakumEntLayer.png");
	Layer->GetTransform()->SetLocalPosition({ 0, -15, -100 });

	Magma = CreateComponent<ContentRenderer>();
	Magma->SetTexture("Magma.png");
	Magma->GetTransform()->SetLocalScale({ 264 * 11, 96 });
	Magma->GetTransform()->SetLocalPosition({ 0, -250, -115 });
	Magma->SetUVconstant({ 0, 0, 11, 1 });

	SetFireDewDrop();
}

void AlterOfZakumEnt::Update(float _DeltaTime)
{
	XUVCount += 0.05f * _DeltaTime;
	
	if (XUVCount >= 1.0f)
	{
		XUVCount -= 1.0f;
	}

	Magma->SetUVconstant({ XUVCount, 0, 11, 1 });

	FireDewDrop();
}

void AlterOfZakumEnt::Render(float _DeltaTime)
{

}

void AlterOfZakumEnt::SetFireDewDrop()
{
	int i = 0;
	for (i = 0; i < 20; i++)
	{
		std::weak_ptr<GameEngineSpriteRenderer> FireDew = CreateComponent<GameEngineSpriteRenderer>();
		FireDew.lock()->CreateAnimation({ .AnimationName = "DewDrop",.SpriteName = "FireDewDrop",.FrameInter = 0.08,.Loop = false,.ScaleToTexture = true });
		FireDew.lock()->GetTransform()->SetLocalPosition({ -1150 + i * 120.0f, -175, -200 });
		FireDew.lock()->SetAnimationUpdateEvent("DewDrop", 9, [= ,this]
			{
				if(FireDew.lock()->IsAnimationEnd() == true)
				{
					FireDewDropList[i].first = false;
					FireDewDropList[i].second->Off();
				}
			});

		FireDewDropList.push_back({ false, FireDew.lock()});
	}
}

void AlterOfZakumEnt::FireDewDrop()
{
	TimeCounting();

	DewDropCount += TimeCount;

	if (DewDropCount >= 0.3f)
	{
		DewDropCount = 0.0f;

		int Index = GameEngineRandom::MainRandom.RandomInt(0, 19);

		if (FireDewDropList[Index].first != true)
		{
			FireDewDropList[Index].first = true;
			FireDewDropList[Index].second->On();
			FireDewDropList[Index].second->ChangeAnimation("DewDrop");
		}
	}
	
}