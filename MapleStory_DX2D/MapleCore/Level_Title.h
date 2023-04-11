#pragma once

#include <GameEngineBase/GameEngineTimeEvent.h>
#include <GameEngineCore\GameEngineLevel.h>

// ���� :
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
private:

};

