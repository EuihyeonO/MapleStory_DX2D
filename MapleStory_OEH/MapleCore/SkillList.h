#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <stack>

class GameEngineSpriteRenderer;
class SkillList : public GameEngineActor
{
	friend class SkillWindow;
private:

	class SkillIcon : public GameEngineActor
	{		
		friend SkillList;

	private:
		std::shared_ptr<class GameEngineUIRenderer> SkillBackGround;

		std::shared_ptr<class GameEngineUIRenderer> IconRender;
		std::shared_ptr<class GameEngineCollision> IconCollision;
		//std::shared_ptr<GameEngineSpriteRenderer> SkillInfo;

		std::shared_ptr<class GameEngineUIRenderer> SkillLevelUpRender;
		std::shared_ptr<class GameEngineCollision> SkillLevelUpButton;

		std::string SkillName = "";
	};

public:

	void ClearList()
	{
		std::map<int, std::vector<std::shared_ptr<SkillIcon>>>::iterator Start = SkillVector.begin();
		std::map<int, std::vector<std::shared_ptr<SkillIcon>>>::iterator End = SkillVector.end();

		for (; Start != End; Start++)
		{
			for (int i = 0; i < Start->second.size(); i++)
			{
				Start->second[i]->Death();
				Start->second[i] = nullptr;
			}
		}
	}

	SkillList();
	~SkillList();

	SkillList(const SkillList& _Other) = delete;
	SkillList(SkillList&& _Other) noexcept = delete;
	SkillList& operator=(const SkillList& _Other) = delete;
	SkillList& operator=(SkillList&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	void InsertSkillToList(int _Index, const std::string_view& _SkillName);
	void IndexSkillOn(int _Index);
	void IndexSkillOff(int _Index);

	std::map<int, std::vector<std::shared_ptr<SkillIcon>>> SkillVector;
};

