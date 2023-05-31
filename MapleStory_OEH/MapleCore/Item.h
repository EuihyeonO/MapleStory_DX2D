#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineUIRenderer;
class Item : public GameEngineActor
{
	friend class ItemList;
	friend class InventoryWindow;
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
	void SetItemInfo(const std::string_view& _ItemName, int _ItemType);

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	
	std::string ItemName = "";
	int ItemType = 0;

	std::shared_ptr<GameEngineUIRenderer> ItemRender = nullptr;
};

