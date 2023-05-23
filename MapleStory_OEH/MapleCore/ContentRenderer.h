#pragma once
#include <GameEngineCore/GameEngineSpriteRenderer.h>

class ContentRenderer : public GameEngineSpriteRenderer
{

public:

	ContentRenderer();
	~ContentRenderer();

	ContentRenderer(const ContentRenderer& _Other) = delete;
	ContentRenderer(ContentRenderer&& _Other) noexcept = delete;
	ContentRenderer& operator=(const ContentRenderer& _Other) = delete;
	ContentRenderer& operator=(ContentRenderer&& _Other) noexcept = delete;

	void SetMulColor(float4 _MulColor)
	{
		ColorOptionValue.MulColor = _MulColor;
	}

	void SetPlusColor(float4 _PlusColor)
	{
		ColorOptionValue.PlusColor = _PlusColor;
	}

	void SetUVconstant(float4 _UV)
	{
		UVconstant = _UV;
	}

protected:

private:
	float4 UVconstant = { 0,0,1,1 };
	void Start() override;
};

