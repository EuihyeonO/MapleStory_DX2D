#pragma once
#include "MonsterBasicFunction.h"

class GreenSnail : public MonsterBasicFunction
{

public:

	GreenSnail();
	~GreenSnail();

	GreenSnail(const GreenSnail& _Other) = delete;
	GreenSnail(GreenSnail&& _Other) noexcept = delete;
	GreenSnail& operator=(const GreenSnail& _Other) = delete;
	GreenSnail& operator=(GreenSnail&& _Other) noexcept = delete;

	void Hit() override;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

	void Spawn(float _DeltaTime) override;
	void MonsterDeath() override {}
private:

	void TextureUpdate();
	void SetAnimationList();	
	void SetDropItemList();

	float RenderAlpha = 0.0f;

	bool isSpawnAnimationEnd = false;

	std::map<std::string, std::vector<float>> FrameList;
	std::vector<std::pair<std::string, /*0이상 100이하의 정수*/int>> DropItemList;

	std::shared_ptr<class ContentRenderer> BasicRender;
	std::shared_ptr<class GameEngineCollision> BasicCollision;
};

