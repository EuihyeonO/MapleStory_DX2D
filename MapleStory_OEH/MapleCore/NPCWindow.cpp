#include "PrecompileHeader.h"
#include "NPCWindow.h"
#include "ContentFontRenderer.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineButton.h>

NPCWindow::NPCWindow()
{
}

NPCWindow::~NPCWindow()
{
}

void NPCWindow::Start()
{
	TimeCounting();

	BackGround = CreateComponent<GameEngineUIRenderer>();
	BackGround->SetScaleToTexture("NPCWindow.png");

	NPCNameFont = CreateComponent<ContentFontRenderer>();
	NPCNameFont->SetFont("±¼¸²");
	NPCNameFont->SetScale(12.0f);
	NPCNameFont->GetTransform()->SetLocalPosition({-206, -36});
	NPCNameFont->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	
	NPCRender = CreateComponent<GameEngineUIRenderer>();
	NPCRender->GetTransform()->SetLocalPosition({ -187, 3 });

	DialogTextFont = CreateComponent<ContentFontRenderer>();
	DialogTextFont->SetFont("±¼¸²");
	DialogTextFont->SetScale(12.0f);
	DialogTextFont->GetTransform()->SetLocalPosition({ -105, 85 });
	DialogTextFont->SetColor({ 0.1f, 0.1f, 0.1f, 1.0f });
}

void NPCWindow::Update(float _DeltaTime)
{
	if (UpdateFunc != nullptr)
	{
		UpdateFunc(*this);
	}

	if (TextButtonList[DialogIndex].size() >= 1)
	{
		std::list<std::shared_ptr<TextButton>>::iterator Start = TextButtonList[DialogIndex].begin();
		std::list<std::shared_ptr<TextButton>>::iterator End = TextButtonList[DialogIndex].end();

		int count = 0;
		for (; Start != End; Start++)
		{
			
			(*Start)->Text->GetTransform()->SetLocalPosition({-106, -17.0f * count});
			(*Start)->Col->GetTransform()->SetLocalPosition(GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition() + float4{ (*Start)->Text->GetTransform()->GetLocalPosition() } + float4{ (*Start)->Col->GetTransform()->GetLocalScale().hx(), -12.0f});

			if ((*Start)->Col->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D) != nullptr)
			{
				(*Start)->Text->SetColor({ 0.0f, 0.0f, 1.0f, 1.0f });

				if (GameEngineInput::IsDown("LClick") == true && (*Start)->Event != nullptr)
				{
					(*Start)->Event();
				}
			}
			else
			{
				(*Start)->Text->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
			}

			count++;
		}
	}
}

void NPCWindow::Render(float _DeltaTime)
{

}

void NPCWindow::SetNPC(const std::string_view& _TextureName, const std::string_view& _NPCName)
{
	NPCNameFont->SetText(_NPCName);
	NPCRender->SetScaleToTexture(_TextureName);
}

void NPCWindow::TextUpdate()
{

	if (TextIndex >= DialogText.size())
	{
		return;
	}

	TimeCounting();
	TextCount += TimeCount;

	if (TextCount >= 0.005f)
	{
		TextCount = 0.0f;
		RenderText.push_back(DialogText[TextIndex]);
		TextIndex++;

		DialogTextFont->SetText(GameEngineString::UniCodeToAnsi(RenderText));
	}
}

void NPCWindow::SetDialogText(const std::string_view& _Text)
{
	DialogText = GameEngineString::AnsiToUniCode(_Text);
	UpdateFunc = &NPCWindow::TextUpdate;
}

void NPCWindow::AddToTextButton(const std::string_view& _Text, int Index, std::function<void()> _Event)
{
	std::shared_ptr<ContentFontRenderer> NewFont = CreateComponent<ContentFontRenderer>();
	NewFont->SetFont("±¼¸²");
	NewFont->SetScale(12.0f);
	NewFont->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	NewFont->SetText(_Text);

	std::shared_ptr<GameEngineCollision> NewFontCollision = CreateComponent<GameEngineCollision>();
	NewFontCollision->SetColType(ColType::AABBBOX2D);
	NewFontCollision->GetTransform()->SetLocalScale({ _Text.size() * 6.0f, 12.0f });
	NewFontCollision->GetTransform()->SetLocalPosition(GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition() + float4{NewFont->GetTransform()->GetLocalPosition()} + float4{ _Text.size() * 6.0f / 2, -12.0f });

	std::shared_ptr<TextButton> NewButton = std::make_shared<TextButton>();
	NewButton->Text = NewFont;
	NewButton->Col = NewFontCollision;
	NewButton->Event = _Event;

	if (DialogIndex != Index)
	{
		NewFont->Off();
		NewFontCollision->Off();
	}

	TextButtonList[Index].push_back(NewButton);
}

