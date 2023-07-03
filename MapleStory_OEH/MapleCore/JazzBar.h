#pragma once
#include <GameEngineCore/GameEngineActor.h>

class JazzBar : public GameEngineActor
{

public:
	const std::string_view GetColMapName()
	{
		return ColMapName;
	}

	JazzBar();
	~JazzBar();

	JazzBar(const JazzBar& _Other) = delete;
	JazzBar(JazzBar&& _Other) noexcept = delete;
	JazzBar& operator=(const JazzBar& _Other) = delete;
	JazzBar& operator=(JazzBar&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	std::string ColMapName = "ColJazzBar.png";
	std::string MapName = "JazzBar.png";

	std::shared_ptr<class GameEngineSpriteRenderer> Map = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> Layer = nullptr;

};

