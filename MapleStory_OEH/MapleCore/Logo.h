#pragma once
#include "BasicFunction.h"

class GameEngineSpriteRenderer;
class Logo : public BasicFunction
{

public:

	Logo();
	~Logo();

	Logo(const Logo& _Other) = delete;
	Logo(Logo&& _Other) noexcept = delete;
	Logo& operator=(const Logo& _Other) = delete;
	Logo& operator=(Logo&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	void NexonAnimation();
	void WizetAnimation();

	float NexonCount = 0.0f;
	int NexonIndex = 0;

	float WizetWaitingCount = 0.0f;
	float WizetCount = 0.0f;
	int WizetIndex = 0;

	float DeathWaitingCount = 0.0f;

	bool isWizetSet = false;
	bool isNexonEnd = false;
	bool isWizetEnd = false;
	bool isCreateObject = false;

	std::shared_ptr<GameEngineSpriteRenderer> Nexon;
	std::shared_ptr<GameEngineSpriteRenderer> Wizet;
};

