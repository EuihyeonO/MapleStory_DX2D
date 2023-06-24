#include "PrecompileHeader.h"
#include "Mouse.h"
#include "TitleObjects.h"
#include "ContentButton.h"

#include <GameEngineCore/GameEngineButton.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <gameengineCore/GameEngineLevel.h>
#include <gameengineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <ctime>

TitleObjects::TitleObjects()
{
}

TitleObjects::~TitleObjects()
{
}

void TitleObjects::Start()
{
	TimeCounting();

	BackGround = CreateComponent<GameEngineSpriteRenderer>();
	BackGround->SetTexture("FullBackGround.png");
	BackGround->GetTransform()->SetLocalScale({ 800, 2396 });
	BackGround->GetTransform()->SetLocalPosition({ -40, 900 });

	Create_LoginBox();

	Logo = CreateComponent<GameEngineSpriteRenderer>();
	Logo->SetTexture("TitleLogo.png");
	Logo->GetTransform()->SetLocalScale({ 397, 219 });
	Logo->GetTransform()->SetLocalPosition({ 0, 175 });

	ChScroll = CreateComponent<GameEngineSpriteRenderer>();
	ChScroll->SetTexture("Scroll.png");
	ChScroll->GetTransform()->SetLocalScale({ 513, 152 });
	ChScroll->GetTransform()->SetLocalPosition({ 0,745});
	SetChScroll();

	Create_ChannelButton();
	Create_CharSelectButton();
	Create_CharacterObject();
	Create_CharCreateObject();

	TitleLight0 = CreateComponent<GameEngineSpriteRenderer>();
	TitleLight0->CreateAnimation({ .AnimationName = "TitleLight",.SpriteName = "TitleLight0",.FrameInter = 1.5f,.Loop = true,.ScaleToTexture = true });
	TitleLight0->ChangeAnimation("TitleLight");
	TitleLight0->GetTransform()->SetLocalPosition({ 200, 55 });

	TitleLight1 = CreateComponent<GameEngineSpriteRenderer>();
	TitleLight1->CreateAnimation({ .AnimationName = "TitleLight",.SpriteName = "TitleLight1",.FrameInter = 2.5f,.Loop = true,.ScaleToTexture = true });
	TitleLight1->ChangeAnimation("TitleLight");
	TitleLight1->GetTransform()->SetLocalPosition({ 125, 130 });

	TitleLight2 = CreateComponent<GameEngineSpriteRenderer>();
	TitleLight2->CreateAnimation({ .AnimationName = "TitleLight",.SpriteName = "TitleLight2",.FrameInter = 1.7f,.Loop = true,.ScaleToTexture = true });
	TitleLight2->ChangeAnimation("TitleLight");
	TitleLight2->GetTransform()->SetLocalPosition({ 115, 130 });
	
	TitleLight3 = CreateComponent<GameEngineSpriteRenderer>();
	TitleLight3->CreateAnimation({ .AnimationName = "TitleLight",.SpriteName = "TitleLight3",.FrameInter = 3.0f,.Loop = true,.ScaleToTexture = true });
	TitleLight3->ChangeAnimation("TitleLight");
	TitleLight3->GetTransform()->SetLocalPosition({ 225, 100 });

	TitleLight4 = CreateComponent<GameEngineSpriteRenderer>();
	TitleLight4->CreateAnimation({ .AnimationName = "TitleLight",.SpriteName = "TitleLight4",.FrameInter = 2.8f,.Loop = true,.ScaleToTexture = true });
	TitleLight4->ChangeAnimation("TitleLight");
	TitleLight4->GetTransform()->SetLocalPosition({ 185, 140 });
	
	TitleLight5 = CreateComponent<GameEngineSpriteRenderer>();
	TitleLight5->CreateAnimation({ .AnimationName = "TitleLight",.SpriteName = "TitleLight5",.FrameInter = 1.0f,.Loop = true,.ScaleToTexture = true });
	TitleLight5->ChangeAnimation("TitleLight");
	TitleLight5->GetTransform()->SetLocalPosition({ 185, 140 });

	Frame = CreateComponent<GameEngineUIRenderer>();
	Frame->SetTexture("Frame.png");
	Frame->GetTransform()->SetLocalScale({ 800, 600 });

	Create_FrameObject();
}

