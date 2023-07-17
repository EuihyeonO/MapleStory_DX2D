#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Adovis : public GameEngineActor
{

public:

	Adovis();
	~Adovis();

	Adovis(const Adovis& _Other) = delete;
	Adovis(Adovis&& _Other) noexcept = delete;
	Adovis& operator=(const Adovis& _Other) = delete;
	Adovis& operator=(Adovis&& _Other) noexcept = delete;

	void ActorDeath();

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	void ChangeLevel(const std::string_view& _Level);
	std::function<void(float)> UpdateFunc = nullptr;

	void OpenWindow();
	std::shared_ptr<class NPCWindow> MyWindow = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> AdovisRender = nullptr;
	std::shared_ptr<class GameEngineCollision> AdovisCollision = nullptr;
};

