#pragma once

#include <GameEngineCore/GameEngineFontRenderer.h>

class ContentFontRenderer : public GameEngineFontRenderer
{

public:

	ContentFontRenderer();
	~ContentFontRenderer();

	ContentFontRenderer(const ContentFontRenderer& _Other) = delete;
	ContentFontRenderer(ContentFontRenderer&& _Other) noexcept = delete;
	ContentFontRenderer& operator=(const ContentFontRenderer& _Other) = delete;
	ContentFontRenderer& operator=(ContentFontRenderer&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
};

