#include "PrecompileHeader.h"
#include "Mouse.h"
#include "TitleObjects.h"
#include "ContentButton.h"
#include "PlayerValue.h"
#include "UIController.h"
#include "Player.h"

#include <GameEngineCore/GameEngineButton.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <gameengineCore/GameEngineLevel.h>
#include <gameengineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
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
	TitleLight0->GetTransform()->SetLocalPosition({ 200, 55, -1 });

	TitleLight1 = CreateComponent<GameEngineSpriteRenderer>();
	TitleLight1->CreateAnimation({ .AnimationName = "TitleLight",.SpriteName = "TitleLight1",.FrameInter = 2.5f,.Loop = true,.ScaleToTexture = true });
	TitleLight1->ChangeAnimation("TitleLight");
	TitleLight1->GetTransform()->SetLocalPosition({ 125, 130, -1 });

	TitleLight2 = CreateComponent<GameEngineSpriteRenderer>();
	TitleLight2->CreateAnimation({ .AnimationName = "TitleLight",.SpriteName = "TitleLight2",.FrameInter = 1.7f,.Loop = true,.ScaleToTexture = true });
	TitleLight2->ChangeAnimation("TitleLight");
	TitleLight2->GetTransform()->SetLocalPosition({ 115, 130, -1 });
	
	TitleLight3 = CreateComponent<GameEngineSpriteRenderer>();
	TitleLight3->CreateAnimation({ .AnimationName = "TitleLight",.SpriteName = "TitleLight3",.FrameInter = 3.0f,.Loop = true,.ScaleToTexture = true });
	TitleLight3->ChangeAnimation("TitleLight");
	TitleLight3->GetTransform()->SetLocalPosition({ 225, 100, -1 });

	TitleLight4 = CreateComponent<GameEngineSpriteRenderer>();
	TitleLight4->CreateAnimation({ .AnimationName = "TitleLight",.SpriteName = "TitleLight4",.FrameInter = 2.8f,.Loop = true,.ScaleToTexture = true });
	TitleLight4->ChangeAnimation("TitleLight");
	TitleLight4->GetTransform()->SetLocalPosition({ 185, 140, -1 });
	
	TitleLight5 = CreateComponent<GameEngineSpriteRenderer>();
	TitleLight5->CreateAnimation({ .AnimationName = "TitleLight",.SpriteName = "TitleLight5",.FrameInter = 1.0f,.Loop = true,.ScaleToTexture = true });
	TitleLight5->ChangeAnimation("TitleLight");
	TitleLight5->GetTransform()->SetLocalPosition({ 185, 140, -1 });

	Frame = CreateComponent<GameEngineUIRenderer>();
	Frame->SetTexture("Frame.png");
	Frame->GetTransform()->SetLocalScale({ 800, 600 });

	ChannelCheck = CreateComponent<GameEngineSpriteRenderer>();
	ChannelCheck->CreateAnimation({ .AnimationName = "Check",.SpriteName = "ChannelCheck",.Loop = false,.ScaleToTexture = true,.FrameTime = {0.1f, 0.05f ,0.05f ,0.1f } });
	ChannelCheck->Off();
	
	NickName = CreateComponent<GameEngineFontRenderer>();
	NickName->SetFont("±¼¸²");
	NickName->SetScale(13.0f);
	NickName->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	NickName->GetTransform()->SetLocalPosition({ 110, 1909 });

	LoginID = CreateComponent<GameEngineFontRenderer>();
	LoginID->SetFont("±¼¸²");
	LoginID->SetScale(13.0f);
	LoginID->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f});
	LoginID->GetTransform()->SetLocalPosition({ 37, 51 });

	LoginPassWord = CreateComponent<GameEngineFontRenderer>();
	LoginPassWord->SetFont("±¼¸²");
	LoginPassWord->SetScale(13.0f);
	LoginPassWord->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	LoginPassWord->GetTransform()->SetLocalPosition({ 37, 21 });

	TypingUpdateFunc = std::bind(&TitleObjects::TypingLoginInfo, this, std::placeholders::_1);

	SetChCollision();
	Create_FrameObject();
}

