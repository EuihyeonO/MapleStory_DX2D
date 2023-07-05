#pragma once

class MapleCore
{

public:

	MapleCore();
	~MapleCore();

	MapleCore(const MapleCore& _Other) = delete;
	MapleCore(MapleCore&& _Other) noexcept = delete;
	MapleCore& operator=(const MapleCore& _Other) = delete;
	MapleCore& operator=(MapleCore&& _Other) noexcept = delete;
	
	static void ContentsResourcesCreate();
	
	static void GameStart();
	static void GameEnd();

	static class GameEngineSoundPlayer BGMPlayer;

protected:

private:

};

