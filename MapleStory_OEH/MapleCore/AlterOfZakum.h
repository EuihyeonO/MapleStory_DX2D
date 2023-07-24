#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
class AlterOfZakum : public GameEngineActor
{
	friend class MiniMap;

public:

	const std::string_view GetColMapName()
	{
		return ColMapName;
	}

	AlterOfZakum();
	~AlterOfZakum();

	AlterOfZakum(const AlterOfZakum& _Other) = delete;
	AlterOfZakum(AlterOfZakum&& _Other) noexcept = delete;
	AlterOfZakum& operator=(const AlterOfZakum& _Other) = delete;
	AlterOfZakum& operator=(AlterOfZakum&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	void SpawnZakum(float _DeltaTime);
	void LandScapeMove();

	void MagmaMove(float _DeltaTime);
	std::string ColMapName = "ColAlterOfZakum.png";
	std::string MapName = "AlterOfZakum.png";

	std::shared_ptr<class ContentRenderer> LandScape0 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> LandScape1 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> LandScape2 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> LandScape3 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> LandScape4 = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> Alter = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> AlterBack = nullptr;

	std::shared_ptr<class RingPortal> RingPortal1 = nullptr;
	std::shared_ptr<class RingPortal> RingPortal2 = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> BackGround = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> Layer = nullptr;

	std::function<void(float)> UpdateFunc = nullptr;
	std::shared_ptr<class GameEngineCollision> AlterCollision = nullptr;
	float ColCount = 0.0f;

	float Magma_UVXMove = 0.0f;

	std::shared_ptr<class ContentRenderer> Magma = nullptr;
};

