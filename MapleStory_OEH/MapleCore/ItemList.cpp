#include "PrecompileHeader.h"
#include "ItemList.h"
#include "Item.h"
#include "UIController.h"
#include "Mouse.h"
#include "PlayerValue.h"
#include "ContentFontRenderer.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineInput.h>

ItemList::ItemList()
{
}

ItemList::~ItemList()
{
}

void ItemList::Start()
{
	MyItemList[(static_cast<int>(ItemType::Equip))].reserve(24);
	MyItemList[(static_cast<int>(ItemType::Use))].reserve(24);
	MyItemList[(static_cast<int>(ItemType::Etc))].reserve(24);
	MyItemList[(static_cast<int>(ItemType::Setup))].reserve(24);
	MyItemList[(static_cast<int>(ItemType::Cash))].reserve(24);

	for (int i = 0; i < 24; i++)
	{
		MyItemList[(static_cast<int>(ItemType::Equip))].push_back(nullptr);
		MyItemList[(static_cast<int>(ItemType::Use))].push_back(nullptr);
		MyItemList[(static_cast<int>(ItemType::Etc))].push_back(nullptr);
		MyItemList[(static_cast<int>(ItemType::Setup))].push_back(nullptr);
		MyItemList[(static_cast<int>(ItemType::Cash))].push_back(nullptr);
	}
}

void ItemList::Update(float _DeltaTime) 
{

}

void ItemList::Render(float _DeltaTime) 
{

}

void ItemList::CreateItem(const std::shared_ptr<ItemInfo> _ItemInfo, int _ItemType, int _Index)
{
	if (_ItemInfo == nullptr)
	{
		return;
	}

	//기존에 있던 아이템이라면
	int Index = FindItem(_ItemInfo->ItemName, _ItemType);
	
	if (Index != -1 && _ItemType != static_cast<int>(ItemType::Equip))
	{
		MyItemList[_ItemType][Index]->MyInfo->Num++;
		SortItemListToType(_ItemType);
		return;
	}

	std::shared_ptr<Item> NewItem = GetLevel()->CreateActor<Item>();

	NewItem->SetItemInfo(_ItemInfo, _ItemType);
	NewItem->GetTransform()->SetParent(GetTransform());

	//빈공간을 채우지 않게 하기 위해
	if (_Index != -1)
	{
		MyItemList[static_cast<int>(_ItemType)][_Index] = NewItem;
		SortItemListToType(_ItemType);
		return;
	}

	size_t Size = MyItemList[_ItemType].size();
	//새로운 아이템이라면 빈공간부터
	for (int i = 0; i < Size; i++)
	{	
		if (MyItemList[static_cast<int>(_ItemType)][i] == nullptr)
		{
			MyItemList[static_cast<int>(_ItemType)][i] = NewItem;
			SortItemListToType(_ItemType);
			return;
		}
	}
}

void ItemList::LoadItem(const std::shared_ptr<ItemInfo> _ItemInfo, int _ItemType, int _Index)
{
	if(_ItemInfo == nullptr)
	{
		MyItemList[static_cast<int>(_ItemType)][_Index] = nullptr;
	}
	else
	{
		CreateItem(_ItemInfo, _ItemType, _Index);
	}

	return;
}

void ItemList::LoadAllItem()
{
	std::map<int, std::vector<std::shared_ptr<ItemInfo>>>& Copy = UIController::GetUIController()->GetItemList();

	size_t Size = 24;

	int i = 0;

	for (i = 0; i < Size; i++)
	{
		LoadItem(Copy[static_cast<int>(ItemType::Equip)][i], static_cast<int>(ItemType::Equip), i);
	}

	for (i = 0; i < Size; i++)
	{
		LoadItem(Copy[static_cast<int>(ItemType::Use)][i], static_cast<int>(ItemType::Use), i);
	}

	for (i = 0; i < Size; i++)
	{
		LoadItem(Copy[static_cast<int>(ItemType::Etc)][i], static_cast<int>(ItemType::Etc), i);
	}

	for (i = 0; i < Size; i++)
	{
		LoadItem(Copy[static_cast<int>(ItemType::Setup)][i], static_cast<int>(ItemType::Setup), i);
	}

	for (i = 0; i < Size; i++)
	{
		LoadItem(Copy[static_cast<int>(ItemType::Cash)][i], static_cast<int>(ItemType::Cash), i);
	}
}

