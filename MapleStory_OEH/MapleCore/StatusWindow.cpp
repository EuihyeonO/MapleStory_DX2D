#include "PrecompileHeader.h"
#include "StatusWindow.h"
#include "Mouse.h"
#include "PlayerValue.h"
#include "ContentFontRenderer.h"

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

	MainWindow->GetTransform()->SetLocalPosition(float4{ -100, 0});
	SubWindow->GetTransform()->SetLocalPosition(float4{ 75, -67 });

	MainWindowClickBar->GetTransform()->SetLocalPosition({ Data.LocalPosition.x, Data.LocalPosition.y + Data.LocalScale.hy() - 22.0f });

	Level = CreateComponent<ContentFontRenderer>();
	Level->SetFont("±¼¸²");
	Level->SetScale(11.0f);
	Level->SetColor({ 0, 0, 0, 1 });
	Level->GetTransform()->SetLocalPosition({ -128, 100 });
	
	Hp = CreateComponent<ContentFontRenderer>();
	Hp->SetFont("±¼¸²");
	Hp->SetScale(11.0f);
	Hp->SetColor({ 0, 0, 0, 1 });
	Hp->GetTransform()->SetLocalPosition({ -128, 63 });

	Mp = CreateComponent<ContentFontRenderer>();
	Mp->SetFont("±¼¸²");
	Mp->SetScale(11.0f);
	Mp->SetColor({ 0, 0, 0, 1 });
	Mp->GetTransform()->SetLocalPosition({ -128, 45 });

	Exp = CreateComponent<ContentFontRenderer>();
	Exp->SetFont("±¼¸²");
	Exp->SetScale(11.0f);
	Exp->SetColor({ 0, 0, 0, 1 });
	Exp->GetTransform()->SetLocalPosition({ -128, 26 });

	Str = CreateComponent<ContentFontRenderer>();
	Str->SetFont("±¼¸²");
	Str->SetScale(11.0f);
	Str->SetColor({ 0, 0, 0, 1 });
	Str->GetTransform()->SetLocalPosition({ -128, -66 });

	Dex = CreateComponent<ContentFontRenderer>();
	Dex->SetFont("±¼¸²");
	Dex->SetScale(11.0f);
	Dex->SetColor({ 0, 0, 0, 1 });
	Dex->GetTransform()->SetLocalPosition({ -128, -84 });

	Int = CreateComponent<ContentFontRenderer>();
	Int->SetFont("±¼¸²");
	Int->SetScale(11.0f);
	Int->SetColor({ 0, 0, 0, 1 });
	Int->GetTransform()->SetLocalPosition({ -128, -102 });

	Luk = CreateComponent<ContentFontRenderer>();
	Luk->SetFont("±¼¸²");
	Luk->SetScale(11.0f);
	Luk->SetColor({ 0, 0, 0, 1 });
	Luk->GetTransform()->SetLocalPosition({ -128, -120 });
}

void StatusWindow::Update(float _DeltaTime)
{
	StatUpdate();
}

void StatusWindow::Render(float _DeltaTime)
{
}

void StatusWindow::StatUpdate()
{
	Hp->SetText(std::to_string(PlayerValue::GetValue()->GetHp()));
	Mp->SetText(std::to_string(PlayerValue::GetValue()->GetMp()));
	Level->SetText(std::to_string(PlayerValue::GetValue()->GetLevel()));
	Exp->SetText(std::to_string(PlayerValue::GetValue()->GetExp()));
	Str->SetText(std::to_string(PlayerValue::GetValue()->GetStr()));
	Dex->SetText(std::to_string(PlayerValue::GetValue()->GetDex()));
	Luk->SetText(std::to_string(PlayerValue::GetValue()->GetLuk()));
	Int->SetText(std::to_string(PlayerValue::GetValue()->GetInt()));
}
