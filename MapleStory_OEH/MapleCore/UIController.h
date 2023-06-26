#pragma once
#include "QuickSlot.h"
#include "PlayerValue.h"
#include "ItemList.h"
#include "EquipItemList.h"

#include <vector>
#include <memory>
#include <string>
#include <string_view>
#include <functional>

struct ItemInfo {
	int Num = 0;
	int Level = 0;
	int EquipType = 0;

	float4 Stat = { 0, 0, 0, 0 };
	std::string ItemName = "";
};

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

	std::map<int, std::vector<std::shared_ptr<ItemInfo>>>& GetItemList()
	{
		return MyItemList;
	}

	void SetCurItemList(std::shared_ptr<ItemList> _ItemList)
	{
		CurItemList = _ItemList;
	}

	void SetCurEquipItemList(std::shared_ptr<class EquipItemList> _EquipItemList)
	{
		CurEquipItemList = _EquipItemList;
	}

	int ItemFind(const std::string_view& _ItemName, int _ItemType)
	{
		size_t Size = MyItemList[_ItemType].size();

		for (int i = 0; i < Size; i++)
		{
			if (MyItemList[_ItemType][i] != nullptr && MyItemList[_ItemType][i]->ItemName == _ItemName)
			{
				return i;
			}
		}

		return -1;
	}

	int GetNumOfItem(int _ItemType)
	{
		int count = 0;

		for (int i = 0; i < 24; i++)
		{
			if (MyItemList[_ItemType][i] != nullptr)
			{
				count++;
			}
		}

		return count;
	}

	void AddToItemList(const std::shared_ptr<ItemInfo> _ItemInfo, int _ItemType)
	{
		int Index = -1;

		if (Index = ItemFind(_ItemInfo->ItemName, _ItemType), Index != -1)
		{
			if (MyItemList[_ItemType][Index] != nullptr && _ItemType != static_cast<int>(ItemType::Equip))
			{
				MyItemList[_ItemType][Index]->Num++;
				
				//업데이트에 반영되도록 현재 액터의 인벤토리도 업데이트
				if(CurItemList !=nullptr)
				{
					CurItemList->CreateItem(_ItemInfo, _ItemType);
				}
			}
			else if (MyItemList[_ItemType][Index] != nullptr && _ItemType == static_cast<int>(ItemType::Equip))
			{
				for (int i = 0; i < MyItemList[_ItemType].size(); i++)
				{
					if (MyItemList[_ItemType][i] == nullptr)
					{
						MyItemList[_ItemType][i] = _ItemInfo;
						break;
					}
				}

				if (CurItemList != nullptr)
				{
					CurItemList->CreateItem(_ItemInfo, _ItemType);
				}
			}
		}
		else if(Index == -1)
		{
			for (int i = 0; i < MyItemList[_ItemType].size(); i++)
			{
				if (MyItemList[_ItemType][i] == nullptr)
				{
					MyItemList[_ItemType][i] = _ItemInfo;
					break;
				}
			}

			if (CurItemList != nullptr)
			{
				CurItemList->CreateItem(_ItemInfo, _ItemType);
			}
		}
	}

	void DeleteToItemList(const std::string_view& _ItemName, int _ItemType, bool AllDelete = false)
	{

		int Index = ItemFind(_ItemName, _ItemType);
		
		if (AllDelete == true)
		{
			MyItemList[_ItemType][Index] = nullptr;
		}
		else if(AllDelete == false && MyItemList[_ItemType][Index]->Num >= 1)
		{
			MyItemList[_ItemType][Index]->Num--;

			if (MyItemList[_ItemType][Index]->Num <= 0)
			{
				MyItemList[_ItemType][Index] = nullptr;
			}
		}
	}

	void AddToEquipItemList(const std::string_view& _EquipItemName, int _EquipType)
	{
		EquipItemList[_EquipType] = _EquipItemName;

		if (CurEquipItemList != nullptr)
		{
			CurEquipItemList->LoadEquipItem(_EquipType);
		}
	}


	const std::string_view GetEquipItem(int _EquipType)
	{
		return EquipItemList[_EquipType];
	}

	void SetShiftSkill(const std::string_view& _TexName, std::function<void(std::shared_ptr<class Player>)> _SkillFunc)
	{
		ShiftSkillTexName = _TexName.data();
		ShiftSkill = _SkillFunc;

		for (int i = 0; i < QuickSlotList.size(); i++)
		{
			QuickSlotList[i]->SetShiftSlotTexture(ShiftSkillTexName);
		}

		PlayerValue::GetValue()->SetShiftSkillAllPlayer(_SkillFunc);
	}
	void SetInsSkill(const std::string_view& _TexName, std::function<void(std::shared_ptr<class Player>)> _SkillFunc)
	{
		InsSkillTexName = _TexName.data();
		InsSkill = _SkillFunc;

		for (int i = 0; i < QuickSlotList.size(); i++)
		{
			QuickSlotList[i]->SetInsSlotTexture(InsSkillTexName);
		}

		PlayerValue::GetValue()->SetInsSkillAllPlayer(_SkillFunc);
	}
	void SetHomeSkill(const std::string_view& _TexName, std::function<void(std::shared_ptr<class Player>)> _SkillFunc)
	{
		HomeSkillTexName = _TexName.data();
		HomeSkill = _SkillFunc;

		for (int i = 0; i < QuickSlotList.size(); i++)
		{
			QuickSlotList[i]->SetHomeSlotTexture(HomeSkillTexName);
		}

		PlayerValue::GetValue()->SetHomeSkillAllPlayer(_SkillFunc);
	}
	void SetPgUpSkill(const std::string_view& _TexName, std::function<void(std::shared_ptr<class Player>)> _SkillFunc)
	{
		PgUpSkillTexName = _TexName.data();
		PgUpSkill = _SkillFunc;

		for (int i = 0; i < QuickSlotList.size(); i++)
		{
			QuickSlotList[i]->SetPgUpSlotTexture(PgUpSkillTexName);
		}

		PlayerValue::GetValue()->SetPgUpSkillAllPlayer(_SkillFunc);
	}
	void SetCtrlSkill(const std::string_view& _TexName, std::function<void(std::shared_ptr<class Player>)> _SkillFunc)
	{
		CtrlSkillTexName = _TexName.data();
		CtrlSkill = _SkillFunc;

		for (int i = 0; i < QuickSlotList.size(); i++)
		{
			QuickSlotList[i]->SetCtrlSlotTexture(CtrlSkillTexName);
		}

		PlayerValue::GetValue()->SetCtrlSkillAllPlayer(_SkillFunc);
	}
	void SetDelSkill(const std::string_view& _TexName, std::function<void(std::shared_ptr<class Player>)> _SkillFunc)
	{
		DelSkillTexName = _TexName.data();
		DelSkill = _SkillFunc;

		for (int i = 0; i < QuickSlotList.size(); i++)
		{
			QuickSlotList[i]->SetDelSlotTexture(DelSkillTexName);
		}

		PlayerValue::GetValue()->SetDelSkillAllPlayer(_SkillFunc);
	}
	void SetEndSkill(const std::string_view& _TexName, std::function<void(std::shared_ptr<class Player>)> _SkillFunc)
	{
		EndSkillTexName = _TexName.data();
		EndSkill = _SkillFunc;

		for (int i = 0; i < QuickSlotList.size(); i++)
		{
			QuickSlotList[i]->SetEndSlotTexture(EndSkillTexName);
		}

		PlayerValue::GetValue()->SetEndSkillAllPlayer(_SkillFunc);
	}
	void SetPgDNSkill(const std::string_view& _TexName, std::function<void(std::shared_ptr<class Player>)> _SkillFunc)
	{
		PgDNSkillTexName = _TexName.data();
		PgDNSkill = _SkillFunc;

		for (int i = 0; i < QuickSlotList.size(); i++)
		{
			QuickSlotList[i]->SetPgDnSlotTexture(PgDNSkillTexName);
		}

		PlayerValue::GetValue()->SetPgDnSkillAllPlayer(_SkillFunc);
	}

	void SetSkillAllQuickSlot();

