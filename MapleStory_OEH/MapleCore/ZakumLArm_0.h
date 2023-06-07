#pragma once
#include "BasicFunction.h"

class ZakumLArm_0 : public BasicFunction
{

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

	std::shared_ptr<class GameEngineSpriteRenderer> ArmRender = nullptr;
};

