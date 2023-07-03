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
#include <GameEnginePlatform/GameEngineSound.h>

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
		NewDir.Move("Common");
		NewDir.Move("CommonNotSprite");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}

		NewDir.MoveParent();
		NewDir.Move("CommonSprite");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Portal").GetFullPath());
	}


	if (nullptr == GameEngineSprite::Find("StatDiceRoll"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("TitleLevel");
		NewDir.Move("TitleNotSprite");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}

		NewDir.MoveParent();
		NewDir.Move("TitleSprite");
		NewDir.Move("UI");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("StatDiceRoll").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DiceStand").GetFullPath());

		NewDir.Move("ChannelScroll");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Akenia").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bera").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Broa").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croa").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Demetos").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Kastia").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Khaini").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mardia").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Plana").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Skania").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Stierce").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Yellond").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Zenis").GetFullPath());

		NewDir.MoveParent();
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ChannelCheck").GetFullPath());
		NewDir.MoveParent();
		NewDir.Move("TitleLight");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TitleLight0").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TitleLight1").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TitleLight2").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TitleLight3").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TitleLight4").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TitleLight5").GetFullPath());
	}


	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sound");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".mp3", });

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineSound::Load(File[i].GetFullPath());
		}
	}

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetCamera(100)->SetProjectionType(CameraType::Orthogonal);

	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, 0.0f });
	
	GetMainCamera()->SetSortType(0, SortType::ZSort);
	GetCamera(100)->SetSortType(0, SortType::ZSort);

	GameLogo = CreateActor<Logo>();
	//std::shared_ptr<TitleObjects> NewTitleObjects1 = CreateActor<TitleObjects>();

	//MyPlayer = CreateActor<Player>();
	//MyPlayer->GetTransform()->SetLocalPosition({ -20, 1768, -1 });
	//MyPlayer->SetRight();

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
		//콜백형식으로 바꿔서 Logo에서 알아서 처리하도록 설정, nullptr을 넣어줄 필요 없게 아예 start에 선언된 지역변수에서 처리
		TitlePlayer = GameEngineSound::Play("Title.mp3");
		TitlePlayer.SetLoop(-1);
		TitlePlayer.SetVolume(0.3f);

		NewTitleObjects = CreateActor<TitleObjects>();
		NewTitleObjects->SetLoginBtEvent([this]
			{
				isCamUp = true;
			});

		NewTitleObjects->SetChannelClickFunc([this] {isCamUp = true; });

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
	if (nullptr == GameEngineSprite::Find("StatDiceRoll"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("TitleLevel");
		NewDir.Move("TitleNotSprite");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}

		NewDir.MoveParent();
		NewDir.Move("TitleSprite");
		NewDir.Move("UI");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("StatDiceRoll").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DiceStand").GetFullPath());

		NewDir.Move("ChannelScroll");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Akenia").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Bera").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Broa").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Croa").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Demetos").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Kastia").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Khaini").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Mardia").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Plana").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Skania").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Stierce").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Yellond").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Zenis").GetFullPath());

		NewDir.MoveParent();
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ChannelCheck").GetFullPath());

		NewDir.MoveParent();
		NewDir.Move("Title");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TitleLight0").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TitleLight1").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TitleLight2").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TitleLight3").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TitleLight4").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TitleLight5").GetFullPath());
	}
}

void Level_Title::LevelChangeEnd()
{
	if (nullptr != GameEngineSprite::Find("StatDiceRoll"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("TitleLevel");
		NewDir.Move("TitleNotSprite");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			std::string FileFullPath = File[i].GetFullPath();
			std::string FileName = "";
			size_t Count = 0;

			for (Count = FileFullPath.size(); Count > 0; Count--)
			{
				char a = FileFullPath[Count];
				if (FileFullPath[Count] == '\\')
				{
					break;
				}
			}

			for (size_t j = Count + 1; j < FileFullPath.size(); j++)
			{
				FileName.push_back(FileFullPath[j]);
			}

 			GameEngineTexture::UnLoad(FileName);
		}

		NewDir.MoveParent();
		NewDir.Move("TitleSprite");
		NewDir.Move("UI");

		GameEngineSprite::UnLoad("StatDiceRoll");
		GameEngineSprite::UnLoad("DiceStand");

		NewDir.Move("ChannelScroll");

		GameEngineSprite::UnLoad("Akenia");
		GameEngineSprite::UnLoad("Bera");
		GameEngineSprite::UnLoad("Broa");
		GameEngineSprite::UnLoad("Croa");
		GameEngineSprite::UnLoad("Demetos");
		GameEngineSprite::UnLoad("Kastia");
		GameEngineSprite::UnLoad("Khaini");
		GameEngineSprite::UnLoad("Mardia");
		GameEngineSprite::UnLoad("Plana");
		GameEngineSprite::UnLoad("Skania");
		GameEngineSprite::UnLoad("Stierce");
		GameEngineSprite::UnLoad("Yellond");
		GameEngineSprite::UnLoad("Zenis");

		NewDir.MoveParent();
		GameEngineSprite::UnLoad("ChannelCheck");

		NewDir.MoveParent();
		NewDir.Move("TitleLight");

		GameEngineSprite::UnLoad("TitleLight0");
		GameEngineSprite::UnLoad("TitleLight1");
		GameEngineSprite::UnLoad("TitleLight2");
		GameEngineSprite::UnLoad("TitleLight3");
		GameEngineSprite::UnLoad("TitleLight4");
		GameEngineSprite::UnLoad("TitleLight5");
	}
	
	MyPlayer->Death();
	//NewTitleObjects->Death();
	MyMouse->Death();

	TitlePlayer.Stop();
	//캐릭터 데스해버리기
	//PlayerList에서도 erase해야함
}