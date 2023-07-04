#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
class RingPortal : public GameEngineActor
{

public:

	RingPortal();
	~RingPortal();

	RingPortal(const RingPortal& _Other) = delete;
	RingPortal(RingPortal&& _Other) noexcept = delete;
	RingPortal& operator=(const RingPortal& _Other) = delete;
	RingPortal& operator=(RingPortal&& _Other) noexcept = delete;
	
	void SetPortalPos(float4 _Pos)
	{
		GetTransform()->SetLocalPosition(_Pos);
	}

	void SetLinkedPos(float4 _Pos)
	{
		LinkedPos = _Pos;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	static bool isUsed;

	void CollisionCheck();
	bool isColToPlayer = false;

	void AlphaUpdate(float _DeltaTime);

	void SetPlayerPosToLinkedPos();

	std::shared_ptr<GameEngineSpriteRenderer> PortalRender = nullptr;
	std::shared_ptr<class GameEngineCollision> PortalCollision = nullptr;

	float4 LinkedPos = { 0, 0 };
};

