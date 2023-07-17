#pragma once
#include "BasicFunction.h"

class GameEngineSpriteRenderer;
class Sera : public BasicFunction
{

public:

	Sera();
	~Sera();

	Sera(const Sera& _Other) = delete;
	Sera(Sera&& _Other) noexcept = delete;
	Sera& operator=(const Sera& _Other) = delete;
	Sera& operator=(Sera&& _Other) noexcept = delete;
	
	void ActorDeath();

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	void ChangeStatus();
	std::string Status = "";

	void MoveUpdate(float _DeltaTime);
	std::function<void(float)> UpdateFunc = nullptr;

	float MoveDistance = 0.0f;
	float4 Dir = { 1, 0 };
	
	void OpenWindow();

	std::shared_ptr<GameEngineSpriteRenderer> SeraRender = nullptr;
	std::shared_ptr<class GameEngineCollision> SeraCollision = nullptr;

	std::shared_ptr<class NPCWindow> MyWindow = nullptr;
};

