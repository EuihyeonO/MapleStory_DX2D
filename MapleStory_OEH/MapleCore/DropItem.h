#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
class GameEngineCollision;

class DropItem : public GameEngineActor
{
public:

	DropItem();
	~DropItem();

	DropItem(const DropItem& _Other) = delete;
	DropItem(DropItem&& _Other) noexcept = delete;
	DropItem& operator=(const DropItem& _Other) = delete;
	DropItem& operator=(DropItem&& _Other) noexcept = delete;

	void MoveDropItem(float _DeltaTime);

	void SetQuadraticFunction(float _XDistance, float4 _StartPos)
	{
		XDistance = _XDistance;
		Xintercept = XDistance + _StartPos.x;
		MaxY += StartPos.y;
		StartPos = _StartPos;

		if (Xintercept == 0.0f)
		{
			Xintercept = 1.0f;
		}

		float Num = (StartPos.x * Xintercept) - (((StartPos.x + Xintercept) / 2.0f) * ((StartPos.x + Xintercept) / 2.0f));
		Coefficient = MaxY / Num;

		GetTransform()->SetLocalPosition(_StartPos);

		isFuncSet = true;
	}

	void SetDropItemInfo(const std::string_view& _ItemName);

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> DropItemRender;
	std::shared_ptr<GameEngineCollision> DropItemCollision;

	std::shared_ptr<GameEngineTexture> ColMap;

	float4 StartPos = { 0, 0 };

	bool isFuncSet = false;
	bool isInfoSet = false;

	std::string ItemName = "";

	float MaxY = 60.0f;

	float Xintercept = 0.0f;
	float XDistance = 0.0f;
	float Coefficient = 0.0f;

	float Dir = 0.0f;
};

