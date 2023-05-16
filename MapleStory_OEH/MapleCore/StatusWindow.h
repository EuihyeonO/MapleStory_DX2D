#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <list>

class GameEngineSpriteRenderer;
class StatusWindow : public GameEngineActor
{

public:

	StatusWindow();
	~StatusWindow();

	StatusWindow(const StatusWindow& _Other) = delete;
	StatusWindow(StatusWindow&& _Other) noexcept = delete;
	StatusWindow& operator=(const StatusWindow& _Other) = delete;
	StatusWindow& operator=(StatusWindow&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	void CreateInputKey();
	void GetKetInput();

	void AllWindowUpdate();

	bool WindowOnOff();
	void WindowOn();
	void WindowOff();
	
	bool PosUpdate();

	std::shared_ptr<GameEngineSpriteRenderer> MainWindow;
	std::shared_ptr<class GameEngineCollision> MainWindowClickBar;
	std::shared_ptr<GameEngineSpriteRenderer> SubWindow;

	std::list<std::function<bool(StatusWindow&)>> UpdateFunction;
};

