#pragma once
#include "BasicFunction.h"

class NPCWindow : public BasicFunction
{

public:

	NPCWindow();
	~NPCWindow();

	NPCWindow(const NPCWindow& _Other) = delete;
	NPCWindow(NPCWindow&& _Other) noexcept = delete;
	NPCWindow& operator=(const NPCWindow& _Other) = delete;
	NPCWindow& operator=(NPCWindow&& _Other) noexcept = delete;
	
	void SetNPC(const std::string_view& _TextureName, const std::string_view& _NPCName);
	void SetDialogText(const std::string_view& _Text);

	void ChangeDialog(const std::string_view& _NewText);
	void AddToTextButton(const std::string_view& _Text, int Index, std::function<void()> _Function = nullptr);

	void SetCloseButton(int _Index, std::function<void()> _Event);
	void SetNextButton(int _Index);
	void SetPrevButton(int _Index);
	void SetOKButton(int _Index, std::function<void()> _Event);

	void CreateUIButtonList(int _Index);

	void ButtonsDeath();
protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	void TextUpdate();

	void UIButtonsOn();
	void UIButtonsOff();
	std::shared_ptr<class GameEngineUIRenderer> BackGround = nullptr;

	std::shared_ptr<class GameEngineUIRenderer> NPCRender = nullptr;
	std::shared_ptr<class ContentFontRenderer> NPCNameFont = nullptr;

	std::shared_ptr<class ContentFontRenderer> DialogTextFont = nullptr;
	std::wstring DialogText;
	std::wstring RenderText;

	std::function<void(NPCWindow&)> UpdateFunc = nullptr;
	float TextCount = 0.0f;
	int TextIndex = 0;

	struct TextButton
	{
		std::shared_ptr<class ContentFontRenderer> Text = nullptr;
		std::shared_ptr<class GameEngineCollision> Col = nullptr;
		std::function<void()> Event = nullptr;
	};

	struct UIButtons
	{
		std::shared_ptr<class GameEngineButton> Close = nullptr;
		std::shared_ptr<class GameEngineButton> Next = nullptr;
		std::shared_ptr<class GameEngineButton> Prev = nullptr;
		std::shared_ptr<class GameEngineButton> OK = nullptr;
	};

	int DialogIndex = 0;

	std::map<int, std::list<std::shared_ptr<TextButton>>> TextButtonList;
	std::map<int, std::shared_ptr<UIButtons>> UIButtonList;
};

