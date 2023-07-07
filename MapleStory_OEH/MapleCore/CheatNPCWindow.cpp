#include "PrecompileHeader.h"
#include "CheatNPCWindow.h"
#include "NPCWindow.h"
#include "PlayerValue.h"

#include <GameEngineCore/GameEngineLevel.h>
CheatNPCWindow::CheatNPCWindow()
{
}

CheatNPCWindow::~CheatNPCWindow()
{
}

void CheatNPCWindow::Start()
{
	MyWindow = GetLevel()->CreateActor<NPCWindow>();
	MyWindow->SetNPC("GM.PNG", "메이플 운영자");
	MyWindow->SetDialogText("원하는 메뉴를 고르라곰!");
	MyWindow->CreateUIButtonList(0);

	MyWindow->AddToTextButton("대량의 경험치를 획득한다.", 0, [this] {GetEXP();});
	MyWindow->SetNpcPos({ -189, 23 });
	MyWindow->SetNamePos({ -226, -36 });
}

void CheatNPCWindow::Update(float _DeltaTime) 
{

}

void CheatNPCWindow::Render(float _DeltaTime)
{

}
void CheatNPCWindow::GetEXP()
{
	PlayerValue::GetValue()->AddExp(100000000);
	MyWindow->CreateUIButtonList(1);

	MyWindow->ChangeDialog("경험치를 줬다곰!");
}

void CheatNPCWindow::WindowDeath()
{
	if (MyWindow != nullptr)
	{
		MyWindow->ButtonsDeath();
		MyWindow->Death();
		MyWindow = nullptr;
	}
}