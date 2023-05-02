#pragma once

#include <GameEngineBase/GameEngineTimeEvent.h>
#include <GameEngineCore\GameEngineLevel.h>

// Ό³Έν :
class Level_BeginnersTown : public GameEngineLevel
{

public:

	Level_BeginnersTown();
	~Level_BeginnersTown();

	Level_BeginnersTown(const Level_BeginnersTown& _Other) = delete;
	Level_BeginnersTown(Level_BeginnersTown&& _Other) noexcept = delete;
	Level_BeginnersTown& operator=(const Level_BeginnersTown& _Other) = delete;
	Level_BeginnersTown& operator=(Level_BeginnersTown&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:

};

