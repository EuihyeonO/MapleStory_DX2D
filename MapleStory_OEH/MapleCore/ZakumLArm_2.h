#pragma once
#include "BasicFunction.h"

class ZakumLArm_2 : public BasicFunction
{

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

	std::shared_ptr<class GameEngineSpriteRenderer> ArmRender = nullptr;
};

