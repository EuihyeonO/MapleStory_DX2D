#include "PrecompileHeader.h"
#include "BottomBar.h"
#include "PlayerValue.h"
#include "ContentFontRenderer.h"
#include "ContentUIRenderer.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

BottomBar::BottomBar()
{
}

BottomBar::~BottomBar()
{
}

void BottomBar::Start()
{

	BottomBarBackGround = CreateComponent<GameEngineUIRenderer>();
	BottomBarBackGround->SetScaleToTexture("BottomBarBackGround.png");

	BottomBarLayer = CreateComponent<GameEngineUIRenderer>();
	BottomBarLayer->SetScaleToTexture("BottomBarLayer.png");

	StatusBar = CreateComponent<GameEngineUIRenderer>();
	StatusBar->SetScaleToTexture("StatusBar.png");

	HpGradation = CreateComponent<GameEngineUIRenderer>();
	HpGradation->SetScaleToTexture("StatusGradation.png");

	MpGradation = CreateComponent<GameEngineUIRenderer>();
	MpGradation->SetScaleToTexture("StatusGradation.png");

	ExpGradation = CreateComponent<GameEngineUIRenderer>();
	ExpGradation->SetTexture("StatusGradation.png");

	StatusBarLayer = CreateComponent<GameEngineUIRenderer>();
	StatusBarLayer->SetScaleToTexture("StatusBarLayer.png");

	LevelRenderer.reserve(4);

	HpFont = CreateComponent<ContentFontRenderer>();
	HpFont->SetFont("굴림");
	HpFont->SetColor({ 1, 1, 1, 1 });
	HpFont->SetScale(11.0f);
	HpFont->GetTransform()->SetLocalPosition({ -165, -267 });

	MpFont = CreateComponent<ContentFontRenderer>();
	MpFont->SetFont("굴림");
	MpFont->SetColor({ 1, 1, 1, 1 });
	MpFont->SetScale(11.0f); 
	MpFont->GetTransform()->SetLocalPosition({ -54, -267 });

	ExpFont = CreateComponent<ContentFontRenderer>();
	ExpFont->SetFont("굴림");
	ExpFont->SetColor({ 1, 1, 1, 1 });
	ExpFont->SetScale(11.0f);
	ExpFont->GetTransform()->SetLocalPosition({ 63, -267 });

	CashShop = CreateComponent<ContentUIRenderer>();
	CashShop->SetTexture("CashShop.png");
	CashShop->GetTransform()->SetLocalScale({ 73, 34 });

	Menu = CreateComponent<ContentUIRenderer>();
	Menu->SetTexture("Menu.png");
	Menu->GetTransform()->SetLocalScale({ 73, 34 });

	ShortCut = CreateComponent<ContentUIRenderer>();
	ShortCut->SetTexture("ShortCut.png");
	ShortCut->GetTransform()->SetLocalScale({ 73, 34 });

	ClassFont = CreateComponent<ContentFontRenderer>();
	ClassFont->SetFont("굴림");
	ClassFont->SetColor({ 1, 1, 1, 1 });
	ClassFont->SetScale(13.0f);
	ClassFont->GetTransform()->SetLocalPosition({ -315, -266 });

	NameFont = CreateComponent<ContentFontRenderer>();
	NameFont->SetFont("굴림");
	NameFont->SetColor({ 1, 1, 1, 1 });
	NameFont->SetScale(13.0f);
	NameFont->GetTransform()->SetLocalPosition({ -315, -282 });
	NameFont->SetText("EuiHyeon");

	RenderHP = PlayerValue::GetValue()->GetHp() - 1;
	RenderHP_flt = static_cast<float>(RenderHP);

	RenderMP = PlayerValue::GetValue()->GetMp() - 1;
	RenderMP_flt = static_cast<float>(RenderMP);

	BottomBarPosUpdate();	
}