protected:

private:
	UIController();
	~UIController();

	static UIController Value;

	//QuickSlot
	std::vector<std::shared_ptr<class QuickSlot>> QuickSlotList;

	std::string ShiftSkillTexName = "";
	std::string InsSkillTexName = "";
	std::string HomeSkillTexName = "";
	std::string PgUpSkillTexName = "";
	std::string CtrlSkillTexName = "";
	std::string DelSkillTexName = "";
	std::string EndSkillTexName = "";
	std::string PgDNSkillTexName = "";

	std::function<void(std::shared_ptr<class Player>)> ShiftSkill = nullptr;
	std::function<void(std::shared_ptr<class Player>)> InsSkill = nullptr;
	std::function<void(std::shared_ptr<class Player>)> HomeSkill = nullptr;
	std::function<void(std::shared_ptr<class Player>)> PgUpSkill = nullptr;
	std::function<void(std::shared_ptr<class Player>)> CtrlSkill = nullptr;
	std::function<void(std::shared_ptr<class Player>)> DelSkill = nullptr;
	std::function<void(std::shared_ptr<class Player>)> EndSkill = nullptr;
	std::function<void(std::shared_ptr<class Player>)> PgDNSkill = nullptr;

	//ItemWindow
	std::map<int, std::vector<std::shared_ptr<ItemInfo>>> MyItemList;

	std::shared_ptr<class ItemList> CurItemList = nullptr;
	//EquipWindow
	std::map <int, std::string> EquipItemList;

	std::shared_ptr<class EquipItemList> CurEquipItemList = nullptr;
};

