#pragma once
#include <GameEngineCore/GameEngineActor.h>

class SouthFerry : public GameEngineActor
{

public:

	SouthFerry();
	~SouthFerry();

	SouthFerry(const SouthFerry& _Other) = delete;
	SouthFerry(SouthFerry&& _Other) noexcept = delete;
	SouthFerry& operator=(const SouthFerry& _Other) = delete;
	SouthFerry& operator=(SouthFerry&& _Other) noexcept = delete;

	const std::string_view GetColMapName()
	{
		return ColMapName;
	}

	void ActorDeath();

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	void BackGroundUpdate(float _DeltaTime);

	std::string ColMapName = "ColSouthFerry.png";
	std::string MapName = "SouthFerry.png";

	std::shared_ptr<class GameEngineSpriteRenderer> Map = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BackGround = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BackColor = nullptr;

	std::vector<std::pair<std::shared_ptr<class GameEngineSpriteRenderer>, float>> CloudList;

	std::shared_ptr<class Portal> Portal1 = nullptr;
	std::shared_ptr<class Shanks> MyShanks = nullptr;

};

