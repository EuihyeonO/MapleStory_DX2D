#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Test : public GameEngineActor
{
public:
	// constrcuter destructer
	Test();
	~Test();

	// delete Function
	Test(const Test& _Other) = delete;
	Test(Test&& _Other) noexcept = delete;
	Test& operator=(const Test& _Other) = delete;
	Test& operator=(Test&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:
	float Angle = 0.0f;
	std::shared_ptr<class GameEngineRenderer> Render0;
	std::shared_ptr<class GameEngineRenderer> Render1;
	std::shared_ptr<class GameEngineRenderer> Render2;

};

