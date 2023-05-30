#pragma once
#include "Player.h"
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

class QuickSlot : public GameEngineActor
{

public:

	std::function<void(std::shared_ptr<class Player>, std::function<void(std::shared_ptr<class Player>)>)> GetSlotFunc(std::shared_ptr<class GameEngineCollision> _Col)
	{
		return ColSlotSkill[_Col].first;
	}

	void SetColSlotTexture(std::shared_ptr<class GameEngineCollision> _Col, const std::string_view& _TextureName)
	{
		ColSlotSkill[_Col].second->SetScaleToTexture(_TextureName);
		ColSlotSkill[_Col].second->On();
	}

	QuickSlot();
	~QuickSlot();

	QuickSlot(const QuickSlot& _Other) = delete;
	QuickSlot(QuickSlot&& _Other) noexcept = delete;
	QuickSlot& operator=(const QuickSlot& _Other) = delete;
	QuickSlot& operator=(QuickSlot&& _Other) noexcept = delete;


protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	std::shared_ptr<GameEngineUIRenderer> QuickSlotRender = nullptr;
	std::shared_ptr<GameEngineUIRenderer> QuickSlotLayer = nullptr;

	
	std::map<std::shared_ptr<class GameEngineCollision>, std::pair<std::function<void(std::shared_ptr<class Player>, std::function<void(std::shared_ptr<class Player>)>)>, std::shared_ptr<GameEngineUIRenderer>>> ColSlotSkill;

	std::shared_ptr<class GameEngineCollision> ShiftSlot;
	std::shared_ptr<class GameEngineCollision> InsSlot;
	std::shared_ptr<class GameEngineCollision> HomeSlot;
	std::shared_ptr<class GameEngineCollision> PgUpSlot;
	std::shared_ptr<class GameEngineCollision> CtrlSlot;
	std::shared_ptr<class GameEngineCollision> DelSlot;
	std::shared_ptr<class GameEngineCollision> EndSlot;
	std::shared_ptr<class GameEngineCollision> PgDnSlot;

	std::shared_ptr<GameEngineUIRenderer> ShiftSkill;
	std::shared_ptr<GameEngineUIRenderer> InsSkill;
	std::shared_ptr<GameEngineUIRenderer> HomeSkill;
	std::shared_ptr<GameEngineUIRenderer> PgUpSkill;
	std::shared_ptr<GameEngineUIRenderer> CtrlSkill;
	std::shared_ptr<GameEngineUIRenderer> DelSkill;
	std::shared_ptr<GameEngineUIRenderer> EndSkill;
	std::shared_ptr<GameEngineUIRenderer> PgDnSkill;
};

