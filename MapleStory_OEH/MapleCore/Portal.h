#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
class Portal : public GameEngineActor
{

public:

	Portal();
	~Portal();

	Portal(const Portal& _Other) = delete;
	Portal(Portal&& _Other) noexcept = delete;
	Portal& operator=(const Portal& _Other) = delete;
	Portal& operator=(Portal&& _Other) noexcept = delete;

	void SetLinkedMap(const std::string_view& _MapName)
	{
		LinkedMap = _MapName;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	std::string LinkedMap = "";

	std::shared_ptr<GameEngineSpriteRenderer> PortalRender = nullptr;
	std::shared_ptr<class GameEngineCollision> PortalCollision = nullptr;
};

