#pragma once
#include "BasicFunction.h"

class ZakumLArm_3 : public BasicFunction
{

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

	std::shared_ptr<class GameEngineSpriteRenderer> ArmRender = nullptr;
};

