#include "PrecompileHeader.h"
#include "Level_Title.h"
#include "Logo.h"
#include "Player.h"
#include "TitleObjects.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineShader.h>
#include <GameEnginePlatform/GameEngineInput.h>

Level_Title::Level_Title()
{
}

Level_Title::~Level_Title()
{
}

void Level_Title::Start()
{
	SetName("TITLE");

	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });


		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, 0.0f });


	//std::shared_ptr<Player> _Player = CreateActor<Player>();
	
	//std::shared_ptr<Logo> GameLogo = CreateActor<Logo>();
	std::shared_ptr<TitleObjects> NewTitleObjects = CreateActor<TitleObjects>();
	std::shared_ptr<Player> NewPlayer = CreateActor<Player>();

	NewPlayer->GetTransform()->SetLocalPosition({ -20, 1768 });
	NewPlayer->SetRight();

	//std::shared_ptr<Test> NewTitleObjects = CreateActor<Test>();
}

void Level_Title::Update(float _DeltaTime)
{
	CameraMove(_DeltaTime);
}

void Level_Title::CameraMove(float _DeltaTime)
{
	if (GameEngineInput::IsKey("CameraUp") == false)
	{
		GameEngineInput::CreateKey("CameraUp", 'W');
	}

	if (GameEngineInput::IsDown("CameraUp") == true)
	{
		if (CameraIndex >= 3 || isCamDown == true)
		{
			return;
		}

		isCamUp = true;
	}

	if (GameEngineInput::IsKey("CameraDown") == false)
	{
		GameEngineInput::CreateKey("CameraDown", 'S');
	}

	if (GameEngineInput::IsDown("CameraDown") == true)
	{
		if (CameraIndex <= 0 || isCamDown == true)
		{
			return;
		}

		isCamDown = true;
	}

	if (isCamUp == true)
	{
		DestiPos = { 0,(CameraIndex + 1) * 600.0f };
		CamPos = GetMainCamera()->GetTransform()->GetLocalPosition();

		LerpRatio += _DeltaTime * LerpSpeed;
		GetMainCamera()->GetTransform()->SetLocalPosition(LerpCamPos.LerpClamp(CamPos, DestiPos, LerpRatio));

		if (LerpRatio >= 1.0f)
		{
			isCamUp = false;
			GetMainCamera()->GetTransform()->SetLocalPosition({ 0,(CameraIndex + 1) * 600.0f });
			CameraIndex++;
			LerpRatio = 0.0f;
		}
	}

	if (isCamDown == true)
	{
		DestiPos = { 0,(CameraIndex - 1) * 600.0f };
		CamPos = GetMainCamera()->GetTransform()->GetLocalPosition();

		LerpRatio += _DeltaTime * LerpSpeed;
		GetMainCamera()->GetTransform()->SetLocalPosition(LerpCamPos.LerpClamp(CamPos, DestiPos, LerpRatio));

		if (LerpRatio >= 1.0f)
		{
			isCamDown = false;
			GetMainCamera()->GetTransform()->SetLocalPosition({ 0,(CameraIndex - 1) * 600.0f });
			CameraIndex--;
			LerpRatio = 0.0f;
		}
	}
}