#pragma once
#include "MonsterBasicFunction.h"

class Spore : public MonsterBasicFunction
{

public:

	Spore();
	~Spore();

	Spore(const Spore& _Other) = delete;
	Spore(Spore&& _Other) noexcept = delete;
	Spore& operator=(const Spore& _Other) = delete;
	Spore& operator=(Spore&& _Other) noexcept = delete;

	void Hit(int _Damage, bool _isRealAttack) override;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

	void Spawn(float _DeltaTime) override;
	void MonsterDeath(float _DeltaTime) override;
private:

	void SetAnimation();
	void SetDropItemList();

	float RenderAlpha = 0.0f;

	int Hp = 50;

	std::map<std::string, std::vector<float>> FrameList;
	std::vector<std::pair<std::string, /*0이상 100이하의 정수*/int>> DropItemList;

};

