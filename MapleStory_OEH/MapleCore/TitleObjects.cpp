#include "PrecompileHeader.h"
#include "TitleObjects.h"
#include <gameengineCore/GameEngineLevel.h>
#include <gameengineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>

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

	Create_ChannelButton();
	Create_CharSelectButton();
	Create_CharacterObject();
	Create_CharCreateObject();

	Frame = CreateComponent<GameEngineSpriteRenderer>();
	Frame->SetTexture("Frame.png");
	Frame->GetTransform()->SetLocalScale({ 800, 600 });

	Create_FrameObject();
}

void TitleObjects::Update(float _DeltaTime)
{
	TimeCounting();
	EmptySlotAnimation();

	//Frame 고정
	float4 CamPos = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();
	Frame->GetTransform()->SetLocalPosition(CamPos);
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

	SignUp = CreateComponent<GameEngineSpriteRenderer>();
	SignUp->SetTexture("SignUpRelease.png");
	SignUp->GetTransform()->SetLocalScale({ 92, 43 });
	SignUp->GetTransform()->SetLocalPosition(LoginBoardPos + float4{-68, -44});

	HomePage = CreateComponent<GameEngineSpriteRenderer>();
	HomePage->SetTexture("HomePageRelease.png");
	HomePage->GetTransform()->SetLocalScale({ 93, 43 });
	HomePage->GetTransform()->SetLocalPosition(LoginBoardPos + float4{ 33, -44 });

	Exit = CreateComponent<GameEngineSpriteRenderer>();
	Exit->SetTexture("ExitRelease.png");
	Exit->GetTransform()->SetLocalScale({ 84, 43 });
	Exit->GetTransform()->SetLocalPosition(LoginBoardPos + float4{ 127, -42 });

	Login = CreateComponent<GameEngineSpriteRenderer>();
	Login->SetTexture("LoginRelease.png");
	Login->GetTransform()->SetLocalScale({ 95, 48 });
	Login->GetTransform()->SetLocalPosition(LoginBoardPos + float4{ 128, 70 });

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
	Zenis = CreateComponent<GameEngineSpriteRenderer>();
	Zenis->SetTexture("ZenisRelease.png");
	Zenis->GetTransform()->SetLocalScale({ 28, 95 });
	Zenis->GetTransform()->SetLocalPosition({ -180, 752 });

	Kastia = CreateComponent<GameEngineSpriteRenderer>();
	Kastia->SetTexture("KastiaRelease.png");
	Kastia->GetTransform()->SetLocalScale({ 28, 95 });
	Kastia->GetTransform()->SetLocalPosition({ -150, 752 });

	Kiny = CreateComponent<GameEngineSpriteRenderer>();
	Kiny->SetTexture("KinyRelease.png");
	Kiny->GetTransform()->SetLocalScale({ 28, 95 });
	Kiny->GetTransform()->SetLocalPosition({ -120, 752 });

	Croa = CreateComponent<GameEngineSpriteRenderer>();
	Croa->SetTexture("CroaRelease.png");
	Croa->GetTransform()->SetLocalScale({ 28, 95 });
	Croa->GetTransform()->SetLocalPosition({ -90, 752 });

	Yellond = CreateComponent<GameEngineSpriteRenderer>();
	Yellond->SetTexture("YellondRelease.png");
	Yellond->GetTransform()->SetLocalScale({ 28, 95 });
	Yellond->GetTransform()->SetLocalPosition({ -60, 752 });

	Plana = CreateComponent<GameEngineSpriteRenderer>();
	Plana->SetTexture("PlanaRelease.png");
	Plana->GetTransform()->SetLocalScale({ 28, 95 });
	Plana->GetTransform()->SetLocalPosition({ -30, 752 });

	Demetos = CreateComponent<GameEngineSpriteRenderer>();
	Demetos->SetTexture("DemetosRelease.png");
	Demetos->GetTransform()->SetLocalScale({ 28, 95 });
	Demetos->GetTransform()->SetLocalPosition({ 0, 752 });

	Akenia = CreateComponent<GameEngineSpriteRenderer>();
	Akenia->SetTexture("AkeniaRelease.png");
	Akenia->GetTransform()->SetLocalScale({ 28, 95 });
	Akenia->GetTransform()->SetLocalPosition({ 30, 752 });

	Bera = CreateComponent<GameEngineSpriteRenderer>();
	Bera->SetTexture("BeraRelease.png");
	Bera->GetTransform()->SetLocalScale({ 28, 95 });
	Bera->GetTransform()->SetLocalPosition({ 60, 752 });

	Broa = CreateComponent<GameEngineSpriteRenderer>();
	Broa->SetTexture("BroaRelease.png");
	Broa->GetTransform()->SetLocalScale({ 28, 95 });
	Broa->GetTransform()->SetLocalPosition({ 90, 752 });

	Mardia = CreateComponent<GameEngineSpriteRenderer>();
	Mardia->SetTexture("MardiaRelease.png");
	Mardia->GetTransform()->SetLocalScale({ 28, 95 });
	Mardia->GetTransform()->SetLocalPosition({ 120, 752 });

	Skania = CreateComponent<GameEngineSpriteRenderer>();
	Skania->SetTexture("SkaniaRelease.png");
	Skania->GetTransform()->SetLocalScale({ 28, 95 });
	Skania->GetTransform()->SetLocalPosition({ 150, 752 });

	Stierce = CreateComponent<GameEngineSpriteRenderer>();
	Stierce->SetTexture("StierceRelease.png");
	Stierce->GetTransform()->SetLocalScale({ 28, 95 });
	Stierce->GetTransform()->SetLocalPosition({ 180, 752 });
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
	//추후에 캐릭터가 있을 때는 이 렌더러를 어떻게 해야하는지 고민 후 변경을 해야할 듯

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

void TitleObjects::TimeCounting()
{
	CurTime = static_cast<float>(clock());

	TimeCount = (CurTime - PrevTime) / 1000.0f;

	PrevTime = CurTime;
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
	//추후에 구현하자
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

	OkButton = CreateComponent<GameEngineSpriteRenderer>();
	OkButton->SetTexture("OkRelease.png");
	OkButton->GetTransform()->SetLocalScale({ 76, 41 });
	OkButton->GetTransform()->SetLocalPosition(CharInfoPos + float4{ -34, -140 });

	NoButton = CreateComponent<GameEngineSpriteRenderer>();
	NoButton->SetTexture("NoRelease.png");
	NoButton->GetTransform()->SetLocalScale({ 81, 41 });
	NoButton->GetTransform()->SetLocalPosition(CharInfoPos + float4{ 43, -140 });
}