#pragma once

#include <GameEngineBase/GameEngineTimeEvent.h>
#include <GameEngineCore\GameEngineLevel.h>

class Level_BeginnersTown2 : public GameEngineLevel
{

public:

	Level_BeginnersTown2();
	~Level_BeginnersTown2();

	Level_BeginnersTown2(const Level_BeginnersTown2& _Other) = delete;
	Level_BeginnersTown2(Level_BeginnersTown2&& _Other) noexcept = delete;
	Level_BeginnersTown2& operator=(const Level_BeginnersTown2& _Other) = delete;
	Level_BeginnersTown2& operator=(Level_BeginnersTown2&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStart() override;
	void LevelChangeEnd() override;
private:
	std::shared_ptr<class Player> MyPlayer = nullptr;
	std::shared_ptr<class BeginnersTown2> Map = nullptr;
	std::shared_ptr<class Mouse> MyMouse = nullptr;
};

