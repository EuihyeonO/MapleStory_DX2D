#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <functional>

class KeyBox : public GameEngineActor
{

public:

	KeyBox();
	~KeyBox();

	KeyBox(const KeyBox& _Other) = delete;
	KeyBox(KeyBox&& _Other) noexcept = delete;
	KeyBox& operator=(const KeyBox& _Other) = delete;
	KeyBox& operator=(KeyBox&& _Other) noexcept = delete;
	
	bool GetisSet();
	void SpawnStart(float4 _Pos);
	void Hit();

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	void GravityUpdate(float _DeltaTime);
	bool Spawn(float _DeltaTime);

	bool isSet = false;

	std::shared_ptr<class GameEngineTexture> ColMap = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> BoxRender = nullptr;
	std::shared_ptr<class GameEngineCollision> BoxCollision = nullptr;

	std::function<bool(KeyBox&, float)> UpdateFunc = nullptr;

	int count = 0;

	bool isHit = false;
	bool isGround = false;
};

