#include "PrecompileHeader.h"
#include "StatusWindow.h"
#include "Mouse.h"
#include "PlayerValue.h"
#include "ContentFontRenderer.h"
#include "ContentButton.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineButton.h>

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
	Exp->GetTransform()->SetLocalPosition({ -128, 27 });

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
	
	StatPoint = CreateComponent<ContentFontRenderer>();
	StatPoint->SetFont("±¼¸²");
	StatPoint->SetScale(11.0f);
	StatPoint->SetColor({ 0, 0, 0, 1 });
	StatPoint->GetTransform()->SetLocalPosition({ -123, -37 });
	
	StrBt = GetLevel()->CreateActor<ContentButton>();
	StrBt->SetReleaseTexture("StatUpRelease.png");
	StrBt->SetHoverTexture("StatUpHover.png");
	StrBt->SetPressTexture("StatUpPress.png");
	StrBt->GetTransform()->SetLocalScale({ 12, 12 });
	StrBt->GetTransform()->SetLocalPosition({ -30, -74 });

	DexBt = GetLevel()->CreateActor<ContentButton>();
	DexBt->SetReleaseTexture("StatUpRelease.png");
	DexBt->SetHoverTexture("StatUpHover.png");
	DexBt->SetPressTexture("StatUpPress.png");
	DexBt->GetTransform()->SetLocalScale({ 12, 12 });
	DexBt->GetTransform()->SetLocalPosition({ -30, -92 });

	IntBt = GetLevel()->CreateActor<ContentButton>();
	IntBt->SetReleaseTexture("StatUpRelease.png");
	IntBt->SetHoverTexture("StatUpHover.png");
	IntBt->SetPressTexture("StatUpPress.png");
	IntBt->GetTransform()->SetLocalScale({ 12, 12 });
	IntBt->GetTransform()->SetLocalPosition({ -30, -110 });

	LukBt = GetLevel()->CreateActor<ContentButton>();
	LukBt->SetReleaseTexture("StatUpRelease.png");
	LukBt->SetHoverTexture("StatUpHover.png");
	LukBt->SetPressTexture("StatUpPress.png");
	LukBt->GetTransform()->SetLocalScale({ 12, 12 });
	LukBt->GetTransform()->SetLocalPosition({ -30, -128 });

	AttRender = CreateComponent<ContentFontRenderer>();
	AttRender->SetFont("±¼¸²");
	AttRender->SetScale(11.0f);
	AttRender->SetColor({ 0, 0, 0, 1 });
	AttRender->GetTransform()->SetLocalPosition({ 62, 26 });
}

void StatusWindow::Update(float _DeltaTime)
{
	StatUpdate();
	ButtonUpdate();
}

void StatusWindow::Render(float _DeltaTime)
{

}

void StatusWindow::StatUpdate()
{
	PlayerValue* Value = PlayerValue::GetValue();	

	Hp->SetText(std::to_string(Value->GetHp()));
	Mp->SetText(std::to_string(Value->GetMp()));
	Level->SetText(std::to_string(Value->GetLevel()));
	Exp->SetText(std::to_string(Value->GetExp()));
	Str->SetText(std::to_string(Value->GetStr()));
	Dex->SetText(std::to_string(Value->GetDex()));
	Luk->SetText(std::to_string(Value->GetLuk()));
	Int->SetText(std::to_string(Value->GetInt()));
	StatPoint->SetText(std::to_string(Value->GetStatPoint()));

	std::string Text = std::to_string(static_cast<int>(Value->GetMinAtt()))+ " ~ " + std::to_string(static_cast<int>(Value->GetMaxAtt()));
	AttRender->SetText(Text);
}


