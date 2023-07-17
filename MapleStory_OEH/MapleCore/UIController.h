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
	int Num = 1;
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

	void SetCurQuickSlot(std::shared_ptr<class QuickSlot> _QuickSlot)
	{
		CurQuickSlot = _QuickSlot;
	}

	std::map<int, std::vector<std::shared_ptr<ItemInfo>>>& GetItemList()
	{
		return MyItemList;
	}

	void SetCurItemList(std::shared_ptr<ItemList> _ItemList)
	{
		CurItemList = _ItemList;
	}

	std::shared_ptr<ItemList> GetCurItemList()
	{
		return CurItemList;
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
		int Index = ItemFind(_ItemInfo->ItemName, _ItemType);

		if (Index != -1)
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
			int i = 0;

			for (i = 0; i < MyItemList[_ItemType].size(); i++)
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
		
		if(Index == -1)
		{
			return;
		}

		if (AllDelete == true)
		{
			MyItemList[_ItemType][Index] = nullptr;
		}
		else if(AllDelete == false)
		{
			MyItemList[_ItemType][Index]->Num--;

			if (MyItemList[_ItemType][Index]->Num <= 0)
			{
				MyItemList[_ItemType][Index] = nullptr;
			}
		}
	}

	void AddToEquipItemList(const std::shared_ptr<ItemInfo> _EquipItem, int _ItemType)
	{	
		int EquipType = _EquipItem->EquipType;
		
		if (EquipType == static_cast<int>(EquipType::OnePiece))
		{
			EquipType = static_cast<int>(EquipType::Coat);
		}

		//같은 부위를 착용하고 있다면, 끼고 있던 아이템을 벗음
		if(EquipItemList[EquipType] == nullptr)
		{
			EquipItemList[EquipType] = _EquipItem;
		}
		else
		{
			AddToItemList(EquipItemList[EquipType], _ItemType);
			EquipItemList[EquipType] = _EquipItem;
		}

		//한벌옷을 착용했을 때, 바지를 입고 있다면 바지도 벗음
		if (_EquipItem->EquipType == static_cast<int>(EquipType::OnePiece) && EquipItemList[static_cast<int>(EquipType::Pants)] != nullptr)
		{
			AddToItemList(EquipItemList[static_cast<int>(EquipType::Pants)], _ItemType);
			EquipItemList[static_cast<int>(EquipType::Pants)] = _EquipItem;
		}

		//아이템창이 켜있으면, 렌더러를 만들어준다.
		if (CurEquipItemList != nullptr)
		{
			CurEquipItemList->LoadEquipItem(EquipType);
		}

		std::shared_ptr<Player> Newpa = Player::GetCurPlayer();

		//캐릭터의 텍스쳐도 바꿔줌
		if(Player::GetCurPlayer() != nullptr)
		{
			switch (EquipType)
			{
			case static_cast<int>(EquipType::Weapon):
				Player::GetCurPlayer()->SetWeaponName(_EquipItem->ItemName);
				break;
			case static_cast<int>(EquipType::Cap):
				Player::GetCurPlayer()->SetCapName(_EquipItem->ItemName);
				break;
			case static_cast<int>(EquipType::Coat):
				Player::GetCurPlayer()->SetCoatName(_EquipItem->ItemName);
				break;
			case static_cast<int>(EquipType::Pants):
				Player::GetCurPlayer()->SetPantsName(_EquipItem->ItemName);
				break;
			}
		}

	}

	const std::shared_ptr<ItemInfo> GetEquipItem(int _EquipType)
	{
		return EquipItemList[_EquipType];
	}

	void SetShiftSkill(const std::string_view& _TexName, std::function<void(std::shared_ptr<class Player>)> _SkillFunc)
	{
		if (_SkillFunc == nullptr)
		{
			return;
		}

		ShiftSkillTexName = _TexName.data();
		ShiftSkill = _SkillFunc;

		CurQuickSlot->SetShiftSlotTexture(ShiftSkillTexName);

		PlayerValue::GetValue()->SetShiftSkillAllPlayer(_SkillFunc);
	}
	void SetInsSkill(const std::string_view& _TexName, std::function<void(std::shared_ptr<class Player>)> _SkillFunc)
	{
		if (_SkillFunc == nullptr)
		{
			return;
		}

		InsSkillTexName = _TexName.data();
		InsSkill = _SkillFunc;

		CurQuickSlot->SetInsSlotTexture(InsSkillTexName);

		PlayerValue::GetValue()->SetInsSkillAllPlayer(_SkillFunc);
	}
	void SetHomeSkill(const std::string_view& _TexName, std::function<void(std::shared_ptr<class Player>)> _SkillFunc)
	{
		if (_SkillFunc == nullptr)
		{
			return;
		}

		HomeSkillTexName = _TexName.data();
		HomeSkill = _SkillFunc;
			
		CurQuickSlot->SetHomeSlotTexture(HomeSkillTexName);

		PlayerValue::GetValue()->SetHomeSkillAllPlayer(_SkillFunc);
	}
	void SetPgUpSkill(const std::string_view& _TexName, std::function<void(std::shared_ptr<class Player>)> _SkillFunc)
	{
		if (_SkillFunc == nullptr)
		{
			return;
		}

		PgUpSkillTexName = _TexName.data();
		PgUpSkill = _SkillFunc;

		CurQuickSlot->SetPgUpSlotTexture(PgUpSkillTexName);

		PlayerValue::GetValue()->SetPgUpSkillAllPlayer(_SkillFunc);
	}
	void SetCtrlSkill(const std::string_view& _TexName, std::function<void(std::shared_ptr<class Player>)> _SkillFunc)
	{
		if (_SkillFunc == nullptr)
		{
			return;
		}

		CtrlSkillTexName = _TexName.data();
		CtrlSkill = _SkillFunc;

		CurQuickSlot->SetCtrlSlotTexture(CtrlSkillTexName);

		PlayerValue::GetValue()->SetCtrlSkillAllPlayer(_SkillFunc);
	}

	void SetDelSkill(const std::string_view& _TexName, std::function<void(std::shared_ptr<class Player>)> _SkillFunc)
	{
		if (_SkillFunc == nullptr)
		{
			return;
		}

		DelSkillTexName = _TexName.data();
		DelSkill = _SkillFunc;
			
		CurQuickSlot->SetDelSlotTexture(DelSkillTexName);

		PlayerValue::GetValue()->SetDelSkillAllPlayer(_SkillFunc);
	}
	void SetEndSkill(const std::string_view& _TexName, std::function<void(std::shared_ptr<class Player>)> _SkillFunc)
	{
		if (_SkillFunc == nullptr)
		{
			return;
		}

		EndSkillTexName = _TexName.data();
		EndSkill = _SkillFunc;

		CurQuickSlot->SetEndSlotTexture(EndSkillTexName);

		PlayerValue::GetValue()->SetEndSkillAllPlayer(_SkillFunc);
	}
	void SetPgDNSkill(const std::string_view& _TexName, std::function<void(std::shared_ptr<class Player>)> _SkillFunc)
	{
		if (_SkillFunc == nullptr)
		{
			return;
		}

		PgDNSkillTexName = _TexName.data();
		PgDNSkill = _SkillFunc;

		CurQuickSlot->SetPgDnSlotTexture(PgDNSkillTexName);

		PlayerValue::GetValue()->SetPgDnSkillAllPlayer(_SkillFunc);
	}

	void LoadQuickSlotSkill()
	{
		if(ShiftSkillTexName != "" && ShiftSkill != nullptr)
		{
			CurQuickSlot->SetShiftSlotTexture(ShiftSkillTexName);
			PlayerValue::GetValue()->SetShiftSkillAllPlayer(ShiftSkill);
		}

		if(CtrlSkillTexName != "" && CtrlSkill != nullptr)
		{
			CurQuickSlot->SetCtrlSlotTexture(CtrlSkillTexName);
			PlayerValue::GetValue()->SetCtrlSkillAllPlayer(CtrlSkill);
		}

		if(EndSkillTexName != "" && EndSkill != nullptr)
		{
			CurQuickSlot->SetEndSlotTexture(EndSkillTexName);
			PlayerValue::GetValue()->SetEndSkillAllPlayer(EndSkill);
		}

		if(HomeSkillTexName != "" && HomeSkill != nullptr)
		{
			CurQuickSlot->SetHomeSlotTexture(HomeSkillTexName);
			PlayerValue::GetValue()->SetHomeSkillAllPlayer(HomeSkill);
		}

		if(InsSkillTexName != "" && InsSkill != nullptr)
		{
			CurQuickSlot->SetInsSlotTexture(InsSkillTexName);
			PlayerValue::GetValue()->SetInsSkillAllPlayer(InsSkill);
		}

		if(PgUpSkillTexName != "" && PgUpSkill != nullptr)
		{
			CurQuickSlot->SetPgUpSlotTexture(PgUpSkillTexName);
			PlayerValue::GetValue()->SetPgUpSkillAllPlayer(PgUpSkill);
		}

		if(DelSkillTexName != "" && DelSkill != nullptr)
		{
			CurQuickSlot->SetDelSlotTexture(DelSkillTexName);
			PlayerValue::GetValue()->SetDelSkillAllPlayer(DelSkill);
		}

		if(PgDNSkillTexName != "" && PgDNSkill != nullptr)
		{
			CurQuickSlot->SetPgDnSlotTexture(PgDNSkillTexName);
			PlayerValue::GetValue()->SetPgDnSkillAllPlayer(PgDNSkill);
		}
	}

	void SetSkillAllQuickSlot();

