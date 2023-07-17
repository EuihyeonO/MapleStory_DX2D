#pragma once
#include <GameEngineCore/GameEngineActor.h>

class KerningCity : public GameEngineActor
{

public:

	KerningCity();
	~KerningCity();

	KerningCity(const KerningCity& _Other) = delete;
	KerningCity(KerningCity&& _Other) noexcept = delete;
	KerningCity& operator=(const KerningCity& _Other) = delete;
	KerningCity& operator=(KerningCity&& _Other) noexcept = delete;
	
	const std::string_view GetColMapName()
	{
		return ColMapName;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	void BackGroundUpdate(float _Deltatime);
	void FadeIn(float _DeltaTime);

	std::function<void(KerningCity&, float)> FadeInUpdate;
	std::shared_ptr<class GameEngineUIRenderer> Black = nullptr;

	std::string ColMapName = "ColKerningCity.png";
	std::string MapName = "KerningCity.png";

	std::shared_ptr<class GameEngineSpriteRenderer> Map = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> BackGround1 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BackGround2 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BackGround3 = nullptr;

	std::shared_ptr<class Portal> Portal1 = nullptr;

};