void ItemList::SortItemListToType(int _ItemType)
{
	int count = 0;

	size_t Size = MyItemList[_ItemType].size();

	for (int i = 0; i < Size; i++)
	{
		if (MyItemList[_ItemType][i] == nullptr)
		{
			count++;
			continue;
		}

		if (MyItemList[_ItemType][i]->isClicked == true)
		{
			count++;
			continue;
		}

		int Yindex = count / 4;
		int Xindex = count % 4;

		MyItemList[_ItemType][i]->GetTransform()->SetLocalPosition(StartPos + float4{Xinterval * Xindex, Yinterval * Yindex });
		MyItemList[_ItemType][i]->NumRenderUpdate();

		MyItemList[_ItemType][i]->ItemIndex = count;
		count++;
	}
}

void ItemList::ClearItem()
{
	size_t Size = MyItemList[static_cast<int>(ItemType::Equip)].size();

	for (int i = 0; i < Size; i++)
	{
		if (MyItemList[static_cast<int>(ItemType::Equip)][i] == nullptr)
		{
			continue;
		}

		if (MyItemList[static_cast<int>(ItemType::Equip)][i]->isClicked == true)
		{
			MyItemList[static_cast<int>(ItemType::Equip)][i]->ItemRender->GetTransform()->SetParent(MyItemList[static_cast<int>(ItemType::Equip)][i]->GetTransform());
			MyItemList[static_cast<int>(ItemType::Equip)][i]->ItemCollision->GetTransform()->SetParent(MyItemList[static_cast<int>(ItemType::Equip)][i]->GetTransform());
		}

		MyItemList[static_cast<int>(ItemType::Equip)][i]->Death();
		MyItemList[static_cast<int>(ItemType::Equip)][i] = nullptr;
	}

	Size = MyItemList[static_cast<int>(ItemType::Use)].size();
	
	for (int i = 0; i < Size; i++)
	{
		if (MyItemList[static_cast<int>(ItemType::Use)][i] == nullptr)
		{
			continue;
		}

		if (MyItemList[static_cast<int>(ItemType::Use)][i]->isClicked == true)
		{
			MyItemList[static_cast<int>(ItemType::Use)][i]->ItemRender->GetTransform()->SetParent(MyItemList[static_cast<int>(ItemType::Use)][i]->GetTransform());
			MyItemList[static_cast<int>(ItemType::Use)][i]->ItemCollision->GetTransform()->SetParent(MyItemList[static_cast<int>(ItemType::Use)][i]->GetTransform());
		}

		MyItemList[static_cast<int>(ItemType::Use)][i]->Death();
		MyItemList[static_cast<int>(ItemType::Use)][i] = nullptr;
	}

	Size = MyItemList[static_cast<int>(ItemType::Etc)].size();

	for (int i = 0; i < Size; i++)
	{
		if (MyItemList[static_cast<int>(ItemType::Etc)][i] == nullptr)
		{
			continue;
		}

		if (MyItemList[static_cast<int>(ItemType::Etc)][i]->isClicked == true)
		{
			MyItemList[static_cast<int>(ItemType::Etc)][i]->ItemRender->GetTransform()->SetParent(MyItemList[static_cast<int>(ItemType::Etc)][i]->GetTransform());
			MyItemList[static_cast<int>(ItemType::Etc)][i]->ItemCollision->GetTransform()->SetParent(MyItemList[static_cast<int>(ItemType::Etc)][i]->GetTransform());
		}

		MyItemList[static_cast<int>(ItemType::Etc)][i]->Death();
		MyItemList[static_cast<int>(ItemType::Etc)][i] = nullptr;
	}

	Size = MyItemList[static_cast<int>(ItemType::Setup)].size();

	for (int i = 0; i < Size; i++)
	{
		if (MyItemList[static_cast<int>(ItemType::Setup)][i] == nullptr)
		{
			continue;
		}

		if (MyItemList[static_cast<int>(ItemType::Setup)][i]->isClicked == true)
		{
			MyItemList[static_cast<int>(ItemType::Setup)][i]->ItemRender->GetTransform()->SetParent(MyItemList[static_cast<int>(ItemType::Setup)][i]->GetTransform());
			MyItemList[static_cast<int>(ItemType::Setup)][i]->ItemCollision->GetTransform()->SetParent(MyItemList[static_cast<int>(ItemType::Setup)][i]->GetTransform());
		}

		MyItemList[static_cast<int>(ItemType::Setup)][i]->Death();
		MyItemList[static_cast<int>(ItemType::Setup)][i] = nullptr;
	}

	Size = MyItemList[static_cast<int>(ItemType::Cash)].size();

	for (int i = 0; i < Size; i++)
	{
		if (MyItemList[static_cast<int>(ItemType::Cash)][i] == nullptr)
		{
			continue;
		}

		if (MyItemList[static_cast<int>(ItemType::Cash)][i]->isClicked == true)
		{
			MyItemList[static_cast<int>(ItemType::Cash)][i]->ItemRender->GetTransform()->SetParent(MyItemList[static_cast<int>(ItemType::Cash)][i]->GetTransform());
			MyItemList[static_cast<int>(ItemType::Cash)][i]->ItemCollision->GetTransform()->SetParent(MyItemList[static_cast<int>(ItemType::Cash)][i]->GetTransform());
		}

		MyItemList[static_cast<int>(ItemType::Cash)][i]->Death();
		MyItemList[static_cast<int>(ItemType::Cash)][i] = nullptr;
	}
}