void TitleObjects::Update(float _DeltaTime)
{
	TimeCounting();
	EmptySlotAnimation();
	RollStatDice();

	if (LogoAlphaAngle >= 135.0f)
	{
		LogoAlphaAngle -= 90.0f;
	}

	LogoAlphaAngle += 15.0f * _DeltaTime;
	Logo->ColorOptionValue.MulColor.a = sin(GameEngineMath::DegToRad * LogoAlphaAngle);
	
	LoginObjectAlphaUpdate(_DeltaTime);

	float4 LoginBoardPos = LoginBoard->GetTransform()->GetLocalPosition();
	//Frame ����
	float4 CamPos = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();

	//LoginBt->GetTransform()->SetWorldPosition(-CamPos + LoginBoardPos + float4{ 128, 70 });
	SignUp->GetTransform()->SetLocalPosition(-CamPos + LoginBoardPos + float4{ -68, -44 });
	Exit->GetTransform()->SetLocalPosition(-CamPos + LoginBoardPos + float4{ 127, -42 });
	HomePage->GetTransform()->SetLocalPosition(-CamPos + LoginBoardPos + float4{ 33, -44 });
}

void TitleObjects::Render(float _DeltaTime)
{

}

void TitleObjects::Create_LoginBox()
{
	LoginBoard = CreateComponent<GameEngineSpriteRenderer>();
	LoginBoard->SetTexture("LoginBox.png");
	LoginBoard->GetTransform()->SetLocalScale({ 368, 236 });
	LoginBoard->GetTransform()->SetLocalPosition({ 100, -40 });

	float4 LoginBoardPos = LoginBoard->GetTransform()->GetLocalPosition();

	SignUp = GetLevel()->CreateActor<GameEngineButton>();
	SignUp->SetReleaseTexture("SignUpRelease.png");
	SignUp->SetHoverTexture("SignUpHover.png");
	SignUp->SetPressTexture("SignUpPress.png");
	SignUp->GetTransform()->SetLocalScale({ 92, 43 });
	SignUp->GetTransform()->SetLocalPosition(LoginBoardPos + float4{ -68, -44 });

	HomePage = GetLevel()->CreateActor<GameEngineButton>();
	HomePage->SetReleaseTexture("HomePageRelease.png");
	HomePage->SetHoverTexture("HomePageHover.png");
	HomePage->SetPressTexture("HomePagePress.png");
	HomePage->GetTransform()->SetLocalScale({ 93, 43 });
	HomePage->GetTransform()->SetLocalPosition(LoginBoardPos + float4{ 33, -44 });

	Exit = GetLevel()->CreateActor<GameEngineButton>();
	Exit->SetReleaseTexture("ExitRelease.png");
	Exit->SetHoverTexture("ExitHover.png");
	Exit->SetPressTexture("ExitPress.png");
	Exit->GetTransform()->SetLocalScale({ 84, 43 });
	Exit->GetTransform()->SetLocalPosition(LoginBoardPos + float4{ 127, -42 });

	LoginBt = GetLevel()->CreateActor<ContentButton>();
	LoginBt->SetReleaseTexture("LoginRelease.png");
	LoginBt->SetHoverTexture("LoginHover.png");
	LoginBt->SetPressTexture("LogInPress.png");
	LoginBt->SetAllPos(LoginBoardPos + float4{ 128, 70 });
	LoginBt->SetAllScale({ 95, 48 });
	LoginBt->SetisUIRenderer(false);

	SaveEmail = CreateComponent<GameEngineSpriteRenderer>();
	SaveEmail->SetTexture("SaveEmailRelease.png");
	SaveEmail->GetTransform()->SetLocalScale({ 85, 23 });
	SaveEmail->GetTransform()->SetLocalPosition(LoginBoardPos + float4{ -31 , 14});

	FindEmail = CreateComponent<GameEngineSpriteRenderer>();
	FindEmail->SetTexture("FindEmailRelease.png");
	FindEmail->GetTransform()->SetLocalScale({ 70, 23 });
	FindEmail->GetTransform()->SetLocalPosition(LoginBoardPos + float4{ 73 , 17 });

	FindPass = CreateComponent<GameEngineSpriteRenderer>();
	FindPass->SetTexture("FindPassRelease.png");
	FindPass->GetTransform()->SetLocalScale({ 58, 23 });
	FindPass->GetTransform()->SetLocalPosition(LoginBoardPos + float4{ 143 , 17 });

	Check = CreateComponent<GameEngineSpriteRenderer>();
	Check->SetTexture("CheckOn.png");
	Check->GetTransform()->SetLocalScale({ 15, 13 });
	Check->GetTransform()->SetLocalPosition(LoginBoardPos + float4{ -80 , 15 });
}

