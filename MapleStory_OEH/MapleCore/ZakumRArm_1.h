#pragma once
#include "ZakumBasicFunction.h"

class ZakumRArm_1 : public ZakumBasicFunction
{
	friend class Zakum;
public:

	ZakumRArm_1();
	~ZakumRArm_1();

	ZakumRArm_1(const ZakumRArm_1& _Other) = delete;
	ZakumRArm_1(ZakumRArm_1&& _Other) noexcept = delete;
	ZakumRArm_1& operator=(const ZakumRArm_1& _Other) = delete;
	ZakumRArm_1& operator=(ZakumRArm_1&& _Other) noexcept = delete;
	
protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	void SetAnimation();
	void Attack() override;
};