void BottomBar::Update(float _DeltaTime) 
{
	GradationUpdate(_DeltaTime);
	LevelUpdate();
	HPAndMPUpdate();

	ClassFont->SetText(PlayerValue::GetValue()->GetClassKr());
}

void BottomBar::Render(float _DeltaTime) 
{

}

void BottomBar::BottomBarPosUpdate()
{
	float4 GameEngineWindowScale = GameEngineWindow::GetScreenSize();

	BottomBarBackGround->GetTransform()->SetLocalPosition({ 0, - GameEngineWindowScale.hy() + 35 });

	float4 BottomBarBackGroundPos = BottomBarBackGround->GetTransform()->GetLocalPosition();
	BottomBarLayer->GetTransform()->SetLocalPosition(BottomBarBackGroundPos + float4{ -GameEngineWindowScale.hx() + 285, 0 });

	float4 BottomBarLayerPos = BottomBarLayer->GetTransform()->GetLocalPosition();
	StatusBar->GetTransform()->SetLocalPosition(BottomBarLayerPos + float4{ 100, -17.5f });

	float4 StatusBarPos = StatusBar->GetTransform()->GetLocalPosition();
	StatusBarLayer->GetTransform()->SetLocalPosition(StatusBarPos);

	CashShop->GetTransform()->SetLocalPosition(BottomBarBackGroundPos + float4{ 209, -18 });
	Menu->GetTransform()->SetLocalPosition(BottomBarBackGroundPos + float4{ 284, -18 });
	ShortCut->GetTransform()->SetLocalPosition(BottomBarBackGroundPos + float4{ 359, -18 });

	std::shared_ptr<ContentUIRenderer> NewRed = CreateComponent<ContentUIRenderer>();
	NewRed->SetScaleToTexture("report_Post_Box.png");
	NewRed->GetTransform()->SetLocalPosition(BottomBarBackGroundPos + float4{ 191, 17 });

	std::shared_ptr<ContentUIRenderer> NewRed1 = CreateComponent<ContentUIRenderer>();
	NewRed1->SetScaleToTexture("EquipKey.png");
	NewRed1->GetTransform()->SetLocalPosition(BottomBarBackGroundPos + float4{ 230, 17 });
	std::shared_ptr<ContentUIRenderer> NewRed2 = CreateComponent<ContentUIRenderer>();
	NewRed2->SetScaleToTexture("InvenKey.png");
	NewRed2->GetTransform()->SetLocalPosition(BottomBarBackGroundPos + float4{ 260, 17 });
	std::shared_ptr<ContentUIRenderer> NewRed3 = CreateComponent<ContentUIRenderer>();
	NewRed3->SetScaleToTexture("StatKey.png");
	NewRed3->GetTransform()->SetLocalPosition(BottomBarBackGroundPos + float4{ 290, 17 });
	std::shared_ptr<ContentUIRenderer> NewRed4 = CreateComponent<ContentUIRenderer>();
	NewRed4->SetScaleToTexture("SkillKey.png");
	NewRed4->GetTransform()->SetLocalPosition(BottomBarBackGroundPos + float4{ 320, 17 });
	std::shared_ptr<ContentUIRenderer> NewRed5 = CreateComponent<ContentUIRenderer>();
	NewRed5->SetScaleToTexture("KeySet.png");
	NewRed5->GetTransform()->SetLocalPosition(BottomBarBackGroundPos + float4{ 350, 17 });
	std::shared_ptr<ContentUIRenderer> NewRed6 = CreateComponent<ContentUIRenderer>();
	NewRed6->SetScaleToTexture("QuickSlotKey.png");
	NewRed6->GetTransform()->SetLocalPosition(BottomBarBackGroundPos + float4{ 380, 17 });

	std::shared_ptr<ContentUIRenderer> NewRed7 = CreateComponent<ContentUIRenderer>();
	NewRed7->SetTexture("Chat.png");
	NewRed7->GetTransform()->SetLocalPosition(BottomBarLayerPos + float4{ -3, 17 });
	NewRed7->GetTransform()->SetLocalScale({566, 24});
	NewRed7->SetMulColor({0.f, 0.0f, 0.0f, 0.4f});

	std::shared_ptr<ContentUIRenderer> Up = CreateComponent<ContentUIRenderer>();
	Up->SetScaleToTexture("ChatUpBt.png");
	Up->GetTransform()->SetLocalPosition(BottomBarLayerPos + float4{ -3, 17 } + float4{276, 6});

	std::shared_ptr<ContentUIRenderer> Down = CreateComponent<ContentUIRenderer>();
	Down->SetScaleToTexture("ChatDownBt.png");
	Down->GetTransform()->SetLocalPosition(BottomBarLayerPos + float4{ -3, 17 } + float4{ 276, -6 });
}

