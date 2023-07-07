#pragma once
#include <GameEngineCore/GameEngineActor.h>


class GameEngineSpriteRenderer;
class CrossRoad : public GameEngineActor
{
	friend class MiniMap;

public:

	const std::string_view GetColMapName()
	{
		return ColMapName;
	}

	CrossRoad();
	~CrossRoad();

	CrossRoad(const CrossRoad& _Other) = delete;
	CrossRoad(CrossRoad&& _Other) noexcept = delete;
	CrossRoad& operator=(const CrossRoad& _Other) = delete;
	CrossRoad& operator=(CrossRoad&& _Other) noexcept = delete;
	
	void ActorDeath();

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	std::string ColMapName = "ColCrossRoad.png";
	std::string MapName = "CrossRoad.png";

	void LandScapeMove(float _DeltaTime);

	std::shared_ptr<GameEngineSpriteRenderer> BackGround = nullptr;

	std::shared_ptr<class Portal> Portal1 = nullptr;
	std::shared_ptr<class Portal> Portal2 = nullptr;
	std::shared_ptr<class MonsterSpawnZone> Zone1 = nullptr;
	std::shared_ptr<class MonsterSpawnZone> Zone2 = nullptr;

	std::shared_ptr<class MiniMap> MyMiniMap = nullptr;

	std::shared_ptr<class ContentRenderer> BasicBackGround = nullptr;

	std::shared_ptr<class ContentRenderer> LandScape0 = nullptr;
	std::shared_ptr<class ContentRenderer> LandScape1 = nullptr;
	std::shared_ptr<class ContentRenderer> LandScape2 = nullptr;
};

