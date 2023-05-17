#include "PrecompileHeader.h"
#include "BottomBar.h"
#include "PlayerValue.h"
#include <GameEngineCore/GameEngineLevel.h>
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
	BottomBarBackGround = CreateComponent<GameEngineSpriteRenderer>();
	BottomBarBackGround->SetScaleToTexture("BottomBarBackGround.png");

	BottomBarLayer = CreateComponent<GameEngineSpriteRenderer>();
	BottomBarLayer->SetScaleToTexture("BottomBarLayer.png");

	StatusBar = CreateComponent<GameEngineSpriteRenderer>();
	StatusBar->SetScaleToTexture("StatusBar.png");

	HpGradation = CreateComponent<GameEngineSpriteRenderer>();
	HpGradation->SetScaleToTexture("StatusGradation.png");

	MpGradation = CreateComponent<GameEngineSpriteRenderer>();
	MpGradation->SetScaleToTexture("StatusGradation.png");

	ExpGradation = CreateComponent<GameEngineSpriteRenderer>();
	ExpGradation->SetTexture("StatusGradation.png");

	StatusBarLayer = CreateComponent<GameEngineSpriteRenderer>();
	StatusBarLayer->SetScaleToTexture("StatusBarLayer.png");

	PlayerValue::GetValue()->SetLevel(11);
	LevelRenderer.reserve(4);
}

void BottomBar::Update(float _DeltaTime) 
{
	BottomBarPosUpdate();
	GradationUpdate();
	LevelUpdate();
}

void BottomBar::Render(float _DeltaTime) 
{

}

void BottomBar::BottomBarPosUpdate()
{
	float4 GameEngineWindowScale = GameEngineWindow::GetScreenSize();

	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();
	BottomBarBackGround->GetTransform()->SetLocalPosition({ CameraPos.x, CameraPos.y - GameEngineWindowScale.hy() + 35 });

	float4 BottomBarBackGroundPos = BottomBarBackGround->GetTransform()->GetLocalPosition();
	BottomBarLayer->GetTransform()->SetLocalPosition(BottomBarBackGroundPos + float4{ -GameEngineWindowScale.hx() + 285, 0 });

	float4 BottomBarLayerPos = BottomBarLayer->GetTransform()->GetLocalPosition();
	StatusBar->GetTransform()->SetLocalPosition(BottomBarLayerPos + float4{ 100, -17.5f });

	float4 StatusBarPos = StatusBar->GetTransform()->GetLocalPosition();
	StatusBarLayer->GetTransform()->SetLocalPosition(StatusBarPos);
}

void BottomBar::GradationUpdate()
{
	float4 StatusBarPos = StatusBar->GetTransform()->GetLocalPosition();

	ExpBarRightPos = StatusBarPos + float4{ 167.0f, -8.0f };
	HpBarRightPos = ExpBarRightPos - float4{ 230.0f , 0.0f };
	MpBarRightPos = HpBarRightPos + float4{ 108.0f , 0.0f };

	//Hp
	float HpRateScale = 1 - PlayerValue::GetValue()->GetHpRate();
	float HpGradationXScale = 106.0f * HpRateScale;

	HpGradation->GetTransform()->SetLocalScale({ HpGradationXScale , 16.0f });
	HpGradation->GetTransform()->SetLocalPosition(HpBarRightPos - float4{ HpGradationXScale / 2.0f, 0.0f });

	//Mp
	float MpRateScale = 1 - PlayerValue::GetValue()->GetMpRate();
	float MpGradationXScale = 105.0f * MpRateScale;

	MpGradation->GetTransform()->SetLocalScale({ MpGradationXScale , 16.0f });
	MpGradation->GetTransform()->SetLocalPosition(MpBarRightPos - float4{MpGradationXScale / 2.0f, 0.0f });

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
				std::shared_ptr<GameEngineSpriteRenderer> NumberRender = CreateComponent<GameEngineSpriteRenderer>();
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