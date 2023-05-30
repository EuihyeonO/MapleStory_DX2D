#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
class Mouse : public GameEngineActor
{

public:

	Mouse();
	~Mouse();

	Mouse(const Mouse& _Other) = delete;
	Mouse(Mouse&& _Other) noexcept = delete;
	Mouse& operator=(const Mouse& _Other) = delete;
	Mouse& operator=(Mouse&& _Other) noexcept = delete;

	static std::shared_ptr<Mouse> GetMouse()
	{
		return CurMouse;
	}

	std::shared_ptr<class GameEngineCollision> GetMouseCollision()
	{
		return CursorCollision;
	}

	void SetCurMouse(std::shared_ptr<Mouse> _Mouse)
	{
		CurMouse = _Mouse;
	}


protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	static std::shared_ptr<Mouse> CurMouse;

	void PosUpdate();

	std::shared_ptr<class GameEngineUIRenderer> Cursor;
	std::shared_ptr<class GameEngineCollision> CursorCollision;

	std::shared_ptr<class GameEngineUIRenderer> Test;
};

