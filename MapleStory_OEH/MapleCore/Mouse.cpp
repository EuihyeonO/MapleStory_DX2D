#include "PrecompileHeader.h"
#include "Mouse.h"
#include "ContentEnums.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <gameengineCore/GameEngineLevel.h>
#include <gameengineCore/GameEngineCamera.h>
#include <gameengineCore/GameEngineUIRenderer.h>

std::shared_ptr<Mouse> Mouse::CurMouse = nullptr;

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
}

void Mouse::Start()
{

	Cursor = CreateComponent<GameEngineUIRenderer>();
	Cursor->SetScaleToTexture("Cursor.png");

	CursorCollision = CreateComponent<GameEngineCollision>();
	CursorCollision->SetOrder(static_cast<int>(CollisionOrder::Mouse));
	CursorCollision->GetTransform()->SetLocalScale({ 6,6 });
	CursorCollision->GetTransform()->SetLocalPosition({ -8, 10 });

	TransformData Data = CursorCollision->GetTransform()->GetTransDataRef();

	Test = CreateComponent<GameEngineUIRenderer>();
	Test->SetTexture("MouseTest.png");
	Test->GetTransform()->SetLocalScale(Data.LocalScale);
	Test->GetTransform()->SetLocalPosition(Data.LocalPosition);

	ShowCursor(false);

	if (GameEngineInput::IsKey("LClick") == false)
	{
		GameEngineInput::CreateKey("LClick", VK_LBUTTON);
	}
}

void Mouse::Update(float _DeltaTime)
{
	PosUpdate();
}

void Mouse::Render(float _DeltaTime)
{
}

void Mouse::PosUpdate()
{
	float4 WindowSize = GameEngineWindow::GetScreenSize();
	float4 MousePos = GameEngineWindow::GetMousePosition();

	MousePos = { MousePos.x - WindowSize.hx(),  WindowSize.hy() - MousePos.y };
	GetTransform()->SetLocalPosition(MousePos + float4{0, 0, 1});

}