void TitleObjects::Create_ChannelButton()
{
	Zenis = GetLevel()->CreateActor<ContentButton>();
	Zenis->SetReleaseTexture("ZenisRelease.png");
	Zenis->SetHoverTexture("ZenisHover.png");
	Zenis->SetPressTexture("ZenisPress.png");
	Zenis->GetTransform()->SetLocalScale({ 28, 95 });
	Zenis->GetTransform()->SetLocalPosition({ -182, 752 });
	Zenis->SetReleaseScale({ 28, 95 });
	Zenis->SetHoverScale({ 28, 97 });
	Zenis->SetPressScale({ 28, 99 });
	Zenis->SetAllPos({ -182, 752 });
	Zenis->SetisUIRenderer(false);
	Zenis->SetEvent([this] {ChScroll->ChangeAnimation("Zenis");});

	Kastia = GetLevel()->CreateActor<ContentButton>();
	Kastia->SetReleaseTexture("KastiaRelease.png");
	Kastia->SetHoverTexture("KastiaHover.png");
	Kastia->SetPressTexture("KastiaPress.png");
	Kastia->SetReleaseScale({ 28, 95 });
	Kastia->SetHoverScale({ 28, 97 });
	Kastia->SetPressScale({ 28, 99 });
	Kastia->SetAllPos({ -152, 752 });
	Kastia->SetisUIRenderer(false);
	Kastia->SetEvent([this] {ChScroll->ChangeAnimation("Kastia"); });

	Kiny = GetLevel()->CreateActor<ContentButton>();
	Kiny->SetReleaseTexture("KinyRelease.png");
	Kiny->SetHoverTexture("KinyHover.png");
	Kiny->SetPressTexture("KinyPress.png");
	Kiny->SetReleaseScale({ 28, 95 });
	Kiny->SetHoverScale({ 28, 97 });
	Kiny->SetPressScale({ 28, 99 });
	Kiny->SetAllPos({ -122, 752 });
	Kiny->SetisUIRenderer(false);
	Kiny->SetEvent([this] {ChScroll->ChangeAnimation("Khaini"); });

	Croa = GetLevel()->CreateActor<ContentButton>();
	Croa->SetReleaseTexture("CroaRelease.png");
	Croa->SetHoverTexture("CroaHover.png");
	Croa->SetPressTexture("CroaPress.png");
	Croa->SetReleaseScale({ 28, 95 });
	Croa->SetHoverScale({ 28, 97 });
	Croa->SetPressScale({ 28, 99 });
	Croa->SetAllPos({ -92, 752 });
	Croa->SetisUIRenderer(false);
	Croa->SetEvent([this] {ChScroll->ChangeAnimation("Croa"); });

	Yellond = GetLevel()->CreateActor<ContentButton>();
	Yellond->SetReleaseTexture("YellondRelease.png");
	Yellond->SetHoverTexture("YellondHover.png");
	Yellond->SetPressTexture("YellondPress.png");
	Yellond->SetReleaseScale({ 28, 95 });
	Yellond->SetHoverScale({ 28, 97 });
	Yellond->SetPressScale({ 28, 99 });
	Yellond->SetAllPos({ -62, 752 });
	Yellond->SetisUIRenderer(false);
	Yellond->SetEvent([this] {ChScroll->ChangeAnimation("Yellond"); });

	Plana = GetLevel()->CreateActor<ContentButton>();
	Plana->SetReleaseTexture("PlanaRelease.png");
	Plana->SetHoverTexture("PlanaHover.png");
	Plana->SetPressTexture("PlanaPress.png");
	Plana->SetReleaseScale({ 28, 95 });
	Plana->SetHoverScale({ 28, 97 });
	Plana->SetPressScale({ 28, 99 });
	Plana->SetAllPos({ -32, 752 });
	Plana->SetisUIRenderer(false);
	Plana->SetEvent([this] {ChScroll->ChangeAnimation("Plana"); });

	Demetos = GetLevel()->CreateActor<ContentButton>();
	Demetos->SetReleaseTexture("DemetosRelease.png");
	Demetos->SetHoverTexture("DemetosHover.png");
	Demetos->SetPressTexture("DemetosPress.png");
	Demetos->SetReleaseScale({ 28, 95 });
	Demetos->SetHoverScale({ 28, 97 });
	Demetos->SetPressScale({ 28, 99 });
	Demetos->SetAllPos({ -2, 752 });
	Demetos->SetisUIRenderer(false);
	Demetos->SetEvent([this] {ChScroll->ChangeAnimation("Demetos"); });

	Akenia = GetLevel()->CreateActor<ContentButton>();
	Akenia->SetReleaseTexture("AkeniaRelease.png");
	Akenia->SetHoverTexture("AkeniaHover.png");
	Akenia->SetPressTexture("AkeniaPress.png");
	Akenia->SetReleaseScale({ 28, 95 });
	Akenia->SetHoverScale({ 28, 97 });
	Akenia->SetPressScale({ 28, 99 });
	Akenia->SetAllPos({ 28, 752 });
	Akenia->SetisUIRenderer(false);
	Akenia->SetEvent([this] {ChScroll->ChangeAnimation("Akenia"); });

	Bera = GetLevel()->CreateActor<ContentButton>();
	Bera->SetReleaseTexture("BeraRelease.png");
	Bera->SetHoverTexture("BeraHover.png");
	Bera->SetPressTexture("BeraPress.png");
	Bera->SetReleaseScale({ 28, 95 });
	Bera->SetHoverScale({ 28, 97 });
	Bera->SetPressScale({ 28, 99 });
	Bera->SetAllPos({ 58, 752 });
	Bera->SetisUIRenderer(false);
	Bera->SetEvent([this] {ChScroll->ChangeAnimation("Bera"); });

	Broa = GetLevel()->CreateActor<ContentButton>();
	Broa->SetReleaseTexture("BroaRelease.png");
	Broa->SetHoverTexture("BroaHover.png");
	Broa->SetPressTexture("BroaPress.png");
	Broa->SetReleaseScale({ 28, 95 });
	Broa->SetHoverScale({ 28, 97 });
	Broa->SetPressScale({ 28, 99 });
	Broa->SetAllPos({ 88, 752 });
	Broa->SetisUIRenderer(false);
	Broa->SetEvent([this] {ChScroll->ChangeAnimation("Broa"); });

	Mardia = GetLevel()->CreateActor<ContentButton>();
	Mardia->SetReleaseTexture("MardiaRelease.png");
	Mardia->SetHoverTexture("MardiaHover.png");
	Mardia->SetPressTexture("MardiaPress.png");
	Mardia->SetReleaseScale({ 28, 95 });
	Mardia->SetHoverScale({ 28, 97 });
	Mardia->SetPressScale({ 28, 99 });
	Mardia->SetAllPos({ 118, 752 });
	Mardia->SetisUIRenderer(false);
	Mardia->SetEvent([this] {ChScroll->ChangeAnimation("Mardia"); });

	Skania = GetLevel()->CreateActor<ContentButton>();
	Skania->SetReleaseTexture("SkaniaRelease.png");
	Skania->SetHoverTexture("SkaniaHover.png");
	Skania->SetPressTexture("SkaniaPress.png");
	Skania->SetReleaseScale({ 28, 95 });
	Skania->SetHoverScale({ 28, 97 });
	Skania->SetPressScale({ 28, 99 });
	Skania->SetAllPos({ 148, 752 });
	Skania->SetisUIRenderer(false);
	Skania->SetEvent([this] {ChScroll->ChangeAnimation("Skania"); });

	Stierce = GetLevel()->CreateActor<ContentButton>();
	Stierce->SetReleaseTexture("StierceRelease.png");
	Stierce->SetHoverTexture("StierceHover.png");
	Stierce->SetPressTexture("StiercePress.png");	
	Stierce->SetReleaseScale({ 28, 95 });
	Stierce->SetHoverScale({ 28, 97 });
	Stierce->SetPressScale({ 28, 99 });
	Stierce->SetAllPos({ 178, 752 });
	Stierce->SetisUIRenderer(false);
	Stierce->SetEvent([this] {ChScroll->ChangeAnimation("Stierce"); });

}

