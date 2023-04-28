#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
class TitleObjects : public GameEngineActor
{

public:

	TitleObjects();
	~TitleObjects();

	TitleObjects(const TitleObjects& _Other) = delete;
	TitleObjects(TitleObjects&& _Other) noexcept = delete;
	TitleObjects& operator=(const TitleObjects& _Other) = delete;
	TitleObjects& operator=(TitleObjects&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:

	void CreateLoginBox();
	void CreateChannelButton();

	std::shared_ptr<GameEngineSpriteRenderer> Frame;
	std::shared_ptr<GameEngineSpriteRenderer> BackGround;
	std::shared_ptr<GameEngineSpriteRenderer> Logo;

	std::shared_ptr<GameEngineSpriteRenderer> WorldSelectLope;
	std::shared_ptr<GameEngineSpriteRenderer> WorldSelectFixture;

	std::shared_ptr<GameEngineSpriteRenderer> ChScroll;

	//로그인창
	std::shared_ptr<GameEngineSpriteRenderer> LoginBoard;
	std::shared_ptr<GameEngineSpriteRenderer> SignUp;
	std::shared_ptr<GameEngineSpriteRenderer> Login;
	std::shared_ptr<GameEngineSpriteRenderer> HomePage;
	std::shared_ptr<GameEngineSpriteRenderer> Exit;
	std::shared_ptr<GameEngineSpriteRenderer> SaveEmail;
	std::shared_ptr<GameEngineSpriteRenderer> FindEmail;
	std::shared_ptr<GameEngineSpriteRenderer> FindPass;
	std::shared_ptr<GameEngineSpriteRenderer> Check;

	//std::shared_ptr<GameEngineSpriteRenderer> LoginBoard;
	//std::shared_ptr<GameEngineSpriteRenderer> LoginBoard;

	//채널
	std::shared_ptr<GameEngineSpriteRenderer> Demetos;
	std::shared_ptr<GameEngineSpriteRenderer> Bellokan;
	std::shared_ptr<GameEngineSpriteRenderer> Bera;
	std::shared_ptr<GameEngineSpriteRenderer> Broa;
	std::shared_ptr<GameEngineSpriteRenderer> Mardia;
	std::shared_ptr<GameEngineSpriteRenderer> Skania;
	std::shared_ptr<GameEngineSpriteRenderer> Stierce;
	std::shared_ptr<GameEngineSpriteRenderer> Akenia;
	std::shared_ptr<GameEngineSpriteRenderer> Zenis;
	std::shared_ptr<GameEngineSpriteRenderer> Kastia;
	std::shared_ptr<GameEngineSpriteRenderer> Kiny;
	std::shared_ptr<GameEngineSpriteRenderer> Croa;
	std::shared_ptr<GameEngineSpriteRenderer> Yellond;
	std::shared_ptr<GameEngineSpriteRenderer> Plana;
	
	int ScrollIndex = 0;
};

