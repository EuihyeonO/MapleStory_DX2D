#include "PrecompileHeader.h"
#include "Level_Title.h"
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

	std::shared_ptr<TitleObjects> NewTitleObjects = CreateActor<TitleObjects>();
}

void Level_Title::Update(float _DeltaTime)
{
	if (GameEngineInput::IsKey("CameraUp") == false)
	{
		GameEngineInput::CreateKey("CameraUp", 'W');
	}

	if (GameEngineInput::IsDown("CameraUp") == true)
	{
		isCamUp = true;
	}

	if (isCamUp == true && isCamSet == false)
	{
		float4 CamPos = GetMainCamera()->GetTransform()->GetWorldPosition();

		GetMainCamera()->GetTransform()->SetWorldPosition({ CamPos.x, CamPos.y + 3500.0f * _DeltaTime, CamPos.z });

		float4 CurCamPos = GetMainCamera()->GetTransform()->GetWorldPosition();

		if (CurCamPos.y >= 600.0f)
		{
			float4 CurCamPos = GetMainCamera()->GetTransform()->GetWorldPosition();

			GetMainCamera()->GetTransform()->SetWorldPosition({ CurCamPos.x, 600.0f, CurCamPos.z });
			isCamSet = true;
		}
	}

	if (isCamUp == true && isCamSet == true)
	{

		if (GameEngineInput::IsDown("CameraUp") == true)
		{
			isCam2Up = true;
		}
	}
	
	if(isCam2Up == true && isCam2Set == false)
	{
		float4 CamPos = GetMainCamera()->GetTransform()->GetWorldPosition();

		GetMainCamera()->GetTransform()->SetWorldPosition({ CamPos.x, CamPos.y + 3500.0f * _DeltaTime, CamPos.z });

		float4 CurCamPos = GetMainCamera()->GetTransform()->GetWorldPosition();

		if (CurCamPos.y >= 1200.0f)
		{
			float4 CurCamPos = GetMainCamera()->GetTransform()->GetWorldPosition();

			GetMainCamera()->GetTransform()->SetWorldPosition({ CurCamPos.x, 1200.0f, CurCamPos.z });
			isCam2Set = true;
		}
	}
}