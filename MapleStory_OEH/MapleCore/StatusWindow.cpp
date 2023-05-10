#include "PrecompileHeader.h"
#include "StatusWindow.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
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

	PosUpdate();
}

void StatusWindow::WindowOff()
{
	MainWindow->Off();
	SubWindow->Off();
}

bool StatusWindow::WindowOnOff()
{
	if (MainWindow->IsUpdate() == true)
	{
		WindowOff();
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