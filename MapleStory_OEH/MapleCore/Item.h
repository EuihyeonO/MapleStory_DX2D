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

	void SetMyInfoBox();

	const std::string_view GetItemNameToKr(const std::string_view& _Name);

	void SetItemToolTip(std::shared_ptr<class ContentFontRenderer>  _FontRenderer);
	void SetInfoBoxPos();

	std::string ItemName = "";

	bool isEmptyItem = false;
	bool isClicked = false;
	bool isEquip = false;

	int ItemType = 0;
	//int EquipLevel = 0;
	//int NumOfItem = 0;
	//int EquipType = -1;

	struct ReQuiredStatInfo {
		int ReQuiredLev;
		int ReQuiredStr;
		int ReQuiredDex;
		int ReQuiredInt;
		int ReQuiredLuk;
	};

	struct StatRenderer {
		std::vector<std::shared_ptr<class ContentUIRenderer>> LevRender;
		std::vector<std::shared_ptr<class ContentUIRenderer>> StrRender;
		std::vector<std::shared_ptr<class ContentUIRenderer>> DexRender;
		std::vector<std::shared_ptr<class ContentUIRenderer>> IntRender;
		std::vector<std::shared_ptr<class ContentUIRenderer>> LukRender;
	};

	struct ItemInfoBox {
		std::shared_ptr<class ContentUIRenderer> ItemRender;
		std::shared_ptr<class ContentUIRenderer> ItemBackGround;
		std::shared_ptr<class ContentUIRenderer> BoxRender;
		std::shared_ptr<class ContentFontRenderer> ItemName;
		std::shared_ptr<class ContentFontRenderer> ItemNameLayer;
		std::shared_ptr<class ContentFontRenderer> ToolTip;
		std::shared_ptr<class ContentUIRenderer> StatInfo = nullptr;
		std::shared_ptr<StatRenderer> ReQuiredStat = nullptr;

		std::shared_ptr<class ContentFontRenderer> Beginner;
		std::shared_ptr<class ContentFontRenderer> Warrior;
		std::shared_ptr<class ContentFontRenderer> archer;
		std::shared_ptr<class ContentFontRenderer> Magician;
		std::shared_ptr<class ContentFontRenderer> Log;

		std::shared_ptr<class ContentFontRenderer> InfoText;
		std::shared_ptr<class ContentFontRenderer> Att;

	};

	void StatRenderOn();
	void StatRenderOff();

	void SetStatRender();
	void SetRequiredStat();

	void UseItem();


	std::shared_ptr<struct ItemInfo> MyInfo = nullptr;
	std::shared_ptr<ItemInfoBox> MyInfoBox = nullptr;
	std::shared_ptr<ReQuiredStatInfo> MyRequiredStat = nullptr;


	int ItemIndex = 0;
	int Digit = 0;

	std::shared_ptr<GameEngineUIRenderer> ItemRender = nullptr;
	std::shared_ptr<GameEngineCollision> ItemCollision = nullptr;

	std::vector<std::shared_ptr<GameEngineUIRenderer>> NumRender;
};

