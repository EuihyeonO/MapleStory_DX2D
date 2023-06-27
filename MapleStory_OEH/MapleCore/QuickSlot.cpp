#include "PrecompileHeader.h"
#include "QuickSlot.h"
#include "UIController.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

QuickSlot::QuickSlot()
{
}

QuickSlot::~QuickSlot()
{
}

void QuickSlot::Start()
{
	UIController::GetUIController()->SetCurQuickSlot(DynamicThis<QuickSlot>());

	QuickSlotRender = CreateComponent<GameEngineUIRenderer>();
	QuickSlotRender->SetScaleToTexture("QuickSlot.png");


	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	float4 QuickSlotScale = QuickSlotRender->GetTransform()->GetLocalScale();

	QuickSlotRender->GetTransform()->SetLocalPosition(float4{ ScreenSize.hx(), -ScreenSize.hy() } - float4{ QuickSlotScale.hx(), -QuickSlotScale.hy() });
	QuickSlotRender->GetTransform()->AddLocalPosition({ 0, 66 });

	QuickSlotLayer = CreateComponent<GameEngineUIRenderer>();
	QuickSlotLayer->SetScaleToTexture("QuickSlotLayer.png");

	QuickSlotLayer->GetTransform()->SetLocalPosition(QuickSlotRender->GetTransform()->GetLocalPosition() + float4{0, 0, -1});

	ShiftSlot = CreateComponent<GameEngineCollision>();
	ShiftSlot->SetOrder(static_cast<int>(CollisionOrder::QuickSlotSkill));
	ShiftSlot->GetTransform()->SetLocalScale({ 32, 32 });
	ShiftSlot->GetTransform()->SetLocalPosition(QuickSlotRender->GetTransform()->GetLocalPosition() + float4{ -52, 17 });

	ShiftSkill = CreateComponent<GameEngineUIRenderer>();
	ShiftSkill->SetOrder(static_cast<int>(CollisionOrder::QuickSlotSkill));
	ShiftSkill->GetTransform()->SetLocalPosition(QuickSlotRender->GetTransform()->GetLocalPosition() + float4{ -52, 17 });
	ShiftSkill->Off();

	InsSlot = CreateComponent<GameEngineCollision>();
	InsSlot->SetOrder(static_cast<int>(CollisionOrder::QuickSlotSkill));
	InsSlot->GetTransform()->SetLocalScale({ 32, 32 });
	InsSlot->GetTransform()->SetLocalPosition(QuickSlotRender->GetTransform()->GetLocalPosition() + float4{ -17, 17 });

	InsSkill = CreateComponent<GameEngineUIRenderer>();
	InsSkill->SetOrder(static_cast<int>(CollisionOrder::QuickSlotSkill));
	InsSkill->GetTransform()->SetLocalPosition(QuickSlotRender->GetTransform()->GetLocalPosition() + float4{ -17, 17 });
	InsSkill->Off();

	HomeSlot = CreateComponent<GameEngineCollision>();
	HomeSlot->SetOrder(static_cast<int>(CollisionOrder::QuickSlotSkill));
	HomeSlot->GetTransform()->SetLocalScale({ 32, 32 });
	HomeSlot->GetTransform()->SetLocalPosition(QuickSlotRender->GetTransform()->GetLocalPosition() + float4{ 18, 17 });

	HomeSkill = CreateComponent<GameEngineUIRenderer>();
	HomeSkill->SetOrder(static_cast<int>(CollisionOrder::QuickSlotSkill));
	HomeSkill->GetTransform()->SetLocalPosition(QuickSlotRender->GetTransform()->GetLocalPosition() + float4{ 18, 17 });
	HomeSkill->Off();

	PgUpSlot = CreateComponent<GameEngineCollision>();
	PgUpSlot->SetOrder(static_cast<int>(CollisionOrder::QuickSlotSkill));
	PgUpSlot->GetTransform()->SetLocalScale({ 32, 32 });
	PgUpSlot->GetTransform()->SetLocalPosition(QuickSlotRender->GetTransform()->GetLocalPosition() + float4{ 53, 17 });

	PgUpSkill = CreateComponent<GameEngineUIRenderer>();
	PgUpSkill->SetOrder(static_cast<int>(CollisionOrder::QuickSlotSkill));
	PgUpSkill->GetTransform()->SetLocalPosition(QuickSlotRender->GetTransform()->GetLocalPosition() + float4{ 53, 17 });
	PgUpSkill->Off();

	CtrlSlot = CreateComponent<GameEngineCollision>();
	CtrlSlot->SetOrder(static_cast<int>(CollisionOrder::QuickSlotSkill));
	CtrlSlot->GetTransform()->SetLocalScale({ 32, 32 });
	CtrlSlot->GetTransform()->SetLocalPosition(QuickSlotRender->GetTransform()->GetLocalPosition() + float4{ -52, -17 });
	
	CtrlSkill = CreateComponent<GameEngineUIRenderer>();
	CtrlSkill->SetOrder(static_cast<int>(CollisionOrder::QuickSlotSkill));
	CtrlSkill->GetTransform()->SetLocalPosition(QuickSlotRender->GetTransform()->GetLocalPosition() + float4{ -52, -17 });
	CtrlSkill->Off();

	DelSlot = CreateComponent<GameEngineCollision>();
	DelSlot->SetOrder(static_cast<int>(CollisionOrder::QuickSlotSkill));
	DelSlot->GetTransform()->SetLocalScale({ 32, 32 });
	DelSlot->GetTransform()->SetLocalPosition(QuickSlotRender->GetTransform()->GetLocalPosition() + float4{ -17, -17 });

	DelSkill = CreateComponent<GameEngineUIRenderer>();
	DelSkill->SetOrder(static_cast<int>(CollisionOrder::QuickSlotSkill));
	DelSkill->GetTransform()->SetLocalPosition(QuickSlotRender->GetTransform()->GetLocalPosition() + float4{ -17, -17 });
	DelSkill->Off();

	EndSlot = CreateComponent<GameEngineCollision>();
	EndSlot->SetOrder(static_cast<int>(CollisionOrder::QuickSlotSkill));
	EndSlot->GetTransform()->SetLocalScale({ 32, 32 });
	EndSlot->GetTransform()->SetLocalPosition(QuickSlotRender->GetTransform()->GetLocalPosition() + float4{ 18, -17 });

	EndSkill = CreateComponent<GameEngineUIRenderer>();
	EndSkill->SetOrder(static_cast<int>(CollisionOrder::QuickSlotSkill));
	EndSkill->GetTransform()->SetLocalPosition(QuickSlotRender->GetTransform()->GetLocalPosition() + float4{ 18, -17 });
	EndSkill->Off();

	PgDnSlot = CreateComponent<GameEngineCollision>();
	PgDnSlot->SetOrder(static_cast<int>(CollisionOrder::QuickSlotSkill));
	PgDnSlot->GetTransform()->SetLocalScale({ 32, 32 });
	PgDnSlot->GetTransform()->SetLocalPosition(QuickSlotRender->GetTransform()->GetLocalPosition() + float4{ 53, -17 });

	PgDnSkill = CreateComponent<GameEngineUIRenderer>();
	PgDnSkill->SetOrder(static_cast<int>(CollisionOrder::QuickSlotSkill));
	PgDnSkill->GetTransform()->SetLocalPosition(QuickSlotRender->GetTransform()->GetLocalPosition() + float4{ 53, -17 });
	PgDnSkill->Off();

	ColSlotSkill[DelSlot] = &UIController::SetDelSkill;
	ColSlotSkill[ShiftSlot] = &UIController::SetShiftSkill;
	ColSlotSkill[PgUpSlot] = &UIController::SetPgUpSkill;
	ColSlotSkill[InsSlot] = &UIController::SetInsSkill;
	ColSlotSkill[HomeSlot] = &UIController::SetHomeSkill;
	ColSlotSkill[CtrlSlot] = &UIController::SetCtrlSkill;
	ColSlotSkill[EndSlot] = &UIController::SetEndSkill;
	ColSlotSkill[PgDnSlot] = &UIController::SetPgDNSkill;

	CtrlSkill->On();
	CtrlSkill->SetScaleToTexture("BasicSwingIcon.png");

	UIController::GetUIController()->LoadQuickSlotSkill();
}