void TitleObjects::Create_CharSelectButton()
{
	CharSelectBox = CreateComponent<GameEngineSpriteRenderer>();
	CharSelectBox->SetTexture("CharSelectBox.png");
	CharSelectBox->GetTransform()->SetLocalScale({ 133, 238 });
	CharSelectBox->GetTransform()->SetLocalPosition({ 211, 1256 });

	float4 BoxPos = CharSelectBox->GetTransform()->GetLocalPosition();

	CharCreate = CreateComponent<GameEngineSpriteRenderer>();
	CharCreate->SetTexture("CreateRelease.png");
	CharCreate->GetTransform()->SetLocalScale({ 101, 35 });
	CharCreate->GetTransform()->SetLocalPosition(BoxPos + float4{1, 48});

	CharSelect = CreateComponent<GameEngineSpriteRenderer>();
	CharSelect->SetTexture("SelectRelease.png");
	CharSelect->GetTransform()->SetLocalScale({ 101, 30 });
	CharSelect->GetTransform()->SetLocalPosition(BoxPos + float4{ 1, 86 });

	CharDelete = CreateComponent<GameEngineSpriteRenderer>();
	CharDelete->SetTexture("DeleteRelease.png");
	CharDelete->GetTransform()->SetLocalScale({ 101, 43 });
	CharDelete->GetTransform()->SetLocalPosition(BoxPos + float4{ 1, -8 });
}