void TitleObjects::Update(float _DeltaTime)
{
	TimeCounting();
	EmptySlotAnimation();
	RollStatDice();

	if (TypingUpdateFunc != nullptr)
	{
		TypingUpdateFunc(_DeltaTime);
	}

	if (LogoAlphaAngle >= 135.0f)
	{
		LogoAlphaAngle -= 90.0f;
	}

	LogoAlphaAngle += 15.0f * _DeltaTime;
	Logo->ColorOptionValue.MulColor.a = sin(GameEngineMath::DegToRad * LogoAlphaAngle);
	
	LoginObjectAlphaUpdate(_DeltaTime);

	float4 LoginBoardPos = LoginBoard->GetTransform()->GetLocalPosition();
	//Frame °íÁ¤
	float4 CamPos = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();

	if (isChScrollOpen == true)
	{
		if(ChScroll->GetCurrentFrame() == 0) 
		{
			ChScroll->GetTransform()->SetLocalPosition({ 0, 620.5 }); 
		}

		ChannelChecking();
	}

	if (FadeOut != nullptr)
	{
		FadeOut(_DeltaTime);
	}
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

	SignUp = GetLevel()->CreateActor<ContentButton>();
	SignUp->SetReleaseTexture("SignUpRelease.png");
	SignUp->SetHoverTexture("SignUpHover.png");
	SignUp->SetPressTexture("SignUpPress.png");
	SignUp->SetAllScale({ 92, 43 });
	SignUp->SetAllPos(LoginBoardPos + float4{ -68, -44 });
	SignUp->SetisUIRenderer(false);
	SignUp->SetHoverSound("ButtonHover.mp3");
	SignUp->SetPressSound("ButtonClick.mp3");

	HomePage = GetLevel()->CreateActor<ContentButton>();
	HomePage->SetReleaseTexture("HomePageRelease.png");
	HomePage->SetHoverTexture("HomePageHover.png");
	HomePage->SetPressTexture("HomePagePress.png");
	HomePage->SetAllScale({ 93, 43 });
	HomePage->SetAllPos(LoginBoardPos + float4{ 33, -44 });
	HomePage->SetisUIRenderer(false);
	HomePage->SetHoverSound("ButtonHover.mp3");
	HomePage->SetPressSound("ButtonClick.mp3");

	Exit = GetLevel()->CreateActor<ContentButton>();
	Exit->SetReleaseTexture("ExitRelease.png");
	Exit->SetHoverTexture("ExitHover.png");
	Exit->SetPressTexture("ExitPress.png");
	Exit->SetAllScale({ 84, 43 });
	Exit->SetAllPos(LoginBoardPos + float4{ 127, -42 });
	Exit->SetisUIRenderer(false);
	Exit->SetHoverSound("ButtonHover.mp3");
	Exit->SetPressSound("ButtonClick.mp3");

	LoginBt = GetLevel()->CreateActor<ContentButton>();
	LoginBt->SetReleaseTexture("LoginDisable.png");
	LoginBt->SetHoverTexture("LoginDisable.png");
	LoginBt->SetPressTexture("LoginDisable.png");
	LoginBt->SetAllPos(LoginBoardPos + float4{ 128, 70 });
	LoginBt->SetAllScale({ 95, 48 });
	LoginBt->SetisUIRenderer(false);
	LoginBt->SetHoverSound("ButtonHover.mp3");
	LoginBt->SetPressSound("ButtonClick.mp3");

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
	Zenis->SetHoverSound("ButtonHover.mp3");
	Zenis->SetHoverSound("WorldSelect.mp3");

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
	Kastia->SetHoverSound("ButtonHover.mp3");
	Kastia->SetPressSound("WorldSelect.mp3");

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
	Kiny->SetHoverSound("ButtonHover.mp3");
	Kiny->SetPressSound("WorldSelect.mp3");

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
	Croa->SetHoverSound("ButtonHover.mp3");
	Croa->SetPressSound("WorldSelect.mp3");

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
	Yellond->SetHoverSound("ButtonHover.mp3");
	Yellond->SetPressSound("WorldSelect.mp3");

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
	Plana->SetHoverSound("ButtonHover.mp3");
	Plana->SetPressSound("WorldSelect.mp3");

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
	Demetos->SetHoverSound("ButtonHover.mp3");
	Demetos->SetPressSound("WorldSelect.mp3");
	
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
	Akenia->SetHoverSound("ButtonHover.mp3");
	Akenia->SetPressSound("WorldSelect.mp3");

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
	Bera->SetHoverSound("ButtonHover.mp3");
	Bera->SetPressSound("WorldSelect.mp3");

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
	Broa->SetHoverSound("ButtonHover.mp3");
	Broa->SetPressSound("WorldSelect.mp3");

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
	Mardia->SetHoverSound("ButtonHover.mp3");
	Mardia->SetPressSound("WorldSelect.mp3");

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
	Skania->SetHoverSound("ButtonHover.mp3");
	Skania->SetPressSound("WorldSelect.mp3");

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
	Stierce->SetHoverSound("ButtonHover.mp3");
	Stierce->SetPressSound("WorldSelect.mp3");
}

