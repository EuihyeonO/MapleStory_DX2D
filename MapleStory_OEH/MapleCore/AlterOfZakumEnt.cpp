#include "PrecompileHeader.h"
#include "AlterOfZakumEnt.h"
#include "Adovis.h"
#include "ContentRenderer.h"
#include "Portal.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>

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
	BackGround->GetTransform()->SetLocalPosition({ 0, 0, 3 });
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

	for (int i = 0; i < 7; i++)
	{
		int Num = i % 2 + 1;

		std::shared_ptr<GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>();
		Renderer->SetScaleToTexture("ZakumLandScape" + std::to_string(Num) + ".png");
		Renderer->GetTransform()->SetLocalPosition({ -1200 + 400.0f * i , 0, 2 });

		Num += 2;

		std::shared_ptr<GameEngineSpriteRenderer> Renderer1 = CreateComponent<GameEngineSpriteRenderer>();
		Renderer1->SetScaleToTexture("ZakumLandScape" + std::to_string(Num) + ".png");
		Renderer1->GetTransform()->SetLocalPosition({ -1400 + 400.0f * i , 0, 1 });
	}

	MyAdovis = GetLevel()->CreateActor<Adovis>();
	MyAdovis->GetTransform()->SetLocalPosition({ 1000, -168, -5 });

	Portal1 = GetLevel()->CreateActor<Portal>();
	Portal1->SetLinkedMap("Level_AlterOfZakum");
	Portal1->GetTransform()->SetLocalPosition({ 1170, -90, -100 });

	Black = CreateComponent<GameEngineUIRenderer>();
	Black->GetTransform()->SetWorldScale({ 800, 600 });
	Black->GetTransform()->SetWorldPosition({ 0, 0 });
	Black->ColorOptionValue.MulColor = { 0.0f, 0.0f, 0.0f, 1.0f };

	FadeInUpdate = &AlterOfZakumEnt::FadeIn;
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

	if (FadeInUpdate != nullptr)
	{
		FadeInUpdate(*this, _DeltaTime);
	}
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
		FireDew.lock()->CreateAnimation({ .AnimationName = "DewDrop",.SpriteName = "FireDewDrop",.FrameInter = 0.08f,.Loop = false,.ScaleToTexture = true });
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

void AlterOfZakumEnt::FadeIn(float _DeltaTime)
{
	Black->ColorOptionValue.MulColor.a -= 1.0F * _DeltaTime;

	if (Black->ColorOptionValue.MulColor.a <= 0)
	{
		Black->Death();
		Black = nullptr;
		FadeInUpdate = nullptr;
	}
}

void AlterOfZakumEnt::ActorDeath()
{
	if (MyAdovis != nullptr)
	{
		MyAdovis->ActorDeath();
		MyAdovis->Death();
		MyAdovis = nullptr;
	}
}