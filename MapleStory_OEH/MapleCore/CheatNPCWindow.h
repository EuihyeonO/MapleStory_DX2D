#pragma once
#include "BasicFunction.h"

class CheatNPCWindow : public BasicFunction
{

public:

	CheatNPCWindow();
	~CheatNPCWindow();

	CheatNPCWindow(const CheatNPCWindow& _Other) = delete;
	CheatNPCWindow(CheatNPCWindow&& _Other) noexcept = delete;
	CheatNPCWindow& operator=(const CheatNPCWindow& _Other) = delete;
	CheatNPCWindow& operator=(CheatNPCWindow&& _Other) noexcept = delete;

	void WindowDeath();

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	void GetEXP();
	void SelectLevel();
	void ColSwitch();
	void UpGradeClass();
	std::shared_ptr<class NPCWindow> MyWindow = nullptr;
};

