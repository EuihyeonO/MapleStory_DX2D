#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <list>

class GameEngineSpriteRenderer;
class StatusWindow : public GameEngineActor
{

public:

	StatusWindow();
	~StatusWindow();

	StatusWindow(const StatusWindow& _Other) = delete;
	StatusWindow(StatusWindow&& _Other) noexcept = delete;
	StatusWindow& operator=(const StatusWindow& _Other) = delete;
	StatusWindow& operator=(StatusWindow&& _Other) noexcept = delete;
	
	void ButtonDeath();

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	void StatUpdate();
	void ButtonUpdate();

	std::shared_ptr<class GameEngineUIRenderer> MainWindow;
	std::shared_ptr<class GameEngineCollision> MainWindowClickBar;
	std::shared_ptr<class GameEngineUIRenderer> SubWindow;

	std::shared_ptr<class ContentFontRenderer> Hp;
	std::shared_ptr<class ContentFontRenderer> Mp;
	std::shared_ptr<class ContentFontRenderer> Level;
	std::shared_ptr<class ContentFontRenderer> Exp;

	std::shared_ptr<class ContentFontRenderer> StatPoint;
	
	std::shared_ptr<class ContentFontRenderer> Str;
	std::shared_ptr<class ContentButton> StrBt;
	std::shared_ptr<class ContentFontRenderer> Dex;
	std::shared_ptr<class ContentButton> DexBt;
	std::shared_ptr<class ContentFontRenderer> Int;
	std::shared_ptr<class ContentButton> IntBt;
	std::shared_ptr<class ContentFontRenderer> Luk;
	std::shared_ptr<class ContentButton> LukBt;

	std::shared_ptr<class ContentFontRenderer> AttRender;


};

