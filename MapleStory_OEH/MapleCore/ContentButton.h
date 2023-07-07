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

	void SetPressEvent(std::function<void()> _Event)
	{
		
		PressEvent = _Event;
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

	void SetHoverSound(const std::string_view& _SoundName)
	{
		ContentHoverSound = _SoundName;
	}

	void SetPressSound(const std::string_view& _SoundName)
	{
		ContentPressSound = _SoundName;
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

	void SetPressInter(float _Inter)
	{
		PressInter = _Inter;
	}

	void SetPressStartTime(float _Time)
	{
		PressStartTime = _Time;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;
private:

	std::string_view ContentReleaseImage = "";
	std::string_view ContentHoverImage = "";
	std::string_view ContentPressImage = "";

	std::string_view ContentHoverSound = "";
	bool isPlayHoverSound = false;
	std::string_view ContentPressSound = "";

	std::shared_ptr<GameEngineSpriteRenderer> MyRender = nullptr;
	std::shared_ptr<GameEngineCollision> MyCollision = nullptr;
	bool isUIRender = true;

	float4 HoverScale;
	float4 HoverPos;
	float4 ReleaseScale;
	float4 ReleasePos;
	float4 PressScale;
	float4 PressPos;

	float PressTime = 0.0f;
	float PressStartTime = 0.0f;
	float PressStartTimeCount = 0.0f;
	float PressInter = 0.0f;
	std::function<void()> Click;
	std::function<void()> PressEvent;
};

