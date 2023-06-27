#pragma once
#include "SkillList.h"
#include <GameEngineCore/GameEngineActor.h>
#include <stack>

class GameEngineSpriteRenderer;
class SkillWindow : public GameEngineActor
{
private:

	struct SkillWindowIndexButton
	{
		std::shared_ptr<class GameEngineCollision> ButtonCollision;
		int index; 

		SkillWindowIndexButton() : index(0), ButtonCollision(nullptr) {}
	};

public:
	void SkillListDeath()
	{
		MySkillList->ClearList();
		MySkillList->Death();
		MySkillList = nullptr;
	}

	SkillWindow();
	~SkillWindow();

	SkillWindow(const SkillWindow& _Other) = delete;
	SkillWindow(SkillWindow&& _Other) noexcept = delete;
	SkillWindow& operator=(const SkillWindow& _Other) = delete;
	SkillWindow& operator=(SkillWindow&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	void ChangeWindowIndex();
	void ColPosUpdate();

	int Index = 0;

	std::shared_ptr<class SkillList> MySkillList = nullptr;

	std::shared_ptr<class GameEngineUIRenderer> SkillWindowRender = nullptr;

	std::shared_ptr<class GameEngineCollision> Index0 = nullptr;
	std::shared_ptr<class GameEngineCollision> Index1 = nullptr;
	std::shared_ptr<class GameEngineCollision> Index2 = nullptr;
	std::shared_ptr<class GameEngineCollision> Index3 = nullptr;
	std::shared_ptr<class GameEngineCollision> Index4 = nullptr;
	//스킬 콜리전은 
};

