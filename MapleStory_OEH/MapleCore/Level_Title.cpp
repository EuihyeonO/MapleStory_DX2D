#include "PrecompileHeader.h"
#include "Level_Title.h"
#include "Logo.h"
#include "Player.h"
#include "Mouse.h"
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
	GameEngineFont::Load("굴림");

	SetName("TITLE");

	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("NotSprite");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });


		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}


	if (nullptr == GameEngineSprite::Find("SmallZakum1Fly"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("UI");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("StatDiceRoll").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DiceStand").GetFullPath());
	}

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, 0.0f });
	GetMainCamera()->SetSortType(0, SortType::ZSort);

	//GameLogo = CreateActor<Logo>();

	std::shared_ptr<TitleObjects> NewTitleObjects = CreateActor<TitleObjects>();
	std::shared_ptr<Player> NewPlayer = CreateActor<Player>();

	NewPlayer->GetTransform()->SetLocalPosition({ -20, 1768, -1 });
	NewPlayer->SetRight();

	MyMouse = CreateActor<Mouse>(static_cast<int>(RenderOrder::UI));
	MyMouse->SetCurMouse(MyMouse);

	if (GameEngineInput::IsKey("CameraUp") == false)
	{
		GameEngineInput::CreateKey("CameraUp", 'W');
	}

	if (GameEngineInput::IsKey("CameraDown") == false)
	{
		GameEngineInput::CreateKey("CameraDown", 'S');
	}

	if (GameEngineInput::IsKey("LevelChange1") == false)
	{
		GameEngineInput::CreateKey("LevelChange1", '1');
		GameEngineInput::CreateKey("LevelChange2", '2');
		GameEngineInput::CreateKey("LevelChange3", '3');
		GameEngineInput::CreateKey("LevelChange4", '4');
	}

}

void Level_Title::Update(float _DeltaTime)
{
	if (GameLogo != nullptr && GameLogo->GetIsCreateObject() == true)
	{
		GameLogo->Death();
		GameLogo = nullptr;

	}

	if (GameEngineInput::IsDown("LevelChange1") == true)
	{
		GameEngineCore::ChangeLevel("Level_BeginnersTown1");
	}
	else if (GameEngineInput::IsDown("LevelChange2") == true)
	{
		GameEngineCore::ChangeLevel("Level_BeginnersTown2");
	}
	else if (GameEngineInput::IsDown("LevelChange3") == true)
	{
		GameEngineCore::ChangeLevel("Level_CrossRoad");
	}
	else if (GameEngineInput::IsDown("LevelChange4") == true)
	{
		GameEngineCore::ChangeLevel("Level_AlterOfZakum");
	}

	CameraMove(_DeltaTime);
}

void Level_Title::CameraMove(float _DeltaTime)
{
	if (GameLogo != nullptr)
	{
		return;
	}

	if (GameEngineInput::IsDown("CameraUp") == true)
	{
		if (CameraIndex >= 3 || isCamDown == true)
		{
			return;
		}

		isCamUp = true;
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

void Level_Title::LevelChangeStart()
{
	if(MyMouse != nullptr)
	{
		MyMouse->SetCurMouse(MyMouse);
	}
}

void Level_Title::LevelChangeEnd()
{
	//캐릭터 데스해버리기
	//PlayerList에서도 erase해야함
}