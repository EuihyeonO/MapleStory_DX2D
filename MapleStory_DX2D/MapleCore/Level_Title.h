#pragma once

#include <GameEngineBase/GameEngineTimeEvent.h>
#include <GameEngineCore\GameEngineLevel.h>

// Ό³Έν :
class Level_Title : public GameEngineLevel
{

public:

	Level_Title();
	~Level_Title();

	Level_Title(const Level_Title& _Other) = delete;
	Level_Title(Level_Title&& _Other) noexcept = delete;
	Level_Title& operator=(const Level_Title& _Other) = delete;
	Level_Title& operator=(Level_Title&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool isCamUp = false;
	bool isCamSet = false;
	bool isCam2Up = false;
	bool isCam2Set = false;
};

