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

	MyWindow->SetNpcPos({ -189, 23 });
	MyWindow->SetNamePos({ -226, -36 });

	MyWindow->AddToTextButton("대량의 경험치를 획득한다.", 0, [this] {GetEXP();});
	MyWindow->AddToTextButton("원하는 레벨로 이동한다.", 0, [this] {SelectLevel(); });
	MyWindow->AddToTextButton("충돌 디버그모드를 켜고 끈다.", 0, [this] {ColSwitch(); });
	MyWindow->AddToTextButton("4차까지 전직을 한다", 0, [this] {UpGradeClass();});

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
	MyWindow->ChangeDialog("경험치를 줬다곰!");
}

void CheatNPCWindow::ColSwitch()
{
	MyWindow->CreateUIButtonList(1);
	GetLevel()->IsDebugSwitch();

	MyWindow->ChangeDialog("충돌 디버그를 온오프 했다곰!");
}

void CheatNPCWindow::SelectLevel()
{
	MyWindow->CreateUIButtonList(1);
	MyWindow->AddToTextButton("사우스페리", 1, [this] {GameEngineCore::ChangeLevel("Level_SouthFerry"); MyWindow->Death(); MyWindow = nullptr; });
	MyWindow->AddToTextButton("재즈바", 1, [this] {GameEngineCore::ChangeLevel("Level_JazzBar"); MyWindow->Death(); MyWindow = nullptr; });
	MyWindow->AddToTextButton("자쿰의 제단 입구", 1, [this] {GameEngineCore::ChangeLevel("Level_AlterOfZakumEnt"); MyWindow->Death(); MyWindow = nullptr; });
	MyWindow->AddToTextButton("자쿰의 시련 2", 1, [this] {GameEngineCore::ChangeLevel("Level_ZakumRoad2"); MyWindow->Death(); MyWindow = nullptr; });
	MyWindow->ChangeDialog("가고 싶은 레벨을 고르라곰!");
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