void TitleObjects::Create_CharacterObject()
{
	//���Ŀ� ĳ���Ͱ� ���� ���� �� �������� ��� �ؾ��ϴ��� ��� �� ������ �ؾ��� ��

	EmptySlot1 = CreateComponent<GameEngineSpriteRenderer>();
	EmptySlot1->SetTexture("EmptyChar.png");
	EmptySlot1->GetTransform()->SetLocalScale({ 51, 71 });
	EmptySlot1->GetTransform()->SetLocalPosition({-160, 1174});


	EmptySlot2 = CreateComponent<GameEngineSpriteRenderer>();
	EmptySlot2->SetTexture("EmptyChar.png");
	EmptySlot2->GetTransform()->SetLocalScale({ 51, 71 });
	EmptySlot2->GetTransform()->SetLocalPosition({ -38, 1174 });

	
	EmptySlot2 = CreateComponent<GameEngineSpriteRenderer>();
	EmptySlot2->SetTexture("EmptyChar.png");
	EmptySlot2->GetTransform()->SetLocalScale({ 51, 71 });
	EmptySlot2->GetTransform()->SetLocalPosition({ 84, 1174 });

	EmptyAnimation1 = CreateComponent<GameEngineSpriteRenderer>();
	EmptyAnimation1->SetTexture("EmptyCharAni0.png");
	EmptyAnimation1->GetTransform()->SetLocalScale({ 62, 9 });
	EmptyAnimation1->GetTransform()->SetLocalPosition({ -160, 1139});

	EmptyAnimation2 = CreateComponent<GameEngineSpriteRenderer>();
	EmptyAnimation2->SetTexture("EmptyCharAni0.png");
	EmptyAnimation2->GetTransform()->SetLocalScale({ 62, 9 });
	EmptyAnimation2->GetTransform()->SetLocalPosition({ -38, 1139 });

	EmptyAnimation3 = CreateComponent<GameEngineSpriteRenderer>();
	EmptyAnimation3->SetTexture("EmptyCharAni0.png");
	EmptyAnimation3->GetTransform()->SetLocalScale({ 62, 9 });
	EmptyAnimation3->GetTransform()->SetLocalPosition({ 84, 1139 });
}

void TitleObjects::EmptySlotAnimation()
{
	EmptyAniTimeCount += TimeCount;

	if (EmptyAniTimeCount >= 0.13f)
	{
		EmptyAniTimeCount = 0.0f;
		EmptyAniIndex++;

		if (EmptyAniIndex > 7)
		{
			EmptyAniIndex = 0;
		}

		std::string AniName = "EmptyCharAni" + std::to_string(EmptyAniIndex) + ".png";

		EmptyAnimation1->SetTexture(AniName);
		EmptyAnimation2->SetTexture(AniName);
		EmptyAnimation3->SetTexture(AniName);
	}
}

void TitleObjects::Create_FrameObject()
{
	//���Ŀ� ��������
}

