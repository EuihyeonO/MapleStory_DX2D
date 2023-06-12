#pragma once
#include "ZakumBasicFunction.h"

class ZakumLArm_0 : public ZakumBasicFunction
{
	friend class Zakum;
public:

	ZakumLArm_0();
	~ZakumLArm_0();

	ZakumLArm_0(const ZakumLArm_0& _Other) = delete;
	ZakumLArm_0(ZakumLArm_0&& _Other) noexcept = delete;
	ZakumLArm_0& operator=(const ZakumLArm_0& _Other) = delete;
	ZakumLArm_0& operator=(ZakumLArm_0&& _Other) noexcept = delete;
	
protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	void SetAnimation();
	void Attack() override;
};

