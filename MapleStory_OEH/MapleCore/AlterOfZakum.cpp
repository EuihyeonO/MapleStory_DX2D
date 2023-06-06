#include "PrecompileHeader.h"
#include "AlterOfZakum.h"

#include "ContentRenderer.h"

AlterOfZakum::AlterOfZakum()
{
}

AlterOfZakum::~AlterOfZakum()
{
}

void AlterOfZakum::Start()
{
	LandScape0 = CreateComponent<ContentRenderer>();
	LandScape0->SetTexture("ZakumLandScape0.png");
	LandScape0->GetTransform()->SetLocalScale({ 200 * 6, 600 });
	LandScape0->SetUVconstant({ 0, 0, 6, 1 });

	LandScape1 = CreateComponent<GameEngineSpriteRenderer>();
	LandScape1->SetScaleToTexture("ZakumLandScape1.png");
	LandScape1->GetTransform()->SetLocalPosition({ -300, 0 });
	LandScape1->ColorOptionValue.MulColor = { 1.0f, 1.0f, 1.0f, 0.7f };

	LandScape2 = CreateComponent<GameEngineSpriteRenderer>();
	LandScape2->SetScaleToTexture("ZakumLandScape1.png");
	LandScape2->GetTransform()->SetLocalPosition({ 300, 0 });
	LandScape2->ColorOptionValue.MulColor = { 1.0f, 1.0f, 1.0f, 0.7f };

	Layer = CreateComponent<GameEngineSpriteRenderer>();
	Layer->SetScaleToTexture("ZakumLayer.png");

	Magma = CreateComponent<ContentRenderer>();
	Magma->SetTexture("Magma.png");
	Magma->GetTransform()->SetLocalScale({ 264 * 5, 96 });
	Magma->GetTransform()->SetLocalPosition({ 0, -220 });
	Magma->SetUVconstant({ 0, 0, 5, 1 });

}

void AlterOfZakum::Update(float _DeltaTime) 
{
	Magma_UVXMove += 0.025f * _DeltaTime;
	
	if (Magma_UVXMove >= 5)
	{
		Magma_UVXMove -= 5.0f;
	}

	Magma->SetUVconstant({ Magma_UVXMove, 0, 5, 1 });
}

void AlterOfZakum::Render(float _DeltaTime)
{
}