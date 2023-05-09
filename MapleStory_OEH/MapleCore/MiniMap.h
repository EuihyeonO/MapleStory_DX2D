#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
class MiniMap : public GameEngineActor
{

public:

	void SetMap(const std::string_view& _MapName);

	MiniMap();
	~MiniMap();

	MiniMap(const MiniMap& _Other) = delete;
	MiniMap(MiniMap&& _Other) noexcept = delete;
	MiniMap& operator=(const MiniMap& _Other) = delete;
	MiniMap& operator=(MiniMap&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:


	std::shared_ptr<GameEngineSpriteRenderer> Map;
	std::shared_ptr<GameEngineSpriteRenderer> Filter;
	std::shared_ptr<GameEngineSpriteRenderer> MiniMapBox;
	std::shared_ptr<GameEngineSpriteRenderer> UserMark;

	float4 DownSizeRatio = {0,0};


};

