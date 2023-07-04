#pragma once
#include "BasicFunction.h"

class BigBox : public BasicFunction
{

public:

	BigBox();
	~BigBox();

	BigBox(const BigBox& _Other) = delete;
	BigBox(BigBox&& _Other) noexcept = delete;
	BigBox& operator=(const BigBox& _Other) = delete;
	BigBox& operator=(BigBox&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	bool GravityUpdate(float _DeltaTime);
	bool CollisionCheck(float _Deltatime);

	bool isGround = false;
	bool isCreateItem = false;
	float ColCount = 0.0f;

	std::function<bool(BigBox&, float)> UpdateFunc = nullptr;

	std::shared_ptr<class GameEngineTexture> ColMap = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> BoxRender = nullptr;
	std::shared_ptr<class GameEngineCollision> BoxCollision = nullptr;
};

