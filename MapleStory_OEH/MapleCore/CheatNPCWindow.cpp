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

	MyWindow->SetNpcPos({ -189, 23 });
	MyWindow->SetNamePos({ -226, -36 });

	MyWindow->AddToTextButton("�뷮�� ����ġ�� ȹ���Ѵ�.", 0, [this] {GetEXP();});
	MyWindow->AddToTextButton("���ϴ� ������ �̵��Ѵ�.", 0, [this] {SelectLevel(); });
	MyWindow->AddToTextButton("�浹 ����׸�带 �Ѱ� ����.", 0, [this] {ColSwitch(); });
	MyWindow->AddToTextButton("4������ ������ �Ѵ�", 0, [this] {UpGradeClass();});

	MyWindow->SetTextButtonPos({ 0, 25 });
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

void CheatNPCWindow::ColSwitch()
{
	MyWindow->CreateUIButtonList(1);
	GetLevel()->IsDebugSwitch();

	MyWindow->ChangeDialog("�浹 ����׸� �¿��� �ߴٰ�!");
}

void CheatNPCWindow::SelectLevel()
{
	MyWindow->CreateUIButtonList(1);
	MyWindow->AddToTextButton("��콺�丮", 1, [this] {GameEngineCore::ChangeLevel("Level_SouthFerry"); MyWindow->Death(); MyWindow = nullptr; });
	MyWindow->AddToTextButton("�����", 1, [this] {GameEngineCore::ChangeLevel("Level_JazzBar"); MyWindow->Death(); MyWindow = nullptr; });
	MyWindow->AddToTextButton("������ ���� �Ա�", 1, [this] {GameEngineCore::ChangeLevel("Level_AlterOfZakumEnt"); MyWindow->Death(); MyWindow = nullptr; });
	MyWindow->AddToTextButton("������ �÷� 2", 1, [this] {GameEngineCore::ChangeLevel("Level_ZakumRoad2"); MyWindow->Death(); MyWindow = nullptr; });
	MyWindow->ChangeDialog("���� ���� ������ �����!");
}

void CheatNPCWindow::UpGradeClass()
{
	PlayerValue::GetValue()->UpGradeClass();
	PlayerValue::GetValue()->UpGradeClass();
	PlayerValue::GetValue()->UpGradeClass();
	PlayerValue::GetValue()->UpGradeClass();

	WindowDeath();
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