#include "PrecompileHeader.h"
#include "QuickSlot.h"
#include "UIController.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

QuickSlot::QuickSlot()
{
}

QuickSlot::~QuickSlot()
{
}

void QuickSlot::Start()
{
	UIController::GetUIController()->AddQuickSlotToList(DynamicThis<QuickSlot>());

	QuickSlotRender = CreateComponent<GameEngineUIRenderer>();
	QuickSlotRender->SetScaleToTexture("QuickSlot.png");

	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	float4 QuickSlotScale = QuickSlotRender->GetTransform()->GetLocalScale();

	QuickSlotRender->GetTransform()->SetLocalPosition(float4{ ScreenSize.hx(), -ScreenSize.hy() } - float4{ QuickSlotScale.hx(), -QuickSlotScale.hy() });
	QuickSlotRender->GetTransform()->AddLocalPosition({ 0, 66 });


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

	//ColSlotSkill[DelSlot].first = &Player::SetDelSkill;
	//ColSlotSkill[DelSlot].second = DelSkill;
	//ColSlotSkill[ShiftSlot].first = &Player::SetShiftSkill;
	//ColSlotSkill[ShiftSlot].second = ShiftSkill;
	//ColSlotSkill[PgUpSlot].first = &Player::SetPgUpSkill;
	//ColSlotSkill[PgUpSlot].second = PgUpSkill;
	//ColSlotSkill[InsSlot].first = &Player::SetInsSkill;
	//ColSlotSkill[InsSlot].second = InsSkill;
	//ColSlotSkill[HomeSlot].first = &Player::SetHomeSkill;
	//ColSlotSkill[HomeSlot].second = HomeSkill;
	//ColSlotSkill[CtrlSlot].first = &Player::SetCtrlSkill;
	//ColSlotSkill[CtrlSlot].second = CtrlSkill;
	//ColSlotSkill[EndSlot].first = &Player::SetEndSkill;
	//ColSlotSkill[EndSlot].second = EndSkill;
	//ColSlotSkill[PgDnSlot].first = &Player::SetPgDnSkill;
	//ColSlotSkill[PgDnSlot].second = PgDnSkill;

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
}

void QuickSlot::Update(float _DeltaTime) 
{
}

void QuickSlot::Render(float _DeltaTime)
{

}