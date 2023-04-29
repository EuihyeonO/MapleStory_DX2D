#include "PrecompileHeader.h"
#include "Mouse.h"
#include <gameengineCore/GameEngineSpriteRenderer.h>
#include <gameengineCore/GameEngineLevel.h>

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
}

void Mouse::Start()
{

	ToLogin = CreateComponent<GameEngineSpriteRenderer>();
	ToLogin->SetTexture("Cursor.png");

	//마우스 위치를 받아오는 함수 아직 없는 듯?

}

void Mouse::Update(float _DeltaTime)
{
}

void Mouse::Render(float _DeltaTime)
{
}