void TitleObjects::Create_CharSelectButton()
{
	CharSelectBox = CreateComponent<GameEngineSpriteRenderer>();
	CharSelectBox->SetTexture("CharSelectBox.png");
	CharSelectBox->GetTransform()->SetLocalScale({ 133, 238 });
	CharSelectBox->GetTransform()->SetLocalPosition({ 211, 1256 });

	float4 BoxPos = CharSelectBox->GetTransform()->GetLocalPosition();

	CharCreate = GetLevel()->CreateActor<ContentButton>();
	CharCreate->SetReleaseTexture("CreateRelease.png");
	CharCreate->SetHoverTexture("CreateHover.png");
	CharCreate->SetPressTexture("CreatePress.png");
	CharCreate->SetAllScale({ 101, 35 });
	CharCreate->SetisUIRenderer(false);
	CharCreate->SetAllPos(BoxPos + float4{1, 48, -1});

	CharSelect = GetLevel()->CreateActor<ContentButton>();
	CharSelect->SetReleaseTexture("SelectDisable.png");
	CharSelect->SetHoverTexture("SelectDisable.png");
	CharSelect->SetPressTexture("SelectDisable.png");
	CharSelect->SetAllScale({ 101, 30 });
	CharSelect->SetisUIRenderer(false);
	CharSelect->SetAllPos(BoxPos + float4{ 1, 86 });
	CharSelect->SetEvent(nullptr);

	CharDelete = GetLevel()->CreateActor<ContentButton>();
	CharDelete->SetReleaseTexture("DeleteRelease.png");
	CharDelete->SetHoverTexture("DeleteHover.png");
	CharDelete->SetPressTexture("DeletePress.png");
	CharDelete->SetAllScale({ 101, 43 });
	CharDelete->SetisUIRenderer(false);
	CharDelete->SetAllPos(BoxPos + float4{ 1, -8 });
}

void TitleObjects::ActivateToCharSelect()
{

	CharSelect->SetReleaseTexture("SelectRelease.png");
	CharSelect->SetHoverTexture("SelectHover.png");
	CharSelect->SetPressTexture("SelectPress.png");
	CharSelect->SetEvent([this]
		{
			GameEngineSound::Play("CharSelect.mp3");

			std::weak_ptr<GameEngineUIRenderer> Black = CreateComponent<GameEngineUIRenderer>();
			Black.lock()->ColorOptionValue.MulColor = { 0.0f, 0.0f, 0.0f, 0.0f };
			Black.lock()->GetTransform()->SetLocalScale({ 800, 600 });

			FadeOut = [Black](float _DeltaTime)
			{
				Black.lock()->ColorOptionValue.MulColor.a += 0.25f * _DeltaTime;
				if (Black.lock()->ColorOptionValue.MulColor.a >= 1.0f)
				{
					Black.lock()->ColorOptionValue.MulColor.a = 1.0f;
					Black.lock()->Death();

					GameEngineCore::ChangeLevel("Level_BeginnersTown1");
				}
			};
		});

	EmptySlot1->Off();
	EmptyAnimation1->Off();

	CharCreate->SetReleaseTexture("CreateDisable.png");
	CharCreate->SetHoverTexture("CreateDisable.png");
	CharCreate->SetPressTexture("CreateDisable.png");
	CharCreate->SetEvent(nullptr);
}

void TitleObjects::TypingLoginInfo(float _DeltaTtime)
{
	TypingCount += _DeltaTtime;

	if(TypingCount >= 0.08f)
	{
		GameEngineSound::Play("Typing.mp3");

		if(isEndID == false)
		{
			std::string CopyText = "OhEuiHyeon";
			IDText.push_back(CopyText[TypingIndex]);
			LoginID->SetText(IDText);

			TypingCount = 0.0f;
			TypingIndex++;

			if (TypingIndex >= CopyText.size())
			{
				isEndID = true;
				TypingCount = -1.0f;
				TypingIndex = 0;
			}
		}
		else
		{
			std::string CopyText = "MapleStory By DX_11";
			
			PassWordText.push_back(CopyText[TypingIndex]);
			LoginPassWord->SetText(PassWordText);

			TypingCount = 0.0f;
			TypingIndex++;

			if (TypingIndex >= CopyText.size())
			{
				LoginBt->SetReleaseTexture("LoginRelease.png");
				LoginBt->SetHoverTexture("LoginHover.png");
				LoginBt->SetPressTexture("LogInPress.png");

				LoginBt->SetHoverSound("ButtonHover.mp3");
				LoginBt->SetPressSound("ButtonClick.mp3");								
				LoginBt->SetEvent(LogintBtFunc);

				TypingIndex = 0;
				TypingUpdateFunc = nullptr;
			}
		}
	}
}

void TitleObjects::TypingNickName(float _DeltaTtime)
{
	NickNameCount += _DeltaTtime;

	if (NickNameCount >= 0.08f)
	{
		GameEngineSound::Play("Typing.mp3");

		std::string CopyText = "EuiHyeon";
		NickNameText.push_back(CopyText[NickNameIndex]);
		NickName->SetText(NickNameText);

		NickNameCount = 0.0f;
		NickNameIndex++;

		if (NickNameIndex >= CopyText.size())
		{
			TypingUpdateFunc = nullptr;
		}
	}
}

