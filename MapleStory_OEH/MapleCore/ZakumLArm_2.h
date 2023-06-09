#pragma once
#include "ZakumBasicFunction.h"

class ZakumLArm_2 : public ZakumBasicFunction
{
	friend class Zakum;
	friend class ZakumBasicFunction;
public:

	ZakumLArm_2();
	~ZakumLArm_2();

	ZakumLArm_2(const ZakumLArm_2& _Other) = delete;
	ZakumLArm_2(ZakumLArm_2&& _Other) noexcept = delete;
	ZakumLArm_2& operator=(const ZakumLArm_2& _Other) = delete;
	ZakumLArm_2& operator=(ZakumLArm_2&& _Other) noexcept = delete;
	
protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

};

