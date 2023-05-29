#include "PrecompileHeader.h"
#include "StatusWindow.h"
#include "Mouse.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

StatusWindow::StatusWindow()
{
}

StatusWindow::~StatusWindow()
{
}

void StatusWindow::Start()
{
	SubWindow = CreateComponent<GameEngineUIRenderer>();
	SubWindow->SetScaleToTexture("SubStatusWindow.png");

	MainWindow = CreateComponent<GameEngineUIRenderer>();
	MainWindow->SetScaleToTexture("MainStatusWindow.png");

	TransformData Data = MainWindow->GetTransform()->GetTransDataRef();

	MainWindowClickBar = CreateComponent<GameEngineCollision>();
	MainWindowClickBar->GetTransform()->SetLocalScale({0,0});
	MainWindowClickBar->GetTransform()->SetLocalPosition({ Data.LocalPosition.x , Data.LocalScale.hy() - 22.0f });
	MainWindowClickBar->SetOrder(static_cast<int>(CollisionOrder::UI));

	MainWindow->GetTransform()->SetLocalPosition(float4{ -100, 0 });
	SubWindow->GetTransform()->SetLocalPosition(float4{ 75, -67 });

	MainWindowClickBar->GetTransform()->SetLocalPosition({ Data.LocalPosition.x, Data.LocalPosition.y + Data.LocalScale.hy() - 22.0f });
}

void StatusWindow::Update(float _DeltaTime)
{
	AllWindowUpdate();

}

void StatusWindow::Render(float _DeltaTime)
{
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