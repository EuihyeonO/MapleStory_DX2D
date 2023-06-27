#pragma once
#include "MonsterBasicFunction.h"

class BlueSnail : public MonsterBasicFunction
{

public:

	BlueSnail();
	~BlueSnail();

	BlueSnail(const BlueSnail& _Other) = delete;
	BlueSnail(BlueSnail&& _Other) noexcept = delete;
	BlueSnail& operator=(const BlueSnail& _Other) = delete;
	BlueSnail& operator=(BlueSnail&& _Other) noexcept = delete;

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

