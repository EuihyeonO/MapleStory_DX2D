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

	//���콺 ��ġ�� �޾ƿ��� �Լ� ���� ���� ��?

}

void Mouse::Update(float _DeltaTime)
{
}

void Mouse::Render(float _DeltaTime)
{
}