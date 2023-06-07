#pragma once
#include "BasicFunction.h"

class ZakumRArm_3 : public BasicFunction
{

public:

	ZakumRArm_3();
	~ZakumRArm_3();

	ZakumRArm_3(const ZakumRArm_3& _Other) = delete;
	ZakumRArm_3(ZakumRArm_3&& _Other) noexcept = delete;
	ZakumRArm_3& operator=(const ZakumRArm_3& _Other) = delete;
	ZakumRArm_3& operator=(ZakumRArm_3&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	std::shared_ptr<class GameEngineSpriteRenderer> ArmRender = nullptr;
};