void ItemList::ChangeRenderItem(int _CurItemType, int _NextItemType)
{
	InventoryItemOff(_CurItemType);
	InventoryItemOn(_NextItemType);
}

void ItemList::InventoryItemOn(int _CurItemType)
{
	size_t Size = MyItemList[_CurItemType].size();

	for (int i = 0; i < Size; i++)
	{
		if(MyItemList[_CurItemType][i] != nullptr)
		{
			MyItemList[_CurItemType][i]->GetItemRender()->On();
			MyItemList[_CurItemType][i]->GetItemCollision()->On();
			MyItemList[_CurItemType][i]->NumRenderOn();
		}
	}
}

void ItemList::InventoryItemOff(int _CurItemType)
{
	size_t Size = MyItemList[_CurItemType].size();

	for (int i = 0; i < Size; i++)
	{
		if (MyItemList[_CurItemType][i] != nullptr)
		{
			MyItemList[_CurItemType][i]->GetItemRender()->Off();
			MyItemList[_CurItemType][i]->GetItemCollision()->Off();
			MyItemList[_CurItemType][i]->NumRenderOff();
		}
	}
}


int ItemList::GetRealSizeOfItemList(int _ItemType)
{
	int count = 0;

	size_t Size = MyItemList[_ItemType].size();

	for (int i = 0; i < Size; i++)
	{
		if(MyItemList[_ItemType][i] != nullptr)
		{
			count++;
		}
	}

	return count;
}

void ItemList::EquipItem(std::shared_ptr<Item> _Item)
{
	if (_Item->MyInfo->Level > PlayerValue::GetValue()->GetLevel())
	{
		return;
	}

	std::string ItemName = GameEngineString::ToUpper(_Item->ItemName);
	int ItemType = _Item->ItemType;


	UIController::GetUIController()->AddToEquipItemList(_Item->MyInfo, ItemType);
	DeleteItem(_Item);
}

void ItemList::DeleteItem(std::shared_ptr<Item> _Item)
{
	int ItemType = _Item->ItemType;

	std::map<int, std::vector<std::shared_ptr<ItemInfo>>>& CurList =  UIController::GetUIController()->GetItemList();

	UIController::GetUIController()->DeleteToItemList(_Item->MyInfo->ItemName, ItemType);
	
	std::map<int, std::vector<std::shared_ptr<ItemInfo>>>& NextList = UIController::GetUIController()->GetItemList();

	size_t Size = MyItemList[ItemType].size();

	for (int i = 0; i < Size; i++)
	{
		if (MyItemList[ItemType][i] == _Item)
		{
			if (MyItemList[ItemType][i]->MyInfo->Num <= 0)
			{
				MyItemList[ItemType][i]->Death();
				MyItemList[ItemType][i] = nullptr;
			}
		}
	}
}

int ItemList::FindItem(const std::string_view& _ItemName, int _ItemType)
{
	size_t Size = MyItemList[_ItemType].size();

	for (int i = 0; i < Size; i++)
	{
		if (MyItemList[_ItemType][i] != nullptr && MyItemList[_ItemType][i]->MyInfo->ItemName == _ItemName)
		{
			return i;
		}
	}

	return -1;
}