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
	MyWindow->SetNPC("GM.PNG", "������ ���");
	MyWindow->SetDialogText("���ϴ� �޴��� �����!");
	MyWindow->CreateUIButtonList(0);

	MyWindow->AddToTextButton("�뷮�� ����ġ�� ȹ���Ѵ�.", 0, [this] {GetEXP();});
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

	MyWindow->ChangeDialog("����ġ�� ��ٰ�!");
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