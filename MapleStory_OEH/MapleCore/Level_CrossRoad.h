#pragma once

#include <GameEngineBase/GameEngineTimeEvent.h>
#include <GameEngineCore\GameEngineLevel.h>

class Level_CrossRoad : public GameEngineLevel
{

public:

	Level_CrossRoad();
	~Level_CrossRoad();

	Level_CrossRoad(const Level_CrossRoad& _Other) = delete;
	Level_CrossRoad(Level_CrossRoad&& _Other) noexcept = delete;
	Level_CrossRoad& operator=(const Level_CrossRoad& _Other) = delete;
	Level_CrossRoad& operator=(Level_CrossRoad&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStart() override;
	void LevelChangeEnd() override;
private:
	std::shared_ptr<class Player> MyPlayer = nullptr;
	std::shared_ptr<class CrossRoad> Map = nullptr;
	std::shared_ptr<class Mouse> MyMouse = nullptr;
	std::shared_ptr<class UIWindowManager> MyUIWindowManager = nullptr;
};