void TitleObjects::Create_CharacterObject()
{
	//ÃßÈÄ¿¡ Ä³¸¯ÅÍ°¡ ÀÖÀ» ¶§´Â ÀÌ ·»´õ·¯¸¦ ¾î¶»°Ô ÇØ¾ßÇÏ´ÂÁö °í¹Î ÈÄ º¯°æÀ» ÇØ¾ßÇÒ µí

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
	//ÃßÈÄ¿¡ ±¸ÇöÇÏÀÚ
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
	float4 InfoScrollPos = InfoScroll->GetTransform()->GetLocalPosition();

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

	OkButton = GetLevel()->CreateActor<ContentButton>();
	OkButton->SetReleaseTexture("OKRelease.png");
	OkButton->SetHoverTexture("OKHover.png");
	OkButton->SetPressTexture("OKPress.png");
	OkButton->SetAllScale({ 76, 41 });
	OkButton->SetisUIRenderer(false);
	OkButton->SetAllPos(CharInfoPos + float4{ -34, -140 });

	NoButton = CreateComponent<GameEngineSpriteRenderer>();
	NoButton->SetTexture("NoRelease.png");
	NoButton->GetTransform()->SetLocalScale({ 81, 41 });
	NoButton->GetTransform()->SetLocalPosition(CharInfoPos + float4{ 43, -140 });

	StrRender = CreateComponent<GameEngineFontRenderer>();
	DexRender = CreateComponent<GameEngineFontRenderer>();
	IntRender = CreateComponent<GameEngineFontRenderer>();
	LukRender = CreateComponent<GameEngineFontRenderer>();

	StrRender->SetFont("±¼¸²");
	StrRender->SetColor({0, 0, 0, 1});
	StrRender->SetScale(12.0f);
	StrRender->SetText("4");
	StrRender->GetTransform()->SetLocalPosition(CharInfoPos + float4{ -31, 9 });

	DexRender->SetFont("±¼¸²");
	DexRender->SetColor({0, 0, 0, 1});
	DexRender->SetScale(12.0f);
	DexRender->SetText("4");
	DexRender->GetTransform()->SetLocalPosition(CharInfoPos + float4{ -31, -11 });

	IntRender->SetFont("±¼¸²");
	IntRender->SetColor({0, 0, 0, 1});
	IntRender->SetScale(12.0f);
	IntRender->SetText("4");
	IntRender->GetTransform()->SetLocalPosition(CharInfoPos + float4{ -31, -31 });

	LukRender->SetFont("±¼¸²");
	LukRender->SetColor({ 0, 0, 0, 1 });
	LukRender->SetScale(12.0f);
	LukRender->SetText("4");
	LukRender->GetTransform()->SetLocalPosition(CharInfoPos + float4{ -31, -51 });

	Hair = CreateComponent<GameEngineFontRenderer>();
	Face = CreateComponent<GameEngineFontRenderer>();
	Coat = CreateComponent<GameEngineFontRenderer>();
	Pants = CreateComponent<GameEngineFontRenderer>();
	Weapon = CreateComponent<GameEngineFontRenderer>();
	Shoes = CreateComponent<GameEngineFontRenderer>();

	FaceVec.reserve(4);
	FaceVec.push_back({"µµÀüÀûÀÎ ¾ó±¼", "Face1"});
	FaceVec.push_back({"½ÅÁßÇÑ ¾ó±¼", "Face2"});

	ClothesVec[static_cast<int>(EquipType::Coat)].reserve(4);
	ClothesVec[static_cast<int>(EquipType::Cap)].reserve(4);
	ClothesVec[static_cast<int>(EquipType::Weapon)].reserve(4);

	ClothesVec[static_cast<int>(EquipType::Coat)].push_back({ "ÇÏ¾á ¹ÝÆÈ ¸éÆ¼", "WHITETSHIRT" });
	ClothesVec[static_cast<int>(EquipType::Coat)].push_back({ "È¸»ö ¹ÝÆÈ ¸éÆ¼", "GRAYTSHIRT" });

	ClothesVec[static_cast<int>(EquipType::Pants)].push_back({ "ÆÄ¶û Ã» ¹Ý¹ÙÁö", "BLUEPANTS" });
	ClothesVec[static_cast<int>(EquipType::Pants)].push_back({ "ÁÖÈ² Ã» ¹Ý¹ÙÁö", "BROWNPANTS" });

	ClothesVec[static_cast<int>(EquipType::Shoes)].push_back({ "°¡Á× »÷µé", "SANDAL" });
	ClothesVec[static_cast<int>(EquipType::Shoes)].push_back({ "»¡°£ °í¹« ÀåÈ­", "RAINBOOTS" });

	Hair->SetFont("±¼¸²");
	Hair->SetColor({ 0, 0, 0, 1 });
	Hair->SetScale(12.0f);
	Hair->SetText("Åäº¥ ¸Ó¸®");
	Hair->SetFontFlag(FW1_TEXT_FLAG::FW1_CENTER);
	Hair->GetTransform()->SetLocalPosition(InfoScrollPos + float4{ 21, 56 });

	Face->SetFont("±¼¸²");
	Face->SetColor({ 0, 0, 0, 1 });
	Face->SetScale(12.0f);
	Face->SetText("µµÀüÀûÀÎ ¾ó±¼");
	Face->SetFontFlag(FW1_TEXT_FLAG::FW1_CENTER);
	Face->GetTransform()->SetLocalPosition(InfoScrollPos + float4{ 21, 35 });

	Coat->SetFont("±¼¸²");
	Coat->SetColor({ 0, 0, 0, 1 });
	Coat->SetScale(12.0f);
	Coat->SetText("ÇÏ¾á ¹ÝÆÈ ¸éÆ¼");
	Coat->SetFontFlag(FW1_TEXT_FLAG::FW1_CENTER);
	Coat->GetTransform()->SetLocalPosition(InfoScrollPos + float4{ 21, 14 });
	
	Pants->SetFont("±¼¸²");
	Pants->SetColor({ 0, 0, 0, 1 });
	Pants->SetScale(12.0f);
	Pants->SetText("ÆÄ¶õ Ã» ¹Ý¹ÙÁö");
	Pants->SetFontFlag(FW1_TEXT_FLAG::FW1_CENTER);
	Pants->GetTransform()->SetLocalPosition(InfoScrollPos + float4{ 21, -7 });
	
	Shoes->SetFont("±¼¸²");
	Shoes->SetColor({ 0, 0, 0, 1 });
	Shoes->SetScale(12.0f);
	Shoes->SetText("°¡Á× »÷µé");
	Shoes->SetFontFlag(FW1_TEXT_FLAG::FW1_CENTER);
	Shoes->GetTransform()->SetLocalPosition(InfoScrollPos + float4{ 21, -28 });

	Weapon->SetFont("±¼¸²");
	Weapon->SetColor({ 0, 0, 0, 1 });
	Weapon->SetScale(12.0f);
	Weapon->SetText("°¡´Ï¾î");
	Weapon->SetFontFlag(FW1_TEXT_FLAG::FW1_CENTER);
	Weapon->GetTransform()->SetLocalPosition(InfoScrollPos + float4{ 21, -49 });

	LChangeCoat = GetLevel()->CreateActor<ContentButton>();
	LChangeCoat->SetReleaseTexture("LeftButtonRelease.png");
	LChangeCoat->SetHoverTexture("LeftButtonHover.png");
	LChangeCoat->SetPressTexture("LeftButtonPress.png");
	LChangeCoat->SetAllScale({ 15, 16 });
	LChangeCoat->SetisUIRenderer(false);
	LChangeCoat->SetAllPos(InfoScrollPos + float4{ -35, 6 });
	LChangeCoat->SetEvent([this]
		{
			CoatIndex--;

			if (CoatIndex < 0)
			{
				CoatIndex = (int)ClothesVec[static_cast<int>(EquipType::Coat)].size() - 1;
			}

			Coat->SetText(ClothesVec[static_cast<int>(EquipType::Coat)][CoatIndex].first);

			std::shared_ptr<ItemInfo> NewItem = std::make_shared<ItemInfo>();
			NewItem->EquipType = static_cast<int>(EquipType::Coat);
			NewItem->ItemName = ClothesVec[static_cast<int>(EquipType::Coat)][CoatIndex].second;

			Player::GetCurPlayer()->SetCoatName(ClothesVec[static_cast<int>(EquipType::Coat)][CoatIndex].second);
		});

	RChangeCoat = GetLevel()->CreateActor<ContentButton>();
	RChangeCoat->SetReleaseTexture("RightButtonRelease.png");
	RChangeCoat->SetHoverTexture("RightButtonHover.png");
	RChangeCoat->SetPressTexture("RightButtonPress.png");
	RChangeCoat->SetAllScale({ 15, 16 });
	RChangeCoat->SetisUIRenderer(false);
	RChangeCoat->SetAllPos(InfoScrollPos + float4{ 78, 6 });
	RChangeCoat->SetEvent([this]
		{
			CoatIndex++;
			if (CoatIndex >= (int)ClothesVec[static_cast<int>(EquipType::Coat)].size())
			{
				CoatIndex = 0;
			}
			Coat->SetText(ClothesVec[static_cast<int>(EquipType::Coat)][CoatIndex].first);

			std::shared_ptr<ItemInfo> NewItem = std::make_shared<ItemInfo>();
			NewItem->EquipType = static_cast<int>(EquipType::Coat);
			NewItem->ItemName = ClothesVec[static_cast<int>(EquipType::Coat)][CoatIndex].second;
			
			Player::GetCurPlayer()->SetCoatName(ClothesVec[static_cast<int>(EquipType::Coat)][CoatIndex].second);
		});

	LChangePants = GetLevel()->CreateActor<ContentButton>();
	LChangePants->SetReleaseTexture("LeftButtonRelease.png");
	LChangePants->SetHoverTexture("LeftButtonHover.png");
	LChangePants->SetPressTexture("LeftButtonPress.png");
	LChangePants->SetAllScale({ 15, 16 });
	LChangePants->SetisUIRenderer(false);
	LChangePants->SetAllPos(InfoScrollPos + float4{ -35, -14 });
	LChangePants->SetEvent([this]
		{
			PantsIndex--;

			if (PantsIndex < 0)
			{
				PantsIndex = (int)ClothesVec[static_cast<int>(EquipType::Pants)].size() - 1;
			}
			Pants->SetText(ClothesVec[static_cast<int>(EquipType::Pants)][PantsIndex].first);

			std::shared_ptr<ItemInfo> NewItem = std::make_shared<ItemInfo>();
			NewItem->EquipType = static_cast<int>(EquipType::Pants);
			NewItem->ItemName = ClothesVec[static_cast<int>(EquipType::Pants)][PantsIndex].second;

			Player::GetCurPlayer()->SetPantsName(ClothesVec[static_cast<int>(EquipType::Pants)][PantsIndex].second);
		});

	RChangePants = GetLevel()->CreateActor<ContentButton>();
	RChangePants->SetReleaseTexture("RightButtonRelease.png");
	RChangePants->SetHoverTexture("RightButtonHover.png");
	RChangePants->SetPressTexture("RightButtonPress.png");
	RChangePants->SetAllScale({ 15, 16 });
	RChangePants->SetisUIRenderer(false);
	RChangePants->SetAllPos(InfoScrollPos + float4{ 78, -14 });
	RChangePants->SetEvent([this]
		{
			PantsIndex++;
			if (PantsIndex >= (int)ClothesVec[static_cast<int>(EquipType::Pants)].size())
			{
				PantsIndex = 0;
			}
			Pants->SetText(ClothesVec[static_cast<int>(EquipType::Pants)][PantsIndex].first);

			std::shared_ptr<ItemInfo> NewItem = std::make_shared<ItemInfo>();
			NewItem->EquipType = static_cast<int>(EquipType::Pants);
			NewItem->ItemName = ClothesVec[static_cast<int>(EquipType::Pants)][PantsIndex].second;

			Player::GetCurPlayer()->SetPantsName(ClothesVec[static_cast<int>(EquipType::Pants)][PantsIndex].second);
		});

	LChangeShoes = GetLevel()->CreateActor<ContentButton>();
	LChangeShoes->SetReleaseTexture("LeftButtonRelease.png");
	LChangeShoes->SetHoverTexture("LeftButtonHover.png");
	LChangeShoes->SetPressTexture("LeftButtonPress.png");
	LChangeShoes->SetAllScale({ 15, 16 });
	LChangeShoes->SetisUIRenderer(false);
	LChangeShoes->SetAllPos(InfoScrollPos + float4{ -35, -34 });
	LChangeShoes->SetEvent([this]
		{
			ShoesIndex--;

			if (ShoesIndex < 0)
			{
				ShoesIndex = (int)ClothesVec[static_cast<int>(EquipType::Shoes)].size() - 1;
			}
			Shoes->SetText(ClothesVec[static_cast<int>(EquipType::Shoes)][ShoesIndex].first);

			std::shared_ptr<ItemInfo> NewItem = std::make_shared<ItemInfo>();
			NewItem->EquipType = static_cast<int>(EquipType::Shoes);
			NewItem->ItemName = ClothesVec[static_cast<int>(EquipType::Shoes)][ShoesIndex].second;

			Player::GetCurPlayer()->SetShoesName(ClothesVec[static_cast<int>(EquipType::Shoes)][ShoesIndex].second);
		});

	RChangeShoes = GetLevel()->CreateActor<ContentButton>();
	RChangeShoes->SetReleaseTexture("RightButtonRelease.png");
	RChangeShoes->SetHoverTexture("RightButtonHover.png");
	RChangeShoes->SetPressTexture("RightButtonPress.png");
	RChangeShoes->SetAllScale({ 15, 16 });
	RChangeShoes->SetisUIRenderer(false);
	RChangeShoes->SetAllPos(InfoScrollPos + float4{ 78, -34 });
	RChangeShoes->SetEvent([this]
		{
			ShoesIndex++;
			if (ShoesIndex >= (int)ClothesVec[static_cast<int>(EquipType::Shoes)].size())
			{
				ShoesIndex = 0;
			}
			Shoes->SetText(ClothesVec[static_cast<int>(EquipType::Shoes)][ShoesIndex].first);

			std::shared_ptr<ItemInfo> NewItem = std::make_shared<ItemInfo>();
			NewItem->EquipType = static_cast<int>(EquipType::Shoes);
			NewItem->ItemName = ClothesVec[static_cast<int>(EquipType::Shoes)][ShoesIndex].second;

			Player::GetCurPlayer()->SetShoesName(ClothesVec[static_cast<int>(EquipType::Shoes)][ShoesIndex].second);
		});

	LChangeFace = GetLevel()->CreateActor<ContentButton>();
	LChangeFace->SetReleaseTexture("LeftButtonRelease.png");
	LChangeFace->SetHoverTexture("LeftButtonHover.png");
	LChangeFace->SetPressTexture("LeftButtonPress.png");
	LChangeFace->SetAllScale({ 15, 16 });
	LChangeFace->SetisUIRenderer(false);
	LChangeFace->SetAllPos(InfoScrollPos + float4{ -35, 26 });
	LChangeFace->SetEvent([this]
		{
			FaceIndex--;

			if (FaceIndex < 0)
			{
				FaceIndex = (int)FaceVec.size() - 1;
			}

			Face->SetText(FaceVec[FaceIndex].first);
			PlayerValue::GetValue()->SetFace(FaceVec[FaceIndex].second);
		});

	RChangeShoes = GetLevel()->CreateActor<ContentButton>();
	RChangeShoes->SetReleaseTexture("RightButtonRelease.png");
	RChangeShoes->SetHoverTexture("RightButtonHover.png");
	RChangeShoes->SetPressTexture("RightButtonPress.png");
	RChangeShoes->SetAllScale({ 15, 16 });
	RChangeShoes->SetisUIRenderer(false);
	RChangeShoes->SetAllPos(InfoScrollPos + float4{ 78, 26 });
	RChangeShoes->SetEvent([this]
		{
			FaceIndex++;

			if (FaceIndex >= (int)FaceVec.size())
			{
				FaceIndex = 0;
			}

			Face->SetText(FaceVec[FaceIndex].first);
			PlayerValue::GetValue()->SetFace(FaceVec[FaceIndex].second);
		});
}