void TitleObjects::Create_CharCreateObject()
{
	CharInfo = CreateComponent<GameEngineSpriteRenderer>();
	CharInfo->SetTexture("CharInfo.png");
	CharInfo->GetTransform()->SetLocalScale({ 201, 332 });
	CharInfo->GetTransform()->SetLocalPosition({ 175, 1842 });

	InfoScroll = CreateComponent<GameEngineSpriteRenderer>();
	InfoScroll->SetTexture("InfoScrollOpen3.png");
	InfoScroll->GetTransform()->SetLocalScale({ 242, 169 });
	InfoScroll->GetTransform()->SetLocalPosition({ -170, 1842 });

	float4 CharInfoPos = CharInfo->GetTransform()->GetLocalPosition();

	Dice = CreateComponent<GameEngineSpriteRenderer>();
	Dice->SetTexture("Dice0.png");
	Dice->GetTransform()->SetLocalScale({ 37, 56 });
	Dice->GetTransform()->SetLocalPosition(CharInfoPos + float4{50, -40});
	Dice->CreateAnimation({ .AnimationName = "Rolling",.SpriteName = "StatDiceRoll",.FrameInter = 0.09f,.Loop = false,.ScaleToTexture = true });
	Dice->CreateAnimation({ .AnimationName = "Stand",.SpriteName = "DiceStand",.FrameInter = 0.01f,.Loop = false,.ScaleToTexture = true });
	Dice->SetAnimationUpdateEvent("Rolling", 0, [this] { StatChange();});
	Dice->SetAnimationUpdateEvent("Rolling", 1, [this] { StatChange();});
	Dice->SetAnimationUpdateEvent("Rolling", 2, [this] { StatChange();});
	Dice->SetAnimationUpdateEvent("Rolling", 3, [this] {if (Dice->IsAnimationEnd() == true) { Dice->ChangeAnimation("Stand"); DiceCol->On(); }});
	
	DiceCol = CreateComponent<GameEngineCollision>();
	DiceCol->SetColType(ColType::AABBBOX2D);
	DiceCol->SetOrder(static_cast<int>(CollisionOrder::UI));
	DiceCol->GetTransform()->SetLocalScale({ 25, 28 });
	DiceCol->GetTransform()->SetLocalPosition(CharInfoPos + float4{ 44, -54 });

	OkButton = CreateComponent<GameEngineSpriteRenderer>();
	OkButton->SetTexture("OkRelease.png");
	OkButton->GetTransform()->SetLocalScale({ 76, 41 });
	OkButton->GetTransform()->SetLocalPosition(CharInfoPos + float4{ -34, -140 });

	NoButton = CreateComponent<GameEngineSpriteRenderer>();
	NoButton->SetTexture("NoRelease.png");
	NoButton->GetTransform()->SetLocalScale({ 81, 41 });
	NoButton->GetTransform()->SetLocalPosition(CharInfoPos + float4{ 43, -140 });

	StrRender = CreateComponent<GameEngineFontRenderer>();
	DexRender = CreateComponent<GameEngineFontRenderer>();
	IntRender = CreateComponent<GameEngineFontRenderer>();
	LukRender = CreateComponent<GameEngineFontRenderer>();

	StrRender->SetFont("����");
	StrRender->SetColor({0, 0, 0, 1});
	StrRender->SetScale(12.0f);
	StrRender->SetText("4");
	StrRender->GetTransform()->SetLocalPosition(CharInfoPos + float4{ -31, 9 });

	DexRender->SetFont("����");
	DexRender->SetColor({0, 0, 0, 1});
	DexRender->SetScale(12.0f);
	DexRender->SetText("4");
	DexRender->GetTransform()->SetLocalPosition(CharInfoPos + float4{ -31, -11 });

	IntRender->SetFont("����");
	IntRender->SetColor({0, 0, 0, 1});
	IntRender->SetScale(12.0f);
	IntRender->SetText("4");
	IntRender->GetTransform()->SetLocalPosition(CharInfoPos + float4{ -31, -31 });

	LukRender->SetFont("����");
	LukRender->SetColor({ 0, 0, 0, 1 });
	LukRender->SetScale(12.0f);
	LukRender->SetText("4");
	LukRender->GetTransform()->SetLocalPosition(CharInfoPos + float4{ -31, -51 });
}

void TitleObjects::RollStatDice()
{
	if (Mouse::GetMouse()->IsClick() == true)
	{
		if (DiceCol->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D) != nullptr)
		{
			Dice->ChangeAnimation("Rolling");
			DiceCol->Off();
		}
	}
}

