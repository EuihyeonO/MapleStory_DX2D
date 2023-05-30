#pragma once
#include "Player.h"
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

class QuickSlot : public GameEngineActor
{

public:

	std::function<void(class UIController&, const std::string_view&, std::function<void(std::shared_ptr<Player>)>)> GetSlotFunc(std::shared_ptr<class GameEngineCollision> _Col)
	{
		return ColSlotSkill[_Col];
	}

	void SetShiftSlotTexture(const std::string_view& _TextureName)
	{
		ShiftSkill->SetScaleToTexture(_TextureName);
		ShiftSkill->On();
	}

	void SetInsSlotTexture(const std::string_view& _TextureName)
	{
		InsSkill->SetScaleToTexture(_TextureName);
		InsSkill->On();
	}

	void SetHomeSlotTexture(const std::string_view& _TextureName)
	{
		HomeSkill->SetScaleToTexture(_TextureName);
		HomeSkill->On();
	}

	void SetPgUpSlotTexture(const std::string_view& _TextureName)
	{
		PgUpSkill->SetScaleToTexture(_TextureName);
		PgUpSkill->On();
	}

	void SetCtrlSlotTexture(const std::string_view& _TextureName)
	{
		CtrlSkill->SetScaleToTexture(_TextureName);
		CtrlSkill->On();
	}

	void SetDelSlotTexture(const std::string_view& _TextureName)
	{
		DelSkill->SetScaleToTexture(_TextureName);
		DelSkill->On();
	}

	void SetEndSlotTexture(const std::string_view& _TextureName)
	{
		EndSkill->SetScaleToTexture(_TextureName);
		EndSkill->On();
	}

	void SetPgDnSlotTexture(const std::string_view& _TextureName)
	{
		PgDnSkill->SetScaleToTexture(_TextureName);
		PgDnSkill->On();
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

	
	std::map<std::shared_ptr<class GameEngineCollision>, std::function<void(UIController&, const std::string_view&, std::function<void(std::shared_ptr<Player>)>)>> ColSlotSkill;

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

