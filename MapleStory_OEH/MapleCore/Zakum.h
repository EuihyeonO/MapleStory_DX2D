#pragma once
#include "BasicFunction.h"
#include <GameEngineCore/GameEngineActor.h>

class Zakum : public BasicFunction
{

public:

	Zakum();
	~Zakum();

	Zakum(const Zakum& _Other) = delete;
	Zakum(Zakum&& _Other) noexcept = delete;
	Zakum& operator=(const Zakum& _Other) = delete;
	Zakum& operator=(Zakum&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	std::shared_ptr<class GameEngineSpriteRenderer> BodyRender = nullptr;
	std::string AnimationName = "";
	
	std::shared_ptr<class ZakumRArm_0> RArm_0 = nullptr;
	std::shared_ptr<class ZakumRArm_1> RArm_1 = nullptr;
	std::shared_ptr<class ZakumRArm_2> RArm_2 = nullptr;
	std::shared_ptr<class ZakumRArm_3> RArm_3 = nullptr;

	std::shared_ptr<class ZakumLArm_0> LArm_0 = nullptr;
	std::shared_ptr<class ZakumLArm_1> LArm_1 = nullptr;
	std::shared_ptr<class ZakumLArm_2> LArm_2 = nullptr;
	std::shared_ptr<class ZakumLArm_3> LArm_3 = nullptr;

	int AniIndex = 0;
	float AniCount = 0;
};