void TitleObjects::StatChange()
{
	Counting += TimeCount;
	if(Counting >=0.03f)
	{
		Counting = 0.0f;

		int MaxSumStat = 28;

		int StrStat = 0;
		int DexStat = 0;
		int IntStat = 0;
		int LukStat = 0;

		StrStat = GameEngineRandom::MainRandom.RandomInt(4, 10);
		MaxSumStat -= StrStat;

		DexStat = GameEngineRandom::MainRandom.RandomInt(4, 10);
		MaxSumStat -= DexStat;

		IntStat = GameEngineRandom::MainRandom.RandomInt(4, 10);
		while (MaxSumStat - IntStat < 4)
		{
			IntStat = GameEngineRandom::MainRandom.RandomInt(4, 10);
		}

		MaxSumStat -= IntStat;
		if (MaxSumStat > 10)
		{
			MaxSumStat = 10;
		}

		LukStat = GameEngineRandom::MainRandom.RandomInt(4, MaxSumStat);

		StrRender->SetText(std::to_string(StrStat));
		DexRender->SetText(std::to_string(DexStat));
		IntRender->SetText(std::to_string(IntStat));
		LukRender->SetText(std::to_string(LukStat));
	}
}

void TitleObjects::LoginObjectAlphaUpdate(float _DeltaTime)
{
	TitleLightAlphaAngle0 += 30 * _DeltaTime;
	TitleLightAlphaAngle1 += 30 * _DeltaTime;
	TitleLightAlphaAngle2 += 30 * _DeltaTime;
	TitleLightAlphaAngle3 += 30 * _DeltaTime;
	TitleLightAlphaAngle4 += 30 * _DeltaTime;

	if (TitleLightAlphaAngle0 >= 180.0f)
	{
		TitleLightAlphaAngle0 -= 180.0f;
		TitleLightAlphaAngle0 *= -1.0f;
	}

	if (TitleLightAlphaAngle1 >= 180.0f)
	{						
		TitleLightAlphaAngle1 -= 180.0f;
		TitleLightAlphaAngle1 *= -1.0f;
	}

	if (TitleLightAlphaAngle2 >= 180.0f)
	{						  
		TitleLightAlphaAngle2 -= 180.0f;
		TitleLightAlphaAngle2 *= -1.0f;
	}

	if (TitleLightAlphaAngle3 >= 180.0f)
	{						
		TitleLightAlphaAngle3 -= 180.0f;
		TitleLightAlphaAngle3 *= -1.0f;
	}

	if (TitleLightAlphaAngle4 >= 180.0f)
	{						
		TitleLightAlphaAngle4 -= 180.0f;
		TitleLightAlphaAngle4 *= -1.0f;
	}

	if (TitleLightAlphaAngle5 >= 180.0f)
	{						
		TitleLightAlphaAngle5 -= 180.0f;
		TitleLightAlphaAngle5 *= -1.0f;
	}

	TitleLight0->ColorOptionValue.MulColor.a = sin(GameEngineMath::DegToRad * TitleLightAlphaAngle0);
	TitleLight1->ColorOptionValue.MulColor.a = sin(GameEngineMath::DegToRad * TitleLightAlphaAngle1);
	TitleLight2->ColorOptionValue.MulColor.a = sin(GameEngineMath::DegToRad * TitleLightAlphaAngle2);
	TitleLight3->ColorOptionValue.MulColor.a = sin(GameEngineMath::DegToRad * TitleLightAlphaAngle3);
	TitleLight4->ColorOptionValue.MulColor.a = sin(GameEngineMath::DegToRad * TitleLightAlphaAngle4);
	TitleLight5->ColorOptionValue.MulColor.a = sin(GameEngineMath::DegToRad * TitleLightAlphaAngle5);
}


