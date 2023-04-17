#include "PrecompileHeader.h"
#include "Level_Title.h"
#include "Test.h"
#include <GameEngineCore/GameEngineCamera.h>

Level_Title::Level_Title()
{
}

Level_Title::~Level_Title()
{
}

void Level_Title::Start()
{
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	std::shared_ptr<Test> NewPlayer = CreateActor<Test>("Test");


}