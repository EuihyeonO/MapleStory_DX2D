#pragma once
#include "BasicFunction.h"

class ZakumRArm_0 : public BasicFunction
{

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

	std::shared_ptr<class GameEngineSpriteRenderer> ArmRender = nullptr;
};

