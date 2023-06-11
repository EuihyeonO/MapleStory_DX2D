#pragma once
#include "ZakumBasicFunction.h"

class ZakumLArm_3 : public ZakumBasicFunction
{
	friend class Zakum;
public:

	ZakumLArm_3();
	~ZakumLArm_3();

	ZakumLArm_3(const ZakumLArm_3& _Other) = delete;
	ZakumLArm_3(ZakumLArm_3&& _Other) noexcept = delete;
	ZakumLArm_3& operator=(const ZakumLArm_3& _Other) = delete;
	ZakumLArm_3& operator=(ZakumLArm_3&& _Other) noexcept = delete;
	
protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	void SetAnimation();

	float DeltaTime = 0.0f;
};

