#pragma once
#include <GameEngineCore/GameEngineActor.h>

class ZakumRoad1 : public GameEngineActor
{

public:

	const std::string_view GetColMapName()
	{
		return ColMapName;
	}

	ZakumRoad1();
	~ZakumRoad1();

	ZakumRoad1(const ZakumRoad1& _Other) = delete;
	ZakumRoad1(ZakumRoad1&& _Other) noexcept = delete;
	ZakumRoad1& operator=(const ZakumRoad1& _Other) = delete;
	ZakumRoad1& operator=(ZakumRoad1&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	std::string ColMapName = "ColZakumRoad1.png";
	std::string MapName = "ZakumRoad1.png";

	void LandScapeMove(float _DeltaTime);

	std::shared_ptr<class GameEngineSpriteRenderer> Tile = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BackGround = nullptr;

	std::shared_ptr<class MiniMap> MyMiniMap = nullptr;

};