void TitleObjects::RollStatDice()
{
	if (GameEngineInput::IsDown("LClick") == true)
	{
		if (DiceCol->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D) != nullptr)
		{
			GameEngineSound::Play("ButtonClick.mp3");
			Dice->ChangeAnimation("Rolling");
			DiceCol->Off();
		}
	}
}

void TitleObjects::StatChange()
{
	Counting += TimeCount;

	int StrStat = 0;
	int DexStat = 0;
	int IntStat = 0;
	int LukStat = 0;

	if (Counting >= 0.03f)
	{
		Counting = 0.0f;

		int MaxSumStat = 28;

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

		PlayerValue::GetValue()->SetStr(StrStat);
		PlayerValue::GetValue()->SetDex(DexStat);
		PlayerValue::GetValue()->SetInt(IntStat);
		PlayerValue::GetValue()->SetLuk(LukStat);
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
	ChScroll->SetAnimationStartEvent("Akenia", 0, [this] {isChScrollOpen = true; AllChColOff(); });
	ChScroll->SetAnimationStartEvent("Akenia", 1, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 617 }); });
	ChScroll->SetAnimationStartEvent("Akenia", 2, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 613 }); AllChColOn(); });

	ChScroll->CreateAnimation({ .AnimationName = "Bera",.SpriteName = "Bera",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ChScroll->SetAnimationStartEvent("Bera", 0, [this] {isChScrollOpen = true; AllChColOff(); });
	ChScroll->SetAnimationStartEvent("Bera", 1, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 617 }); });
	ChScroll->SetAnimationStartEvent("Bera", 2, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 613 }); AllChColOn(); });
	
	ChScroll->CreateAnimation({ .AnimationName = "Broa",.SpriteName = "Broa",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ChScroll->SetAnimationStartEvent("Broa", 0, [this] {isChScrollOpen = true; AllChColOff(); });
	ChScroll->SetAnimationStartEvent("Broa", 1, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 617 }); });
	ChScroll->SetAnimationStartEvent("Broa", 2, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 613 }); AllChColOn(); });

	ChScroll->CreateAnimation({ .AnimationName = "Croa",.SpriteName = "Croa",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ChScroll->SetAnimationStartEvent("Croa", 0, [this] {isChScrollOpen = true; AllChColOff(); });
	ChScroll->SetAnimationStartEvent("Croa", 1, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 617 }); });
	ChScroll->SetAnimationStartEvent("Croa", 2, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 613 }); AllChColOn(); });

	ChScroll->CreateAnimation({ .AnimationName = "Demetos",.SpriteName = "Demetos",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ChScroll->SetAnimationStartEvent("Demetos", 0, [this] {isChScrollOpen = true; AllChColOff(); });
	ChScroll->SetAnimationStartEvent("Demetos", 1, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 617 }); });
	ChScroll->SetAnimationStartEvent("Demetos", 2, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 613 }); AllChColOn(); });

	ChScroll->CreateAnimation({ .AnimationName = "Kastia",.SpriteName = "Kastia",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ChScroll->SetAnimationStartEvent("Kastia", 0, [this] {isChScrollOpen = true; AllChColOff(); });
	ChScroll->SetAnimationStartEvent("Kastia", 1, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 617 }); });
	ChScroll->SetAnimationStartEvent("Kastia", 2, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 613 }); AllChColOn(); });

	ChScroll->CreateAnimation({ .AnimationName = "Khaini",.SpriteName = "Khaini",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ChScroll->SetAnimationStartEvent("Khaini", 0, [this] {isChScrollOpen = true; AllChColOff();  });
	ChScroll->SetAnimationStartEvent("Khaini", 1, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 617 }); });
	ChScroll->SetAnimationStartEvent("Khaini", 2, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 613 }); AllChColOn(); });

	ChScroll->CreateAnimation({ .AnimationName = "Mardia",.SpriteName = "Mardia",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ChScroll->SetAnimationStartEvent("Mardia", 0, [this] {isChScrollOpen = true; AllChColOff();  });
	ChScroll->SetAnimationStartEvent("Mardia", 1, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 617 }); });
	ChScroll->SetAnimationStartEvent("Mardia", 2, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 613 }); AllChColOn(); });

	ChScroll->CreateAnimation({ .AnimationName = "Plana",.SpriteName = "Plana",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ChScroll->SetAnimationStartEvent("Plana", 0, [this] {isChScrollOpen = true; AllChColOff();  });
	ChScroll->SetAnimationStartEvent("Plana", 1, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 617 }); });
	ChScroll->SetAnimationStartEvent("Plana", 2, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 613 }); AllChColOn(); });

	ChScroll->CreateAnimation({ .AnimationName = "Skania",.SpriteName = "Skania",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ChScroll->SetAnimationStartEvent("Skania", 0, [this] {isChScrollOpen = true; AllChColOff();  });
	ChScroll->SetAnimationStartEvent("Skania", 1, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 617 }); });
	ChScroll->SetAnimationStartEvent("Skania", 2, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 613 }); AllChColOn(); });

	ChScroll->CreateAnimation({ .AnimationName = "Stierce",.SpriteName = "Stierce",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ChScroll->SetAnimationStartEvent("Stierce", 0, [this] {isChScrollOpen = true; AllChColOff();  });
	ChScroll->SetAnimationStartEvent("Stierce", 1, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 617 }); });
	ChScroll->SetAnimationStartEvent("Stierce", 2, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 613 }); AllChColOn(); });

	ChScroll->CreateAnimation({ .AnimationName = "Yellond",.SpriteName = "Yellond",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ChScroll->SetAnimationStartEvent("Yellond", 0, [this] {isChScrollOpen = true; AllChColOff(); });
	ChScroll->SetAnimationStartEvent("Yellond", 1, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 617 }); });
	ChScroll->SetAnimationStartEvent("Yellond", 2, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 613 }); AllChColOn(); });

	ChScroll->CreateAnimation({ .AnimationName = "Zenis",.SpriteName = "Zenis",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	ChScroll->SetAnimationStartEvent("Zenis", 0, [this] {isChScrollOpen = true; AllChColOff();  });
	ChScroll->SetAnimationStartEvent("Zenis", 1, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 617 }); });
	ChScroll->SetAnimationStartEvent("Zenis", 2, [this] {ChScroll->GetTransform()->SetLocalPosition({ 0, 613 }); AllChColOn(); });

}

