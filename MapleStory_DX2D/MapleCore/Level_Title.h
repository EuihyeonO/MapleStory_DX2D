#pragma once

#include <GameEngineBase/GameEngineTimeEvent.h>
#include <GameEngineCore\GameEngineLevel.h>

// Ό³Έν :
class Level_Title : public GameEngineLevel
{

public:

	Level_Title();
	~Level_Title();

	Level_Title(const Level_Title& _Other) = delete;
	Level_Title(Level_Title&& _Other) noexcept = delete;
	Level_Title& operator=(const Level_Title& _Other) = delete;
	Level_Title& operator=(Level_Title&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	void CameraMove(float _DeltaTime);

	bool isCamUp = false;
	bool isCamDown = false;

	int CameraIndex = 0;

	float4 DestiPos;
	float4 CamPos;

	float LerpRatio = 0.0f;
	float LerpSpeed = 3.f;

	float4 LerpCamPos = {0,0};
};