void BottomBar::GradationUpdate(float _DeltaTime)
{
	float4 StatusBarPos = StatusBar->GetTransform()->GetLocalPosition();

	ExpBarRightPos = StatusBarPos + float4{ 167.0f, -8.0f };
	HpBarRightPos = ExpBarRightPos - float4{ 230.0f , 0.0f };
	MpBarRightPos = HpBarRightPos + float4{ 108.0f , 0.0f };

	int RealHp = PlayerValue::GetValue()->GetHp();
	int MaxHp = PlayerValue::GetValue()->GetMaxHp();
	
	//Hp
	if (RealHp != RenderHP)
	{
		if(RealHp > RenderHP)
		{
			RenderHP_flt += MaxHp * 2.0f * _DeltaTime;
			RenderHP = static_cast<int>(RenderHP_flt);

			if (RenderHP >= RealHp)
			{
				RenderHP_flt = static_cast<float>(RealHp);
				RenderHP = RealHp;
			}
		}
		else
		{
			RenderHP_flt -= MaxHp * 2.0f * _DeltaTime;
			RenderHP = static_cast<int>(RenderHP_flt);

			if (RenderHP <= RealHp)
			{
				RenderHP_flt = static_cast<float>(RealHp);
				RenderHP = RealHp;
			}
		}

		float RenderHPRate = 0.0f;

		if(RealHp >= 0)
		{
			RenderHPRate = static_cast<float>(RenderHP) / static_cast<float>(MaxHp);
		}
		else
		{
			RenderHPRate = 0.0f;
		}

		float HpRateScale = 1 - RenderHPRate;
		float HpGradationXScale = 106.0f * HpRateScale;

		HpGradation->GetTransform()->SetLocalScale({ HpGradationXScale , 16.0f });
		HpGradation->GetTransform()->SetLocalPosition(HpBarRightPos - float4{ HpGradationXScale / 2.0f, 0.0f });
	}

	//Mp
	int RealMp = PlayerValue::GetValue()->GetMp();
	int MaxMp = PlayerValue::GetValue()->GetMaxMp();

	if (RealMp != RenderMP)
	{

		if (RealMp > RenderMP)
		{
			RenderMP_flt += MaxMp * 2.0f * _DeltaTime;
			RenderMP = static_cast<int>(RenderMP_flt);

			if (RenderMP >= RealMp)
			{
				RenderMP_flt = static_cast<float>(RealMp);
				RenderMP = RealMp;
			}
		}
		else
		{
			RenderMP_flt -= MaxMp * 2.0f * _DeltaTime;
			RenderMP = static_cast<int>(RenderMP_flt);

			if (RenderMP <= RealMp)
			{
				RenderMP_flt = static_cast<float>(RealMp);
				RenderMP = RealMp;
			}
		}

		float RenderMPRate = 0.0f;

		if (RealMp >= 0)
		{
			RenderMPRate = static_cast<float>(RenderMP) / static_cast<float>(MaxMp);
		}
		else
		{
			RenderMPRate = 0.0f;
		}

		float MpRateScale = 1 - RenderMPRate;
		float MpGradationXScale = 105.0f * MpRateScale;

		MpGradation->GetTransform()->SetLocalScale({ MpGradationXScale , 16.0f });
		MpGradation->GetTransform()->SetLocalPosition(MpBarRightPos - float4{ MpGradationXScale / 2.0f, 0.0f });
	}

	//Exp
	float ExpRateScale = 1 - PlayerValue::GetValue()->GetExpRate();

	float ExpGradationXScale = 114.0f * ExpRateScale;
	ExpGradation->GetTransform()->SetLocalScale({ ExpGradationXScale , 16.0f });
	ExpGradation->GetTransform()->SetLocalPosition(ExpBarRightPos - float4{ ExpGradationXScale / 2.0f, 0});
}

