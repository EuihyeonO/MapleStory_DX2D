#pragma once
#include <GameEngineCore/GameEngineButton.h>

class ContentButton : public GameEngineButton
{

public:

	ContentButton();
	~ContentButton();

	ContentButton(const ContentButton& _Other) = delete;
	ContentButton(ContentButton&& _Other) noexcept = delete;
	ContentButton& operator=(const ContentButton& _Other) = delete;
	ContentButton& operator=(ContentButton&& _Other) noexcept = delete;

	std::shared_ptr<GameEngineSpriteRenderer> GetContentRender()
	{
		return MyRender;
	}

	void SetisUIRenderer(bool _bool)
	{
		isUIRender = _bool;
	}

	void SetEvent(std::function<void()> _Click)
	{
		Click = _Click;
	}

	void SetReleaseTexture(const std::string_view& _ImageName)
	{
		ContentReleaseImage = _ImageName;
	}

	void SetHoverTexture(const std::string_view& _ImageName)
	{
		ContentHoverImage = _ImageName;
	}

	void SetPressTexture(const std::string_view& _ImageName)
	{
		ContentPressImage = _ImageName;
	}

	void SetHoverScale(float4 _Scale)
	{
		HoverScale = _Scale;
	}

	void SetReleaseScale(float4 _Scale)
	{
		ReleaseScale = _Scale;
	}

	void SetPressScale(float4 _Scale)
	{
		PressScale = _Scale;
	}

	void SetHoverPos(float4 _Pos)
	{
		HoverPos = _Pos;
	}

	void SetReleasePos(float4 _Pos)
	{
		ReleasePos = _Pos;
	}

	void SetPressPos(float4 _Pos)
	{
		PressPos = _Pos;
	}

	void SetAllScale(float4 _Scale)
	{
		ReleaseScale = _Scale;
		HoverScale = _Scale;
		PressScale = _Scale;
	}

	void SetAllPos(float4 _Pos)
	{
		ReleasePos = _Pos;
		HoverPos = _Pos;
		PressPos = _Pos;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;
private:

	std::string_view ContentReleaseImage = "";
	std::string_view ContentHoverImage = "";
	std::string_view ContentPressImage = "";

	std::shared_ptr<GameEngineSpriteRenderer> MyRender = nullptr;
	std::shared_ptr<GameEngineCollision> MyCollision = nullptr;
	bool isUIRender = true;

	float4 HoverScale;
	float4 HoverPos;
	float4 ReleaseScale;
	float4 ReleasePos;
	float4 PressScale;
	float4 PressPos;

	std::function<void()> Click;
};

