#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
class Test : public GameEngineActor
{

public:

	Test();
	~Test();

	Test(const Test& _Other) = delete;
	Test(Test&& _Other) noexcept = delete;
	Test& operator=(const Test& _Other) = delete;
	Test& operator=(Test&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	std::shared_ptr<GameEngineSpriteRenderer> LoginBoard;

};

