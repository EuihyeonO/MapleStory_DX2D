#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <functional>

class DarkLord : public GameEngineActor
{

public:

	DarkLord();
	~DarkLord();

	DarkLord(const DarkLord& _Other) = delete;
	DarkLord(DarkLord&& _Other) noexcept = delete;
	DarkLord& operator=(const DarkLord& _Other) = delete;
	DarkLord& operator=(DarkLord&& _Other) noexcept = delete;
	
	void ActorDeath();

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	void OpenWindow();
	void ChangeLevel(const std::string_view& _LevelName);

	std::function<void(float)> UpdateFunc = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> DarkLordRender;
	std::shared_ptr<class GameEngineCollision> DarkLordCollision;
	
	std::shared_ptr<class NPCWindow> MyWindow;
};

