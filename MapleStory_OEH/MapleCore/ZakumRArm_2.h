#pragma once
#include "ZakumBasicFunction.h"

class ZakumRArm_2 : public ZakumBasicFunction
{
	friend class Zakum;
public:

	ZakumRArm_2();
	~ZakumRArm_2();

	ZakumRArm_2(const ZakumRArm_2& _Other) = delete;
	ZakumRArm_2(ZakumRArm_2&& _Other) noexcept = delete;
	ZakumRArm_2& operator=(const ZakumRArm_2& _Other) = delete;
	ZakumRArm_2& operator=(ZakumRArm_2&& _Other) noexcept = delete;
	
protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	void SetAnimation();
	void Attack() override;
};

