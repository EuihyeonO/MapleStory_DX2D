#pragma once
#include <GameEngineCore/GameEngineActor.h>

class KeyBox : public GameEngineActor
{

public:

	KeyBox();
	~KeyBox();

	KeyBox(const KeyBox& _Other) = delete;
	KeyBox(KeyBox&& _Other) noexcept = delete;
	KeyBox& operator=(const KeyBox& _Other) = delete;
	KeyBox& operator=(KeyBox&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	std::shared_ptr<class GameEngineSpriteRenderer> BoxRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BoxCollision = nullptr;

	int count = 0;
};

