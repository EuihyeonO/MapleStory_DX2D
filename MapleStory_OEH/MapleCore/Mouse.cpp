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
	CursorCollision->GetTransform()->SetLocalScale({ 5 , 5 });
	CursorCollision->GetTransform()->SetLocalPosition({ -8, 10 });
	CursorCollision->SetColType(ColType::AABBBOX2D);

	TransformData Data = CursorCollision->GetTransform()->GetTransDataRef();
	
	ShowCursor(false);

	if (GameEngineInput::IsKey("LClick") == false)
	{
		GameEngineInput::CreateKey("LClick", VK_LBUTTON);
	}
}

void Mouse::Update(float _DeltaTime)
{
	PosUpdate();
	ClickUpdate();
}

void Mouse::Render(float _DeltaTime)
{
}

void Mouse::PosUpdate()
{
	float4 WindowSize = GameEngineWindow::GetScreenSize();
	float4 MousePos = GameEngineWindow::GetMousePosition();

	MousePos = { MousePos.x - WindowSize.hx(),  WindowSize.hy() - MousePos.y, -1000.0f};
	GetTransform()->SetLocalPosition(MousePos);
	CursorCollision->GetTransform()->SetWorldPosition(GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition() + float4{ -8, 10 } + MousePos);
}

void Mouse::ClickUpdate()
{
	TimeCounting();

	if (isDoubleClick == true)
	{
		//더블클릭은 한 프레임에 대해서만 유효
		isDoubleClick = false;
	}

	if (GameEngineInput::IsDown("LClick") == true)
	{
		if (isClick == true)
		{
			isDoubleClick = true;
			isClick = false;

			ClickCount = 0.0f;
		}
		else
		{
			isClick = true;
			ClickCount = 0.0f;
		}
	}

	if (isClick == true)
	{
		ClickCount += TimeCount;

		if (ClickCount > 0.3f)
		{
			isClick = false;
		}
	}

	if (isDoubleClick == true)
	{
		int a = 0;
	}
}