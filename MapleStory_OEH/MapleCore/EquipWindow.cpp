#include "PrecompileHeader.h"
#include "EquipWindow.h"
#include "EquipItemList.h"

#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

EquipWindow::EquipWindow()
{
}

EquipWindow::~EquipWindow()
{
}


void EquipWindow::Start()
{
	EquipWindowRender = CreateComponent<GameEngineUIRenderer>();
	EquipWindowRender->SetScaleToTexture("EquipWindow.png");

	GetTransform()->SetLocalPosition({ -200, 100 });

	MyEquipItemList = GetLevel()->CreateActor<EquipItemList>();
}

void EquipWindow::Update(float _DeltaTime) 
{

}

void EquipWindow::Render(float _DeltaTime)
{

}