#pragma once
#include "BasicFunction.h"

class GameEngineSpriteRenderer;
class Rozar : public BasicFunction
{
public:

public:

	Rozar();
	~Rozar();

	Rozar(const Rozar& _Other) = delete;
	Rozar(Rozar&& _Other) noexcept = delete;
	Rozar& operator=(const Rozar& _Other) = delete;
	Rozar& operator=(Rozar&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	void TextureUpdate();
	void StatusUpdate();

	int AniIndex = 0;
	float AnimationCount = 0.0f;

	std::string Status;
	float WinkFrame[2] = { 0.2f, 4.8f };
	std::shared_ptr<GameEngineSpriteRenderer> RozarRender;
};
