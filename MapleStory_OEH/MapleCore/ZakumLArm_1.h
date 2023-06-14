#pragma once
#include "ZakumBasicFunction.h"

class ZakumLArm_1 : public ZakumBasicFunction
{
	friend class Zakum;
public:

	ZakumLArm_1();
	~ZakumLArm_1();

	ZakumLArm_1(const ZakumLArm_1& _Other) = delete;
	ZakumLArm_1(ZakumLArm_1&& _Other) noexcept = delete;
	ZakumLArm_1& operator=(const ZakumLArm_1& _Other) = delete;
	ZakumLArm_1& operator=(ZakumLArm_1&& _Other) noexcept = delete;
	
protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	void SetAnimation();
	void Attack() override;
	
	void FireRain();
	void PosionSmog();
	
	
	std::function<void()> UpdateFunc;

	std::vector<std::pair<std::shared_ptr<GameEngineSpriteRenderer>, std::shared_ptr<class GameEngineCollision>>> SmogVec;
	std::vector<bool> isSmogAlphaUp;
	bool isSmogOn = false;
};

