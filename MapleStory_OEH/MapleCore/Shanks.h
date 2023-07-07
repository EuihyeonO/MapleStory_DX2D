#pragma once
#include "BasicFunction.h"

class Shanks : public BasicFunction
{

public:

	Shanks();
	~Shanks();

	Shanks(const Shanks& _Other) = delete;
	Shanks(Shanks&& _Other) noexcept = delete;
	Shanks& operator=(const Shanks& _Other) = delete;
	Shanks& operator=(Shanks&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	void OpenWindow();
	void ChangeLevel(const std::string_view& _LevelName);

	std::shared_ptr<class GameEngineSpriteRenderer> ShanksRender = nullptr;
	std::shared_ptr<class GameEngineCollision> ShanksCollision = nullptr;

	std::shared_ptr<class NPCWindow> MyWindow = nullptr;
	std::function<void(float)> UpdateFunc = nullptr;
};

