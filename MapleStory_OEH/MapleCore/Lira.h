#pragma once
#include "BasicFunction.h"
#include <functional>

class GameEngineSpriteRenderer;
class Lira : public BasicFunction
{

public:

	Lira();
	~Lira();

	Lira(const Lira& _Other) = delete;
	Lira(Lira&& _Other) noexcept = delete;
	Lira& operator=(const Lira& _Other) = delete;
	Lira& operator=(Lira&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	void ChangeLevel(const std::string_view& _LevelName);
	
	void OpenWindow();

	std::function<void(float)> UpdateFunc = nullptr;

	std::shared_ptr<GameEngineSpriteRenderer> LiraRender;
	std::shared_ptr<class GameEngineCollision> LiraCollision;
	std::shared_ptr<class NPCWindow> MyWindow;
};

