#include "PrecompileHeader.h"
#include "ZakumRoad1.h"

ZakumRoad1::ZakumRoad1()
{
}

ZakumRoad1::~ZakumRoad1()
{
}

void ZakumRoad1::Start()
{
	BackGround = CreateComponent<GameEngineSpriteRenderer>();
	BackGround->SetScaleToTexture("ZakumRoad1BackGround.png");

	Tile = CreateComponent<GameEngineSpriteRenderer>();
	Tile->SetScaleToTexture("ZakumRoad1.png");

}

void ZakumRoad1::Update(float _DeltaTime) 
{

}

void ZakumRoad1::Render(float _DeltaTime) 
{

}