void TitleObjects::SetChCollision()
{
	ChColVec.reserve(20);

	for (int i = 0; i < 20; i++)
	{
		std::shared_ptr<GameEngineCollision> NewCol = CreateComponent<GameEngineCollision>();
		
		NewCol->SetColType(ColType::AABBBOX2D);
		NewCol->SetOrder(static_cast<int>(CollisionOrder::Channel));
		NewCol->GetTransform()->SetLocalScale({ 92, 30 });
		NewCol->GetTransform()->SetLocalPosition({ -139 + ((i % 4) * 97.0f), 603 - ((i / 4) * 32.0f)});
		NewCol->Off();

		ChColVec.push_back(NewCol);
	}

	ChannelCheck->On();
}

void TitleObjects::AllChColOn()
{
	for (int i = 0; i < 20; i++)
	{
		ChColVec[i]->On();
	}
}

void TitleObjects::AllChColOff()
{
	for (int i = 0; i < 20; i++)
	{
		ChColVec[i]->Off();
	}

	ChannelCheck->Off();
	SelectedChannel = nullptr;
}

void TitleObjects::ChannelChecking()
{
	std::shared_ptr<Mouse> MyMouse = Mouse::GetMouse();
	std::shared_ptr<GameEngineCollision> Col = MyMouse->GetMouseCollision()->Collision(static_cast<int>(CollisionOrder::Channel), ColType::AABBBOX2D, ColType::AABBBOX2D);
	
	if (Col != nullptr)
	{
		if(Col != SelectedChannel && GameEngineInput::IsDown("LClick") == true)
		{
			ChannelCheck->On();
			ChannelCheck->ChangeAnimation("Check");
			ChannelCheck->GetTransform()->SetWorldPosition(Col->GetTransform()->GetWorldPosition() + float4{ -22.0f, 7.0f });
			SelectedChannel = Col;
			GameEngineSound::Play("ChannelCheck.mp3");
		}
		else if(Col == SelectedChannel && MyMouse->IsDoubleClick() == true)
		{
			if(MyMouse->IsDoubleClick() == true)
			{
				ChannelClickFunc();
			}
		}
	}
}