#pragma once
#include "ZakumBasicFunction.h"

class ZakumRArm_0 : public ZakumBasicFunction
{
	friend class Zakum;
public:

	ZakumRArm_0();
	~ZakumRArm_0();

	ZakumRArm_0(const ZakumRArm_0& _Other) = delete;
	ZakumRArm_0(ZakumRArm_0&& _Other) noexcept = delete;
	ZakumRArm_0& operator=(const ZakumRArm_0& _Other) = delete;
	ZakumRArm_0& operator=(ZakumRArm_0&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	void SetAnimation();
};

