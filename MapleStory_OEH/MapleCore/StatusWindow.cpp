#include "PrecompileHeader.h"
#include "StatusWindow.h"
#include "Mouse.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCamera.h>

StatusWindow::StatusWindow()
{
}

StatusWindow::~StatusWindow()
{
}

void StatusWindow::Start()
{
	CreateInputKey();

	MainWindow = CreateComponent<GameEngineSpriteRenderer>();
	MainWindow->SetScaleToTexture("MainStatusWindow.png");
	MainWindow->Off();

	TransformData Data = MainWindow->GetTransform()->GetTransDataRef();

	MainWindowClickBar = CreateComponent<GameEngineCollision>();
	MainWindowClickBar->GetTransform()->SetLocalScale({0,0});
	MainWindowClickBar->GetTransform()->SetLocalPosition({ Data.LocalPosition.x , Data.LocalScale.hy() - 22.0f });
	MainWindowClickBar->SetOrder(static_cast<int>(CollisionOrder::UI));

	SubWindow = CreateComponent<GameEngineSpriteRenderer>();
	SubWindow->SetScaleToTexture("SubStatusWindow.png");
	SubWindow->Off();
}

void StatusWindow::Update(float _DeltaTime)
{
	GetKetInput();
	AllWindowUpdate();

}

void StatusWindow::Render(float _DeltaTime)
{
}

void StatusWindow::WindowOn()
{
	MainWindow->On();
	SubWindow->On();

	TransformData Data = MainWindow->GetTransform()->GetTransDataRef();
	MainWindowClickBar->GetTransform()->SetLocalScale({ Data.LocalScale.x, 22.0f });
	PosUpdate();
}

void StatusWindow::WindowOff()
{
	MainWindow->Off();
	SubWindow->Off();
	MainWindowClickBar->GetTransform()->SetLocalScale({ 0,0,0 });
}

bool StatusWindow::WindowOnOff()
{
	if (MainWindow->IsUpdate() == true)
	{
		WindowOff();
		TransformData Data = MainWindowClickBar->GetTransform()->GetTransDataRef();
		return true;
	}
	else
	{
		WindowOn();
		UpdateFunction.push_back(&StatusWindow::PosUpdate);
		return true;
	}
}

bool StatusWindow::PosUpdate()
{
	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();
	MainWindow->GetTransform()->SetLocalPosition(CameraPos - float4{ 100, 0 });
	SubWindow->GetTransform()->SetLocalPosition(CameraPos + float4{ 75, -67 });
	
	TransformData Data = MainWindow->GetTransform()->GetTransDataRef();
	MainWindowClickBar->GetTransform()->SetLocalPosition({ Data.LocalPosition.x, Data.LocalPosition.y + Data.LocalScale.hy() - 22.0f });

	if (MainWindow->IsUpdate() == true)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void StatusWindow::CreateInputKey()
{
	if (GameEngineInput::IsKey("StatWindowOpen") == false)
	{
		GameEngineInput::CreateKey("StatWindowOpen", 'S');
	}
}

void StatusWindow::GetKetInput()
{
	if (GameEngineInput::IsDown("StatWindowOpen") == true)
	{
		UpdateFunction.push_back(&StatusWindow::WindowOnOff);
	}

	else if (GameEngineInput::IsDown("LClick") == true)
	{
		//좌표 및 기타 수치 수정해야함
		if (nullptr != MainWindowClickBar->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D))
		{
			MainWindow->GetTransform()->SetParent(Mouse::GetMouse()->GetTransform());
		}
		else
		{
			MainWindow->GetTransform()->SetParent(GetTransform());
		}
	}
}

void StatusWindow::AllWindowUpdate()
{

	if (UpdateFunction.size() == 0)
	{
		return;
	}

	std::list<std::function<bool(StatusWindow&)>>::iterator StartIter = UpdateFunction.begin();
	std::list<std::function<bool(StatusWindow&)>>::iterator EndIter = UpdateFunction.end();

	for (; StartIter != EndIter; )
	{
		std::function<bool(StatusWindow&)> Func = *StartIter;
		bool IsEnd = Func(*this);

		if (IsEnd == true)
		{
			StartIter = UpdateFunction.erase(StartIter);
			continue;
		}

		StartIter++;
	}
}