void BottomBar::LevelUpdate()
{
	int Level = PlayerValue::GetValue()->GetLevel();

	std::vector<std::string> LevelDigitStringVector;

	for (int i = 0; Level > 0; i++)
	{
		int LevelDigit = Level % 10;
		Level /= 10;
		LevelDigitStringVector.push_back(std::to_string(LevelDigit));
	}	

	size_t LevelRendererSize = LevelRenderer.size();
	size_t LevelDigitStringVectorSize = LevelDigitStringVector.size();

	//레벨은 변했지만, 자리수는 그대로일 때는 컴포넌트를 생성할 필요 없이 텍스쳐만 바꾸면 됨.
	if (LevelRendererSize == LevelDigitStringVectorSize)
	{
		for (int i = 0; i < LevelDigitStringVectorSize; i++)
		{
			LevelRenderer[i]->SetScaleToTexture("LevelNum" + LevelDigitStringVector[i] + ".png");
		}
	}

	//자리수가 변했을 때에는 초과분만큼 컴포넌트를 생성해야함
	else if (LevelRendererSize < LevelDigitStringVectorSize)
	{
		for (int i = 0; i < LevelDigitStringVectorSize; i++)
		{
			if(i >= LevelRendererSize)
			{
				std::shared_ptr<GameEngineUIRenderer> NumberRender = CreateComponent<GameEngineUIRenderer>();
				NumberRender->SetScaleToTexture("LevelNum" + LevelDigitStringVector[i] + ".png");
				LevelRenderer.push_back(NumberRender);
			}
			else
			{
				LevelRenderer[i]->SetScaleToTexture("LevelNum" + LevelDigitStringVector[i] + ".png");
			}
		}
	}

	LevelRendererSize = LevelRenderer.size();

	float4 BottomBarLayerPos = BottomBarLayer->GetTransform()->GetLocalPosition();
	float StartXpos = -245.0f + ((LevelRendererSize - 1.0f) * (-5.0f));

	for(int i = static_cast<int>(LevelRendererSize - 1); i >= 0; i--)
	{
		LevelRenderer[i]->GetTransform()->SetLocalPosition(BottomBarLayerPos + float4{ StartXpos + ((LevelRendererSize - i) * 12.0f) + 0.5f, -18.5f });
	}
}

void BottomBar::HPAndMPUpdate()
{
	std::string Hp = "[" + std::to_string(RenderHP) + " / " + std::to_string(PlayerValue::GetValue()->GetMaxHp()) + " ]";
	HpFont->SetText(Hp);

	std::string Mp = "[" + std::to_string(PlayerValue::GetValue()->GetMp()) + " / " + std::to_string(PlayerValue::GetValue()->GetMaxMp()) + " ]";
	MpFont->SetText(Mp);

	std::string ExpRate = std::to_string(PlayerValue::GetValue()->GetExpRate() * 100.0f);

	std::string Exp = std::to_string(PlayerValue::GetValue()->GetExp()) + " [" + ExpRate.substr(0, 5) + " %]";
	ExpFont->SetText(Exp);
}