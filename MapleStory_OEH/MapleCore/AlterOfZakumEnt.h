#pragma once
#include "BasicFunction.h"

class AlterOfZakumEnt : public BasicFunction
{

public:

	const std::string_view GetColMapName()
	{
		return ColMapName;
	}

	AlterOfZakumEnt();
	~AlterOfZakumEnt();

	AlterOfZakumEnt(const AlterOfZakumEnt& _Other) = delete;
	AlterOfZakumEnt(AlterOfZakumEnt&& _Other) noexcept = delete;
	AlterOfZakumEnt& operator=(const AlterOfZakumEnt& _Other) = delete;
	AlterOfZakumEnt& operator=(AlterOfZakumEnt&& _Other) noexcept = delete;

	void ActorDeath();

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	std::string ColMapName = "ColAlterOfZakumEnt.png";
	std::string MapName = "AlterOfZakumEnt.png";

	float XUVCount = 0.0f;
	float DewDropCount = 0.0f;

	std::shared_ptr<class GameEngineSpriteRenderer> Map = nullptr;
	std::shared_ptr<class ContentRenderer> BackGround = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> Layer = nullptr;
	std::shared_ptr<class ContentRenderer> Magma = nullptr;

	void SetFireDewDrop();
	void FireDewDrop();

	void FadeIn(float _DeltaTime);
	std::function<void(AlterOfZakumEnt&, float)> FadeInUpdate;
	std::shared_ptr<class GameEngineUIRenderer> Black = nullptr;
	std::shared_ptr<class Adovis> MyAdovis = nullptr;
	
	std::shared_ptr<class Portal> Portal1 = nullptr;

	std::shared_ptr<class RingPortal> RingPortal1 = nullptr;
	std::shared_ptr<class RingPortal> RingPortal2 = nullptr;
	std::vector<std::pair<bool, std::shared_ptr<class GameEngineSpriteRenderer>>> FireDewDropList;
					
};

