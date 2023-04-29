#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
class Mouse : public GameEngineActor
{

public:

	Mouse();
	~Mouse();

	Mouse(const Mouse& _Other) = delete;
	Mouse(Mouse&& _Other) noexcept = delete;
	Mouse& operator=(const Mouse& _Other) = delete;
	Mouse& operator=(Mouse&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> ToLogin;
};