void StatusWindow::ButtonUpdate()
{
	if (PlayerValue::GetValue()->GetStatPoint() <= 0)
	{
		StrBt->SetReleaseTexture("StatUpDisable.png");
		StrBt->SetHoverTexture("StatUpDisable.png");
		StrBt->SetPressTexture("StatUpDisable.png");

		StrBt->SetEvent(nullptr);
		StrBt->SetPressEvent(nullptr);

		DexBt->SetReleaseTexture("StatUpDisable.png");
		DexBt->SetHoverTexture("StatUpDisable.png");
		DexBt->SetPressTexture("StatUpDisable.png");
		
		DexBt->SetEvent(nullptr);
		DexBt->SetPressEvent(nullptr);

		IntBt->SetReleaseTexture("StatUpDisable.png");
		IntBt->SetHoverTexture("StatUpDisable.png");
		IntBt->SetPressTexture("StatUpDisable.png");
		
		IntBt->SetEvent(nullptr);
		IntBt->SetPressEvent(nullptr);

		LukBt->SetReleaseTexture("StatUpDisable.png");
		LukBt->SetHoverTexture("StatUpDisable.png");
		LukBt->SetPressTexture("StatUpDisable.png");
		
		LukBt->SetEvent(nullptr);
		LukBt->SetPressEvent(nullptr);
	}
	else
	{
		StrBt->SetReleaseTexture("StatUpRelease.png");
		StrBt->SetHoverTexture("StatUpHover.png");
		StrBt->SetPressTexture("StatUpPress.png");

		StrBt->SetEvent([this]
			{
				PlayerValue::GetValue()->AddStatPoint(-1);
				PlayerValue::GetValue()->AddStr(1);
				PlayerValue::GetValue()->AttUpdate();
			});
		StrBt->SetPressEvent([this]
			{
				PlayerValue::GetValue()->AddStatPoint(-1);
				PlayerValue::GetValue()->AddStr(1);
				PlayerValue::GetValue()->AttUpdate();
			});
		StrBt->SetPressInter(0.01f);
		StrBt->SetPressStartTime(1.0f);

		DexBt->SetReleaseTexture("StatUpRelease.png");
		DexBt->SetHoverTexture("StatUpHover.png");
		DexBt->SetPressTexture("StatUpPress.png");
		
		DexBt->SetEvent([this]
			{
				PlayerValue::GetValue()->AddStatPoint(-1);
				PlayerValue::GetValue()->AddDex(1);
				PlayerValue::GetValue()->AttUpdate();
			});
		DexBt->SetPressEvent([this]
			{
				PlayerValue::GetValue()->AddStatPoint(-1);
				PlayerValue::GetValue()->AddDex(1);
				PlayerValue::GetValue()->AttUpdate();
			});
		DexBt->SetPressInter(0.01f);
		DexBt->SetPressStartTime(1.0f);

		IntBt->SetReleaseTexture("StatUpRelease.png");
		IntBt->SetHoverTexture("StatUpHover.png");
		IntBt->SetPressTexture("StatUpPress.png");
		
		IntBt->SetEvent([this]
			{
				PlayerValue::GetValue()->AddStatPoint(-1);
				PlayerValue::GetValue()->AddInt(1);
				PlayerValue::GetValue()->AttUpdate();
			});
		IntBt->SetPressEvent([this]
			{
				PlayerValue::GetValue()->AddStatPoint(-1);
				PlayerValue::GetValue()->AddInt(1);
				PlayerValue::GetValue()->AttUpdate();
			});
		IntBt->SetPressInter(0.01f);
		IntBt->SetPressStartTime(1.0f);

		LukBt->SetReleaseTexture("StatUpRelease.png");
		LukBt->SetHoverTexture("StatUpHover.png");
		LukBt->SetPressTexture("StatUpPress.png");
		
		LukBt->SetEvent([this]
			{
				PlayerValue::GetValue()->AddStatPoint(-1);
				PlayerValue::GetValue()->AddLuk(1);
				PlayerValue::GetValue()->AttUpdate();
			});
		LukBt->SetPressEvent([this]
			{
				PlayerValue::GetValue()->AddStatPoint(-1);
				PlayerValue::GetValue()->AddLuk(1);
				PlayerValue::GetValue()->AttUpdate();
			});
		LukBt->SetPressInter(0.01f);
		LukBt->SetPressStartTime(1.0f);

	}


}

void StatusWindow::ButtonDeath()
{
	if (StrBt != nullptr)
	{
		StrBt->Death();
	}

	if (DexBt != nullptr)
	{
		DexBt->Death();
	}

	if (IntBt != nullptr)
	{
		IntBt->Death();
	}

	if (LukBt != nullptr)
	{
		LukBt->Death();
	}
}