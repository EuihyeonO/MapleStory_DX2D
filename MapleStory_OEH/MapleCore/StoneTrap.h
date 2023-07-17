#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <functional>

class StoneTrap : public GameEngineActor
{

public:

	StoneTrap();
	~StoneTrap();

	StoneTrap(const StoneTrap& _Other) = delete;
	StoneTrap(StoneTrap&& _Other) noexcept = delete;
	StoneTrap& operator=(const StoneTrap& _Other) = delete;
	StoneTrap& operator=(StoneTrap&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	std::shared_ptr<class GameEngineSpriteRenderer> TrapRender;
	std::shared_ptr<class GameEngineCollision> TrapCol;
};

