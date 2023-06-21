#pragma once
#include <GameEngineCore/GameEngineSpriteRenderer.h>

class ContentUIRenderer : public GameEngineSpriteRenderer
{

public:

	ContentUIRenderer();
	~ContentUIRenderer();

	ContentUIRenderer(const ContentUIRenderer& _Other) = delete;
	ContentUIRenderer(ContentUIRenderer&& _Other) noexcept = delete;
	ContentUIRenderer& operator=(const ContentUIRenderer& _Other) = delete;
	ContentUIRenderer& operator=(ContentUIRenderer&& _Other) noexcept = delete;

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


	void SetCircleMulColor(float4 _CircleMulColor)
	{
		CircleMulColor = _CircleMulColor;
	}

protected:

private:
	float4 UVconstant = { 0,0,1,1 };
	float4 CircleMulColor = { 0, 0, -1, 0 };

	void Start() override;
};

