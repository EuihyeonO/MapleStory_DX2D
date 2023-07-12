#pragma once
#include <GameEngineCore/GameEngineActor.h>

class ZakumRoad2 : public GameEngineActor
{

public:

	const std::string_view GetColMapName()
	{
		return ColMapName;
	}

	ZakumRoad2();
	~ZakumRoad2();

	ZakumRoad2(const ZakumRoad2& _Other) = delete;
	ZakumRoad2(ZakumRoad2&& _Other) noexcept = delete;
	ZakumRoad2& operator=(const ZakumRoad2& _Other) = delete;
	ZakumRoad2& operator=(ZakumRoad2&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	std::string ColMapName = "ColZakumRoad2.png";
	std::string MapName = "ZakumRoad2.png";
	
	float XUVCount = 0.0f;

	std::shared_ptr<class GameEngineSpriteRenderer> Tile = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> Layer = nullptr;
	std::shared_ptr<class ContentRenderer> BackGround = nullptr;
	std::shared_ptr<class ContentRenderer> Magma = nullptr;
};