void TitleObjects::SetChScroll()
{
	ChScroll->CreateAnimation({ .AnimationName = "Akenia",.SpriteName = "Akenia",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ChScroll->SetAnimationStartEvent("Akenia", 0, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 620.5 }); });
	ChScroll->SetAnimationStartEvent("Akenia", 1, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 617 }); });
	ChScroll->SetAnimationStartEvent("Akenia", 2, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 613 }); });

	ChScroll->CreateAnimation({ .AnimationName = "Bera",.SpriteName = "Bera",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ChScroll->SetAnimationStartEvent("Bera", 0, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 620.5 }); });
	ChScroll->SetAnimationStartEvent("Bera", 1, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 617 }); });
	ChScroll->SetAnimationStartEvent("Bera", 2, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 613 }); });
	
	ChScroll->CreateAnimation({ .AnimationName = "Broa",.SpriteName = "Broa",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ChScroll->SetAnimationStartEvent("Broa", 0, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 620.5 }); });
	ChScroll->SetAnimationStartEvent("Broa", 1, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 617 }); });
	ChScroll->SetAnimationStartEvent("Broa", 2, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 613 }); });

	ChScroll->CreateAnimation({ .AnimationName = "Croa",.SpriteName = "Croa",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ChScroll->SetAnimationStartEvent("Croa", 0, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 620.5 }); });
	ChScroll->SetAnimationStartEvent("Croa", 1, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 617 }); });
	ChScroll->SetAnimationStartEvent("Croa", 2, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 613 }); });

	ChScroll->CreateAnimation({ .AnimationName = "Demetos",.SpriteName = "Demetos",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ChScroll->SetAnimationStartEvent("Demetos", 0, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 620.5 }); });
	ChScroll->SetAnimationStartEvent("Demetos", 1, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 617 }); });
	ChScroll->SetAnimationStartEvent("Demetos", 2, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 613 }); });

	ChScroll->CreateAnimation({ .AnimationName = "Kastia",.SpriteName = "Kastia",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ChScroll->SetAnimationStartEvent("Kastia", 0, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 620.5 }); });
	ChScroll->SetAnimationStartEvent("Kastia", 1, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 617 }); });
	ChScroll->SetAnimationStartEvent("Kastia", 2, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 613 }); });

	ChScroll->CreateAnimation({ .AnimationName = "Khaini",.SpriteName = "Khaini",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ChScroll->SetAnimationStartEvent("Khaini", 0, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 620.5 }); });
	ChScroll->SetAnimationStartEvent("Khaini", 1, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 617 }); });
	ChScroll->SetAnimationStartEvent("Khaini", 2, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 613 }); });

	ChScroll->CreateAnimation({ .AnimationName = "Mardia",.SpriteName = "Mardia",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ChScroll->SetAnimationStartEvent("Mardia", 0, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 620.5 }); });
	ChScroll->SetAnimationStartEvent("Mardia", 1, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 617 }); });
	ChScroll->SetAnimationStartEvent("Mardia", 2, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 613 }); });

	ChScroll->CreateAnimation({ .AnimationName = "Plana",.SpriteName = "Plana",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ChScroll->SetAnimationStartEvent("Plana", 0, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 620.5 }); });
	ChScroll->SetAnimationStartEvent("Plana", 1, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 617 }); });
	ChScroll->SetAnimationStartEvent("Plana", 2, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 613 }); });

	ChScroll->CreateAnimation({ .AnimationName = "Skania",.SpriteName = "Skania",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ChScroll->SetAnimationStartEvent("Skania", 0, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 620.5 }); });
	ChScroll->SetAnimationStartEvent("Skania", 1, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 617 }); });
	ChScroll->SetAnimationStartEvent("Skania", 2, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 613 }); });

	ChScroll->CreateAnimation({ .AnimationName = "Stierce",.SpriteName = "Stierce",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ChScroll->SetAnimationStartEvent("Stierce", 0, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 620.5 }); });
	ChScroll->SetAnimationStartEvent("Stierce", 1, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 617 }); });
	ChScroll->SetAnimationStartEvent("Stierce", 2, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 613 }); });

	ChScroll->CreateAnimation({ .AnimationName = "Yellond",.SpriteName = "Yellond",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ChScroll->SetAnimationStartEvent("Yellond", 0, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 620.5 }); });
	ChScroll->SetAnimationStartEvent("Yellond", 1, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 617 }); });
	ChScroll->SetAnimationStartEvent("Yellond", 2, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 613 }); });

	ChScroll->CreateAnimation({ .AnimationName = "Zenis",.SpriteName = "Zenis",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ChScroll->SetAnimationStartEvent("Zenis", 0, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 620.5 }); });
	ChScroll->SetAnimationStartEvent("Zenis", 1, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 617 }); });
	ChScroll->SetAnimationStartEvent("Zenis", 2, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 613 }); });

}