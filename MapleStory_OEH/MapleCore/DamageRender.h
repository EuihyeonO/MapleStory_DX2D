#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <list>

class GameEngineSpriteRenderer;
class DamageRender : public GameEngineActor
{

public:

	DamageRender();
	~DamageRender();

	DamageRender(const DamageRender& _Other) = delete;
	DamageRender(DamageRender&& _Other) noexcept = delete;
	DamageRender& operator=(const DamageRender& _Other) = delete;
	DamageRender& operator=(DamageRender&& _Other) noexcept = delete;

	void PushDamageToQueue(int _Damage);
	void DeleteDamage();

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	void RenderUpdate(float _DeltaTime);

	std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*> DamageRenderList;
};

