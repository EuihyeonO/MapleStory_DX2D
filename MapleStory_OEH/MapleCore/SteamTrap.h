#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <functional>

class SteamTrap : public GameEngineActor
{

public:

	SteamTrap();
	~SteamTrap();

	SteamTrap(const SteamTrap& _Other) = delete;
	SteamTrap(SteamTrap&& _Other) noexcept = delete;
	SteamTrap& operator=(const SteamTrap& _Other) = delete;
	SteamTrap& operator=(SteamTrap&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	std::shared_ptr<class GameEngineSpriteRenderer> Trap;

	std::shared_ptr<class GameEngineSpriteRenderer> TrapRender;
	std::shared_ptr<class GameEngineCollision> TrapCol;
};

