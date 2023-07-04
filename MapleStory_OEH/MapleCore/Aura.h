#pragma once
#include "BasicFunction.h"

class GameEngineSpriteRenderer;
class Aura : public BasicFunction
{

public:

	Aura();
	~Aura();

	Aura(const Aura& _Other) = delete;
	Aura(Aura&& _Other) noexcept = delete;
	Aura& operator=(const Aura& _Other) = delete;
	Aura& operator=(Aura&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	void OpenWindow();

	std::shared_ptr<GameEngineSpriteRenderer> AuraRender = nullptr;
	std::shared_ptr<class GameEngineCollision> AuraCollision = nullptr;

	void ChangeLevel(const std::string_view& _LevelName);

	std::function<void(float)> UpdateFunc = nullptr;
	std::shared_ptr<class NPCWindow> MyWindow = nullptr;
};

