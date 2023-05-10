#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
class Hina : public GameEngineActor
{
public:

	Hina();
	~Hina();

	Hina(const Hina& _Other) = delete;
	Hina(Hina&& _Other) noexcept = delete;
	Hina& operator=(const Hina& _Other) = delete;
	Hina& operator=(Hina&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	void TimeCounting();

	float CurTime = 0.0f;
	float PrevTime = 0.0f;
	float TimeCount = 0.0f;

	void SetFrameList();

	void TextureUpdate();
	void StatusUpdate();

	int AniIndex = 0;
	float AnimationCount = 0.0f;

	std::string Status;
	std::map<std::string, std::vector<float>> FrameList;
	std::shared_ptr<GameEngineSpriteRenderer> HinaRender;
};

