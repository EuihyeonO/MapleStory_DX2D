#include "PrecompileHeader.h"
#include "Test.h"
#include <gameengineCore/GameEngineSpriteRenderer.h>
#include <gameengineCore/GameEngineLevel.h>
#include <gameengineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>

Test::Test()
{
}

Test::~Test()
{
}

void Test::Start()
{		
	LoginBoard = CreateComponent<GameEngineSpriteRenderer>();
	LoginBoard->SetTexture("LoginBox.png");
	LoginBoard->GetTransform()->SetLocalScale({ 368, 236 });
	LoginBoard->GetTransform()->SetLocalPosition({ 100, -40 });
}		
		
void Test::Update(float _DeltaTime)
{		
		
}		
		
void Test::Render(float _DeltaTime)
{

}