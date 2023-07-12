#pragma once
#include "BasicFunction.h"

class GameEngineSpriteRenderer;
class Hina : public BasicFunction
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

	void SetFrameList();

	void TextureUpdate();
	void StatusUpdate();
	
	void OpenWindow();

	int AniIndex = 0;
	float AnimationCount = 0.0f;

	std::string Status;
	std::map<std::string, std::vector<float>> FrameList;
	std::shared_ptr<GameEngineSpriteRenderer> HinaRender;
	std::shared_ptr<class GameEngineCollision> HinaCollision;
	std::shared_ptr<class NPCWindow> MyWindow;
};

