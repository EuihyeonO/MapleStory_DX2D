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

	static Mouse* GetMouse()
	{
		return CurMouse;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	static Mouse* CurMouse;

	void PosUpdate();

	std::shared_ptr<GameEngineSpriteRenderer> Cursor;
	std::shared_ptr<class GameEngineCollision> CursorCollision;
};