void NPCWindow::ChangeDialog(const std::string_view& _NewText)
{
	DialogText.clear();
	DialogText = GameEngineString::AnsiToUniCode(_NewText);

	RenderText.clear();

	TextIndex = 0;
	TextCount = 0.0f;

	if (TextButtonList[DialogIndex].size() >= 1)
	{
		std::list<std::shared_ptr<TextButton>>::iterator IterStart = TextButtonList[DialogIndex].begin();
		std::list<std::shared_ptr<TextButton>>::iterator IterEnd = TextButtonList[DialogIndex].end();

		for (; IterStart != IterEnd; IterStart++)
		{
			(*IterStart)->Col->Off();
			(*IterStart)->Text->Off();
		}
	}
	
	UIButtonsOff();

	DialogIndex++;

	if (TextButtonList[DialogIndex].size() >= 1)
	{
		std::list<std::shared_ptr<TextButton>>::iterator IterStart = TextButtonList[DialogIndex].begin();
		std::list<std::shared_ptr<TextButton>>::iterator IterEnd = TextButtonList[DialogIndex].end();

		for (; IterStart != IterEnd; IterStart++)
		{
			(*IterStart)->Col->On();
			(*IterStart)->Text->On();
		}
	}

	UIButtonsOn();
}

void NPCWindow::CreateUIButtonList(int _Index)
{
	UIButtonList[_Index] = std::make_shared<UIButtons>();
}

void NPCWindow::SetCloseButton(int _Index, std::function<void()> _Event)
{
	UIButtonList[_Index]->Close = GetLevel()->CreateActor<GameEngineButton>();
	UIButtonList[_Index]->Close->SetReleaseTexture("NPCWindowCloseRelease.png");
	UIButtonList[_Index]->Close->SetHoverTexture("NPCWindowCloseHover.png");
	UIButtonList[_Index]->Close->SetPressTexture("NPCWindowClosePress.png");
	UIButtonList[_Index]->Close->SetEvent(_Event);

	UIButtonList[_Index]->Close->GetTransform()->SetLocalPosition({ -210, -109, -3 });
	UIButtonList[_Index]->Close->GetTransform()->SetLocalScale({ 85, 18, -3 });

	if(DialogIndex != _Index)
	{
		UIButtonList[_Index]->Close->Off();
	}
}

void NPCWindow::SetNextButton(int _Index)
{

}

void NPCWindow::SetPrevButton(int _Index)
{

}

void NPCWindow::SetOKButton(int _Index, std::function<void()> _Event)
{

}

void NPCWindow::UIButtonsOn()
{
	if(UIButtonList[DialogIndex]->Close != nullptr)
	{
		UIButtonList[DialogIndex]->Close->On();
	}
	
	if (UIButtonList[DialogIndex]->Next != nullptr)
	{
		UIButtonList[DialogIndex]->Next->On();
	}	
	
	if (UIButtonList[DialogIndex]->Prev != nullptr)
	{
		UIButtonList[DialogIndex]->Prev->On();
	}	
	
	if (UIButtonList[DialogIndex]->OK != nullptr)
	{
		UIButtonList[DialogIndex]->OK->On();
	}
}

void NPCWindow::UIButtonsOff() 
{
	if (UIButtonList[DialogIndex]->Close != nullptr)
	{
		UIButtonList[DialogIndex]->Close->Off();
	}

	if (UIButtonList[DialogIndex]->Next != nullptr)
	{
		UIButtonList[DialogIndex]->Next->Off();
	}

	if (UIButtonList[DialogIndex]->Prev != nullptr)
	{
		UIButtonList[DialogIndex]->Prev->Off();
	}

	if (UIButtonList[DialogIndex]->OK != nullptr)
	{
		UIButtonList[DialogIndex]->OK->Off();
	}
}


void NPCWindow::ButtonsDeath()
{
	std::map<int, std::shared_ptr<UIButtons>>::iterator StartIter = UIButtonList.begin();
	std::map<int, std::shared_ptr<UIButtons>>::iterator EndIter = UIButtonList.end();

	for (; StartIter != EndIter;)
	{
		if (StartIter->second->Close != nullptr)
		{
			StartIter->second->Close->Death();
			StartIter->second->Close = nullptr;
		}

		if (StartIter->second->Next != nullptr)
		{
			StartIter->second->Next->Death();
			StartIter->second->Next = nullptr;
		}

		if (StartIter->second->Prev != nullptr)
		{
			StartIter->second->Prev->Death();
			StartIter->second->Prev = nullptr;
		}

		if (StartIter->second->OK != nullptr)
		{
			StartIter->second->OK->Death();
			StartIter->second->OK = nullptr;
		}

		StartIter = UIButtonList.erase(StartIter);
	}
}
