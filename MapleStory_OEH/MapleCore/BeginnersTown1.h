#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
class BeginnersTown1 : public GameEngineActor
{
	friend class MiniMap;
	friend class Level_BeginnersTown1;
public:
	const std::string_view GetColMapName()
	{
		return ColMapName;
	}

	BeginnersTown1();
	~BeginnersTown1();

	BeginnersTown1(const BeginnersTown1& _Other) = delete;
	BeginnersTown1(BeginnersTown1&& _Other) noexcept = delete;
	BeginnersTown1& operator=(const BeginnersTown1& _Other) = delete;
	BeginnersTown1& operator=(BeginnersTown1&& _Other) noexcept = delete;

	

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	void ActorDeath();
	void BackGroundMove(float _DeltaTime);

	std::string ColMapName = "ColBeginnersTown1.png";
	std::string MapName = "BeginnersTown1.png";

	float XMoveConstant = 0.0f;

	std::shared_ptr<class MiniMap> MyMiniMap = nullptr;

	std::shared_ptr<GameEngineSpriteRenderer> BackGround = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Rope = nullptr;
	std::shared_ptr<class GameEngineCollision> RopeCol = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> BackGroundLayer = nullptr;

	std::shared_ptr<GameEngineSpriteRenderer> LandScape0 = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> LandScape2 = nullptr;

	std::shared_ptr<class Portal> MyPortal = nullptr;
	std::shared_ptr<class ContentRenderer> Cloud = nullptr;

	void FadeIn(float _DeltaTime);
	std::function<void(BeginnersTown1&, float)> FadeInUpdate;
	std::shared_ptr<class GameEngineUIRenderer> Black = nullptr;
};

