#include "PrecompileHeader.h"
#include "Mouse.h"
#include "ContentEnums.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <gameengineCore/GameEngineLevel.h>
#include <gameengineCore/GameEngineCamera.h>

Mouse* Mouse::CurMouse = nullptr;

Mouse::Mouse()
{
	CurMouse = this;
}

Mouse::~Mouse()
{
}

void Mouse::Start()
{
	Cursor = CreateComponent<GameEngineSpriteRenderer>();
	Cursor->SetScaleToTexture("Cursor.png");
	
	CursorCollision = CreateComponent<GameEngineCollision>();
	CursorCollision->SetOrder(static_cast<int>(CollisionOrder::Mouse));
	CursorCollision->GetTransform()->SetLocalPosition(Cursor->GetTransform()->GetLocalPosition());

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
	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();

	GetTransform()->SetLocalPosition(MousePos + CameraPos);
}