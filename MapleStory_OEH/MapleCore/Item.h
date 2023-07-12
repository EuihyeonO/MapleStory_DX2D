#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineUIRenderer;
class GameEngineCollision;
class Item : public GameEngineActor
{
	friend class ItemList;
	friend class InventoryWindow;
	friend class EquipItemList;

public:

	Item();
	~Item();

	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

	std::shared_ptr<GameEngineUIRenderer> GetItemRender()
	{
		return ItemRender;
	}

	std::shared_ptr<GameEngineCollision> GetItemCollision()
	{
		return ItemCollision;
	}

	void SetItemInfo(std::shared_ptr<struct ItemInfo> _ItemName, int _ItemType);

	void Clicked();
	void EquipThis();

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	
	void NumRenderUpdate();
	void NumRenderOff();
	void NumRenderOn();

	void InfoBoxOn();
	void InfoBoxOff();

	void InfoBoxUpdate();

	const std::string_view GetItemNameToKr(const std::string_view& _Name);

	std::string ItemName = "";

	bool isEmptyItem = false;
	bool isClicked = false;
	bool isEquip = false;

	int ItemType = 0;
	//int EquipLevel = 0;
	//int NumOfItem = 0;
	//int EquipType = -1;
	
	struct ItemInfoBox {
		std::shared_ptr<class ContentUIRenderer> ItemRender;
		std::shared_ptr<class ContentUIRenderer> ItemBackGround;
		std::shared_ptr<class ContentUIRenderer> BoxRender;
		std::shared_ptr<class ContentFontRenderer> ItemName;
		std::shared_ptr<class ContentFontRenderer> ItemNameLayer;
	};

	std::shared_ptr<struct ItemInfo> MyInfo = nullptr;
	std::shared_ptr<ItemInfoBox> MyInfoBox = nullptr;
	int ItemIndex = 0;
	int Digit = 0;

	std::shared_ptr<GameEngineUIRenderer> ItemRender = nullptr;
	std::shared_ptr<GameEngineCollision> ItemCollision = nullptr;

	std::vector<std::shared_ptr<GameEngineUIRenderer>> NumRender;
};

