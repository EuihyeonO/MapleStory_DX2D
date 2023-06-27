#include "PrecompileHeader.h"
#include "Level_ZakumRoad1.h"
#include "ZakumRoad1.h"

Level_ZakumRoad1::Level_ZakumRoad1()
{
}

Level_ZakumRoad1::~Level_ZakumRoad1()
{
}

void Level_ZakumRoad1::Start()
{
	SetName("ZAKUMROAD1");

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetCamera(100)->SetProjectionType(CameraType::Orthogonal);

	GetMainCamera()->SetSortType(0, SortType::ZSort);
	GetCamera(100)->SetSortType(0, SortType::ZSort);
}

void Level_ZakumRoad1::Update(float _DeltaTime)
{

}

void Level_ZakumRoad1::LevelChangeStart()
{
	LoadResources();
	ActorCreate();
}

void Level_ZakumRoad1::LevelChangeEnd()
{
	ActorDeath();
	UnLoadResources();
}



void Level_ZakumRoad1::ActorCreate()
{
	Map = CreateActor<ZakumRoad1>();
}

void Level_ZakumRoad1::ActorDeath()
{
	if (Map != nullptr)
	{
		Map->Death();
		Map = nullptr;
	}
}

void Level_ZakumRoad1::LoadResources()
{
	if (nullptr == GameEngineTexture::Find("ZakumRoad1.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("ZakumRoad1");
		NewDir.Move("ZakumRoad1NotSprite");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}
	else
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("ZakumRoad1");
		NewDir.Move("ZakumRoad1NotSprite");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::ReLoad(File[i].GetFullPath());
		}
	}
}

void Level_ZakumRoad1::UnLoadResources()
{
	if (nullptr != GameEngineTexture::Find("ZakumRoad1.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("ZakumRoad1");
		NewDir.Move("ZakumRoad1NotSprite");

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
	}
}

