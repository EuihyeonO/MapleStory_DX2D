#pragma once
#include <GameEngineCore/GameEngineActor.h>


class GameEngineSpriteRenderer;
class BeginnersTown2 : public GameEngineActor
{
	friend class MiniMap;

public:

	const std::string_view GetColMapName()
	{
		return ColMapName;
	}

	BeginnersTown2();
	~BeginnersTown2();

	BeginnersTown2(const BeginnersTown2& _Other) = delete;
	BeginnersTown2(BeginnersTown2&& _Other) noexcept = delete;
	BeginnersTown2& operator=(const BeginnersTown2& _Other) = delete;
	BeginnersTown2& operator=(BeginnersTown2&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	void BackGroundMove(float _DeltaTime);

	float XMoveConstant = 0.0f;

	std::string ColMapName = "ColBeginnersTown2.png";
	std::string MapName = "BeginnersTown2.png";

	std::shared_ptr<class MiniMap> MyMiniMap = nullptr;

	std::shared_ptr<GameEngineSpriteRenderer> BackGround = nullptr;

	std::shared_ptr<GameEngineSpriteRenderer> LandScape0 = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> LandScape2 = nullptr;

	std::shared_ptr<class ContentRenderer> Cloud = nullptr;
};

