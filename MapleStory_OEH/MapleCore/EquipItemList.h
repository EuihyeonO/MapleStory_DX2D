#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <map>

class GameEngineUIRenderer;
class EquipItemList : public GameEngineActor
{

public:

	EquipItemList();
	~EquipItemList();

	EquipItemList(const EquipItemList& _Other) = delete;
	EquipItemList(EquipItemList&& _Other) noexcept = delete;
	EquipItemList& operator=(const EquipItemList& _Other) = delete;
	EquipItemList& operator=(EquipItemList&& _Other) noexcept = delete;

	void EquipItem(std::shared_ptr<class Item> _Item);
	
	void LoadAllEquipItem();
	void LoadEquipItem(int _ItemType);

	void ClearEquipItem();
	void SortItem();

	void DeleteEquipItem(int _EquipType);

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	std::map<int, std::shared_ptr<class Item>> MyEquipItems;
};