void QuickSlot::Update(float _DeltaTime) 
{
	ColPosUpdate();
}

void QuickSlot::Render(float _DeltaTime)
{

}

void QuickSlot::ColPosUpdate()
{
	float4 CamPos = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();
	float4 QuickSlotPos = QuickSlotRender->GetTransform()->GetLocalPosition();

	ShiftSlot->GetTransform()->SetLocalPosition(CamPos + QuickSlotPos + float4{ -52, 17 });
	InsSlot->GetTransform()->SetLocalPosition(CamPos + QuickSlotPos + float4{ -17, 17 });
	HomeSlot->GetTransform()->SetLocalPosition(CamPos + QuickSlotPos + float4{ 18, 17 });
	PgUpSlot->GetTransform()->SetLocalPosition(CamPos + QuickSlotPos + float4{ 53, 17 });
	CtrlSlot->GetTransform()->SetLocalPosition(CamPos + QuickSlotPos + float4{ -52, -17 });
	DelSlot->GetTransform()->SetLocalPosition(CamPos + QuickSlotPos + float4{ -17, -17 });
	EndSlot->GetTransform()->SetLocalPosition(CamPos + QuickSlotPos + float4{ 18, -17 });
	PgDnSlot->GetTransform()->SetLocalPosition(CamPos + QuickSlotPos + float4{ 53, -17 });
}