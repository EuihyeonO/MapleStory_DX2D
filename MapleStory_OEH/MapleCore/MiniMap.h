#pragma once
#include <GameEngineCore/GameEngineActor.h>

class MiniMap : public GameEngineActor
{

public:

	void SetMap(const std::string_view& _MapName);

	MiniMap();
	~MiniMap();

	MiniMap(const MiniMap& _Other) = delete;
	MiniMap(MiniMap&& _Other) noexcept = delete;
	MiniMap& operator=(const MiniMap& _Other) = delete;
	MiniMap& operator=(MiniMap&& _Other) noexcept = delete;

	std::shared_ptr<class GameEngineUIRenderer> GetMap()
	{
		return Map;
	}

	void SetNPCToMiniMap(float4 _Pos);
	void SetPortalToMiniMap(float4 _Pos);
	void SetMapMark(const std::string_view& _MarkName);
	void SetWorldName(const std::string_view& _MarkName);
	void SetMapName(const std::string_view& _MarkName);
protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	void MiniMapUpdate();

	void MiniMapOn();
	void MiniMapOff();

	bool MiniMapOnOff();

	bool PosUpdate();

	void GetKetInput();
	void CreateInputKey();


	std::list<std::function<bool(MiniMap&)>> UpdateFunction;

	std::shared_ptr<class GameEngineUIRenderer> MapMark;
	std::shared_ptr<class GameEngineUIRenderer> Map;
	std::shared_ptr<class GameEngineUIRenderer> Filter;
	std::shared_ptr<class GameEngineUIRenderer> MiniMapBox;
	std::shared_ptr<class GameEngineUIRenderer> UserMark;

	std::shared_ptr<class ContentFontRenderer> WorldName;
	std::shared_ptr<class ContentFontRenderer> MapName;

	std::shared_ptr<class ContentFontRenderer> WorldNameWhiteLayer;
	std::shared_ptr<class ContentFontRenderer> WorldNameBlackLayer1;
	std::shared_ptr<class ContentFontRenderer> WorldNameBlackLayer2;

	std::shared_ptr<class ContentFontRenderer> MapNameWhiteLayer;
	std::shared_ptr<class ContentFontRenderer> MapNameBlackLayer1;
	std::shared_ptr<class ContentFontRenderer> MapNameBlackLayer2;
	float4 DownSizeRatio = {0,0};

	std::list<std::shared_ptr<GameEngineUIRenderer>> NPCMarkList;
	std::list<std::shared_ptr<GameEngineUIRenderer>> PortalMarkList;
	void MarkOn();
	void MarkOff();
};