protected:

private:
	UIController();
	~UIController();

	static UIController Value;

	//QuickSlot
	std::shared_ptr<class QuickSlot> CurQuickSlot;

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
	std::map <int, std::shared_ptr<ItemInfo>> EquipItemList;

	std::shared_ptr<class EquipItemList> CurEquipItemList = nullptr;

public:
	void AddToQuestList(const std::string_view& _Quest)
	{
		if (isQuestInList(_Quest) == true)
		{
			return;
		}

		QuestList.push_back(_Quest.data());
	}

	void QuestClear(const std::string_view& _Quest)
	{
		if (isQuestInList(_Quest) != true)
		{
			return;
		}

		std::list<std::string>::iterator StartIter = QuestList.begin();
		std::list<std::string>::iterator EndIter = QuestList.end();

		for (; StartIter != EndIter;)
		{
			if (*StartIter == _Quest.data())
			{
				StartIter = QuestList.erase(StartIter);
				break;
			}
			StartIter++;
		}

		ClearQuestList.push_back(_Quest.data());
	}

	bool isQuestInList(const std::string_view& _Quest)
	{
		std::list<std::string>::iterator StartIter = QuestList.begin();
		std::list<std::string>::iterator EndIter = QuestList.end();

		for (; StartIter != EndIter; StartIter++)
		{
			if (*StartIter == _Quest.data())
			{
				return true;
			}
		}
		return false;
	}

	bool isQuestInClearList(const std::string_view& _Quest)
	{
		std::list<std::string>::iterator StartIter = ClearQuestList.begin();
		std::list<std::string>::iterator EndIter = ClearQuestList.end();

		for (; StartIter != EndIter; StartIter++)
		{
			if (*StartIter == _Quest.data())
			{
				return true;
			}
		}
		return false;
	}
private:
	std::list<std::string> QuestList;
	std::list<std::string> ClearQuestList;
};

