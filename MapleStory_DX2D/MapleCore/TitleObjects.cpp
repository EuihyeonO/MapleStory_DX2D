#include "PrecompileHeader.h"
#include "TitleObjects.h"
#include <gameengineCore/GameEngineSpriteRenderer.h>
#include <gameengineCore/GameEngineLevel.h>
#include <gameengineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>

TitleObjects::TitleObjects()
{
}

TitleObjects::~TitleObjects()
{
}

void TitleObjects::Start()
{
	
	BackGround = CreateComponent<GameEngineSpriteRenderer>();
	BackGround->SetTexture("FullBackGround.png");
	BackGround->GetTransform()->SetLocalScale({ 800, 2396 });
	BackGround->GetTransform()->SetLocalPosition({ -40, 900 });

	CreateLoginBox();

	Logo = CreateComponent<GameEngineSpriteRenderer>();
	Logo->SetTexture("TitleLogo.png");
	Logo->GetTransform()->SetLocalScale({ 397, 219 });
	Logo->GetTransform()->SetLocalPosition({ 0, 175 });

	ChScroll = CreateComponent<GameEngineSpriteRenderer>();
	ChScroll->SetTexture("Scroll.png");
	ChScroll->GetTransform()->SetLocalScale({ 513, 152 });
	ChScroll->GetTransform()->SetLocalPosition({ 0,745});

	CreateChannelButton();

	Frame = CreateComponent<GameEngineSpriteRenderer>();
	Frame->SetTexture("Frame.png");
	Frame->GetTransform()->SetLocalScale({ 800, 600 });
}

void TitleObjects::Update(float _DeltaTime)
{
	float4 CamPos = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();
	Frame->GetTransform()->SetLocalPosition(CamPos);

	if (GameEngineInput::IsKey("Scorll") == false)
	{
		GameEngineInput::CreateKey("Scorll", 'E');
	}

	if (GameEngineInput::IsDown("Scorll") == true)
	{
		ScrollIndex++;
		std::string Name = "ScrollOpen" + std::to_string(ScrollIndex) + ".png";
		ChScroll->SetTexture(Name);
		//스크롤 이미지 크기가 조금씩 다름 ( 나중에 수정해야 함 )
		ChScroll->GetTransform()->SetLocalScale({ 513, 401 });
		ChScroll->GetTransform()->SetLocalPosition({ 0,620 });
	}

}

void TitleObjects::Render(float _DeltaTime)
{

}

void TitleObjects::CreateLoginBox()
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

void TitleObjects::CreateChannelButton()
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