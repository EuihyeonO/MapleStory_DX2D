#pragma once
#include <vector>
#include <memory>
#include <string>
#include <string_view>

class UIController
{

public:

	UIController(const UIController& _Other) = delete;
	UIController(UIController&& _Other) noexcept = delete;
	UIController& operator=(const UIController& _Other) = delete;
	UIController& operator=(UIController&& _Other) noexcept = delete;

	static UIController* GetUIController()
	{
		return &Value;
	}

	void AddQuickSlotToList(std::shared_ptr<class QuickSlot> _QuickSlot)
	{
		QuickSlotList.push_back(_QuickSlot);
	}

	void SetShiftSkillName(const std::string_view& _SkillName)
	{
		ShiftSkillName = _SkillName.data();
	}
	void SetInsSkillName(const std::string_view& _SkillName)
	{
		InsSkillName = _SkillName.data();
	}
	void SetHomeSkillName(const std::string_view& _SkillName)
	{
		HomeSkillName = _SkillName.data();
	}
	void SetPgUpSkillName(const std::string_view& _SkillName)
	{
		PgUpSkillName = _SkillName.data();
	}
	void SetCtrlSkillName(const std::string_view& _SkillName)
	{
		CtrlSkillName = _SkillName.data();
	}
	void SetDelSkillName(const std::string_view& _SkillName)
	{
		DelSkillName = _SkillName.data();
	}
	void SetEndSkillName(const std::string_view& _SkillName)
	{
		EndSkillName = _SkillName.data();
	}
	void SetPgDNSkillName(const std::string_view& _SkillName)
	{
		PgDNSkillName = _SkillName.data();
	}

protected:

private:
	UIController();
	~UIController();

	static UIController Value;

	std::vector<std::shared_ptr<class QuickSlot>> QuickSlotList;

	//QuickSlot
	std::string ShiftSkillName = "";
	std::string InsSkillName = "";
	std::string HomeSkillName = "";
	std::string PgUpSkillName = "";
	std::string CtrlSkillName = "";
	std::string DelSkillName = "";
	std::string EndSkillName = "";
	std::string PgDNSkillName = "";
};

