#pragma once

class GameEngineVideo
{

public:

	GameEngineVideo();
	~GameEngineVideo();

	GameEngineVideo(const GameEngineVideo& _Other) = delete;
	GameEngineVideo(GameEngineVideo&& _Other) noexcept = delete;
	GameEngineVideo& operator=(const GameEngineVideo& _Other) = delete;
	GameEngineVideo& operator=(GameEngineVideo&& _Other) noexcept = delete;

protected:

private:

};

