#pragma once
#include "MonsterBasicFunction.h"

class GameEngineSpriteRenderer;
class GreenSnail : public MonsterBasicFunction
{

public:

	GreenSnail();
	~GreenSnail();

	GreenSnail(const GreenSnail& _Other) = delete;
	GreenSnail(GreenSnail&& _Other) noexcept = delete;
	GreenSnail& operator=(const GreenSnail& _Other) = delete;
	GreenSnail& operator=(GreenSnail&& _Other) noexcept = delete;


protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

	void Spawn(float _DeltaTime) override;
	void Hit() override;
	void Death(){}
private:

	void TextureUpdate();
	void SetAnimationList();
	

	float RenderAlpha = 0.0f;

	bool isSpawnAnimationEnd = false;

	std::map<std::string, std::vector<float>> FrameList;

	std::shared_ptr<class GameEngineSpriteRenderer> BasicRender;
	std::shared_ptr<class GameEngineCollision> BasicCollision;
};

