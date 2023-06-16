#include "PrecompileHeader.h"
#include "Player.h"
#include "PlayerValue.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <ctime>


void Player::SetAllTexturePosVector()
{
	//Frame
	AniFrameList["Stand"].push_back(0.5f);
	AniFrameList["Stand"].push_back(0.5f);
	AniFrameList["Stand"].push_back(0.5f);
	AniFrameList["Stand"].push_back(0.5f);

	AniFrameList["Walk"].push_back(0.18f);
	AniFrameList["Walk"].push_back(0.18f);
	AniFrameList["Walk"].push_back(0.18f);
	AniFrameList["Walk"].push_back(0.18f);

	AniFrameList["Swing0"].push_back(0.3f);
	AniFrameList["Swing0"].push_back(0.15f);
	AniFrameList["Swing0"].push_back(0.35f);

	AniFrameList["Swing1"].push_back(0.3f);
	AniFrameList["Swing1"].push_back(0.15f);
	AniFrameList["Swing1"].push_back(0.35f);

	AniFrameList["Swing2"].push_back(0.3f);
	AniFrameList["Swing2"].push_back(0.15f);
	AniFrameList["Swing2"].push_back(0.35f);

	AniFrameList["Alert"].push_back(0.5f);
	AniFrameList["Alert"].push_back(0.5f);
	AniFrameList["Alert"].push_back(0.5f);

	AniFrameList["Ladder"].push_back(0.25f);
	AniFrameList["Ladder"].push_back(0.25f);

	AniFrameList["Jump"].push_back(0.0f);

	//Origin은 X반전 Y그대로
	SetBodyTexturePosVector();
	//Coat
	SetCoatTexturePosVector();
	//Pants	
	SetPantsTexturePosVector();
	//Weapon
	SetWeaponTexturePosVector();
	//HairAndFace
	SetHairAndFaceTexturePosVector();
}

void Player::SetBodyTexturePosVector()
{
	//Body
	BodyOriginPos["Stand"].push_back({ -16, 31 });
	BodyOriginPos["Stand"].push_back({ -17, 31 });
	BodyOriginPos["Stand"].push_back({ -18, 31 });
	BodyOriginPos["Stand"].push_back({ -17, 31 });
	BodyOriginPos["Walk"].push_back({ -19, 32 });
	BodyOriginPos["Walk"].push_back({ -16, 32 });
	BodyOriginPos["Walk"].push_back({ -19, 32 });
	BodyOriginPos["Walk"].push_back({ -21, 31 });
	BodyOriginPos["Swing0"].push_back({ -11, 27 });
	BodyOriginPos["Swing0"].push_back({ -11, 31 });
	BodyOriginPos["Swing0"].push_back({ -38, 27 });
	BodyOriginPos["Swing1"].push_back({ -18, 31 });
	BodyOriginPos["Swing1"].push_back({ -21, 31 });
	BodyOriginPos["Swing1"].push_back({ -30, 29 });
	BodyOriginPos["Swing2"].push_back({ -36, 27 });
	BodyOriginPos["Swing2"].push_back({ -28, 30 });
	BodyOriginPos["Swing2"].push_back({ -36, 27 });

	BodyOriginPos["Alert"].push_back({ -16, 29 });
	BodyOriginPos["Alert"].push_back({ -16, 30 });
	BodyOriginPos["Alert"].push_back({ -16, 31 });

	BodyOriginPos["Ladder"].push_back({ -11, 43 });
	BodyOriginPos["Ladder"].push_back({ -10, 41 });
	
	BodyOriginPos["Jump"].push_back({ -22, 30 });


	//x는 그대로, y는 반전 
	BodyNavelPos["Stand"].push_back({ -8, 21 });
	BodyNavelPos["Stand"].push_back({ -7, 20 });
	BodyNavelPos["Stand"].push_back({ -6, 21 });
	BodyNavelPos["Stand"].push_back({ -7, 20 });
	BodyNavelPos["Walk"].push_back({ -6, 20 });
	BodyNavelPos["Walk"].push_back({ -6, 20 });
	BodyNavelPos["Walk"].push_back({ -6, 20 });
	BodyNavelPos["Walk"].push_back({ -6, 18 });
	BodyNavelPos["Swing0"].push_back({ -1, 16 });
	BodyNavelPos["Swing0"].push_back({ -8, 20 });
	BodyNavelPos["Swing0"].push_back({ -29, 17 });
	BodyNavelPos["Swing1"].push_back({ -6, 20 });
	BodyNavelPos["Swing1"].push_back({ -8, 18 });
	BodyNavelPos["Swing1"].push_back({ -11, 16 });
	BodyNavelPos["Swing2"].push_back({ -8, 16 });
	BodyNavelPos["Swing2"].push_back({ -24, 17 });
	BodyNavelPos["Swing2"].push_back({ -30, 16 });
	BodyNavelPos["Alert"].push_back({ -3, 18 });
	BodyNavelPos["Alert"].push_back({ -3, 19 });
	BodyNavelPos["Alert"].push_back({ -3, 20 });
	BodyNavelPos["Ladder"].push_back({ 0, 21 });
	BodyNavelPos["Ladder"].push_back({ 2, 19 });
	BodyNavelPos["Jump"].push_back({ -5, 18 });
	//
	BodyNeckPos["Stand"].push_back({ -4, 32 });
	BodyNeckPos["Stand"].push_back({ -4, 32 });
	BodyNeckPos["Stand"].push_back({ -4, 32 });
	BodyNeckPos["Stand"].push_back({ -4, 32 });
	BodyNeckPos["Walk"].push_back({ -4, 32 });
	BodyNeckPos["Walk"].push_back({ -4, 31 });
	BodyNeckPos["Walk"].push_back({ -4, 32 });
	BodyNeckPos["Walk"].push_back({ -4, 31 });
	BodyNeckPos["Swing0"].push_back({ -9, 26 });
	BodyNeckPos["Swing0"].push_back({ -10, 31 });
	BodyNeckPos["Swing0"].push_back({ -37, 25 });
	BodyNeckPos["Swing1"].push_back({ -4, 32 });
	BodyNeckPos["Swing1"].push_back({ -13, 30 });
	BodyNeckPos["Swing1"].push_back({ -17, 27 });
	BodyNeckPos["Swing2"].push_back({ -11, 27 });
	BodyNeckPos["Swing2"].push_back({ -31, 28 });
	BodyNeckPos["Swing2"].push_back({ -34, 26 });
	BodyNeckPos["Alert"].push_back({ -4, 29 });
	BodyNeckPos["Alert"].push_back({ -4, 30 });
	BodyNeckPos["Alert"].push_back({ -4, 31 });
	BodyNeckPos["Ladder"].push_back({ -1, 30 });
	BodyNeckPos["Ladder"].push_back({ 2, 28 });
	BodyNeckPos["Jump"].push_back({ -4, 30 });

	//
	BodyHandPos["Ladder"].push_back({ -4, 39 });
	BodyHandPos["Ladder"].push_back({ 7, 38 });
	//Arm

	ArmOriginPos["Stand"].push_back({ -5, 9 });
	ArmOriginPos["Stand"].push_back({ -5, 9 });
	ArmOriginPos["Stand"].push_back({ -6, 9 });
	ArmOriginPos["Stand"].push_back({ -5, 9 });
	ArmOriginPos["Walk"].push_back({ -6, 8 });
	ArmOriginPos["Walk"].push_back({ -6, 9 });
	ArmOriginPos["Walk"].push_back({ -6, 9 });
	ArmOriginPos["Walk"].push_back({ -7, 7 });
	ArmOriginPos["Swing0"].push_back({ -7, 7 });
	ArmOriginPos["Swing0"].push_back({ -7, 7 });
	ArmOriginPos["Swing0"].push_back({ -6, 7 });
	ArmOriginPos["Swing1"].push_back({ -11, 7 });
	ArmOriginPos["Swing1"].push_back({ -12, 6 });
	ArmOriginPos["Swing1"].push_back({ -10, 8 });
	ArmOriginPos["Swing2"].push_back({ -11, 7 });
	ArmOriginPos["Swing2"].push_back({ -12, 6 });
	ArmOriginPos["Swing2"].push_back({ -10, 8 });
	ArmOriginPos["Alert"].push_back({ -6, 8 });
	ArmOriginPos["Alert"].push_back({ -7, 8 });
	ArmOriginPos["Alert"].push_back({ -6, 10 });
	ArmOriginPos["Jump"].push_back({ -7,7 });

	//X 반전, Y그대로
	ArmToNavelPos["Stand"].push_back({ 13, -1 });
	ArmToNavelPos["Stand"].push_back({ 13, 0 });
	ArmToNavelPos["Stand"].push_back({ 13, -1 });
	ArmToNavelPos["Stand"].push_back({ 13, 0 });
	ArmToNavelPos["Walk"].push_back({ 12, 2 });
	ArmToNavelPos["Walk"].push_back({ 6, -1 });
	ArmToNavelPos["Walk"].push_back({ 12, 2 });
	ArmToNavelPos["Walk"].push_back({ 13, 4 });
	ArmToNavelPos["Swing0"].push_back({ -5, 2 });
	ArmToNavelPos["Swing0"].push_back({ -5, 4 });
	ArmToNavelPos["Swing0"].push_back({ 8, 18 });
	ArmToNavelPos["Swing1"].push_back({ -11, 12 });
	ArmToNavelPos["Swing1"].push_back({ -13, 9 });
	ArmToNavelPos["Swing1"].push_back({ 14, 3 });

	ArmToNavelPos["Swing2"].push_back({ 14, 10 });
	ArmToNavelPos["Swing2"].push_back({ -11, 5 });
	ArmToNavelPos["Swing2"].push_back({ 2, 1 });

	ArmToNavelPos["Alert"].push_back({ 11,  1 });
	ArmToNavelPos["Alert"].push_back({ 11,  1 });
	ArmToNavelPos["Alert"].push_back({ 11, -1 });

	ArmToNavelPos["Jump"].push_back({ 7, 5 });

	//Y만 반전
	ArmHandPos["Stand"].push_back({ -1, -5 });
	ArmHandPos["Stand"].push_back({ -1, -5 });
	ArmHandPos["Stand"].push_back({ -1, -5 });
	ArmHandPos["Stand"].push_back({ -1, -5 });

	ArmHandPos["Walk"].push_back({ 1, -5 });
	ArmHandPos["Walk"].push_back({ -2, -5 });
	ArmHandPos["Walk"].push_back({ 1, -6 });
	ArmHandPos["Walk"].push_back({ 3, -5 });

	ArmHandPos["Swing0"].push_back({ 0, -2 });
	ArmHandPos["Swing0"].push_back({ -3, -5 });
	ArmHandPos["Swing0"].push_back({ 11, 1 });

	ArmHandPos["Swing1"].push_back({ -6, 4 });
	ArmHandPos["Swing1"].push_back({ -8, -8 });
	ArmHandPos["Swing1"].push_back({ 5, -4 });

	ArmHandPos["Swing2"].push_back({ 6, 3 });
	ArmHandPos["Swing2"].push_back({ -9, -2 });
	ArmHandPos["Swing2"].push_back({ -9, 0 });

	ArmHandPos["Alert"].push_back({ -5, -5 });
	ArmHandPos["Alert"].push_back({ -6, -6 });
	ArmHandPos["Alert"].push_back({ -5, -5 });

	ArmHandPos["Jump"].push_back({ -3, 3 });
	//
	HeadOriginPos["Front"] = float4{ -19, 17 };
	HeadOriginPos["Back"] = float4{ -20, 17 };

	HeadToNeckPos["Front"] = float4{ 0, 15 };
	HeadToNeckPos["Back"] = float4{ 0, 15 };
	//x,y 둘다반전
	HeadBrowPos["Front"] = float4{ -4, 5 };
	HeadBrowPos["Back"] = float4{ -4, 5 };
}

void Player::SetCoatTexturePosVector()
{
	CoatOriginPos["Stand"]["WhiteTshirt"].push_back({ -11, 9 });
	CoatOriginPos["Stand"]["WhiteTshirt"].push_back({ -10, 9 });
	CoatOriginPos["Stand"]["WhiteTshirt"].push_back({ -10, 9 });
	CoatOriginPos["Stand"]["WhiteTshirt"].push_back({ -10, 9 });

	CoatOriginPos["Walk"]["WhiteTshirt"].push_back({ -11, 9 });
	CoatOriginPos["Walk"]["WhiteTshirt"].push_back({ -11, 9 });
	CoatOriginPos["Walk"]["WhiteTshirt"].push_back({ -11, 9 });
	CoatOriginPos["Walk"]["WhiteTshirt"].push_back({ -11, 9 });

	CoatOriginPos["Swing0"]["WhiteTshirt"].push_back({ -11, 9 });
	CoatOriginPos["Swing0"]["WhiteTshirt"].push_back({ -10, 10 });
	CoatOriginPos["Swing0"]["WhiteTshirt"].push_back({ -11, 9 });

	CoatOriginPos["Swing1"]["WhiteTshirt"].push_back({ -10, 10 });
	CoatOriginPos["Swing1"]["WhiteTshirt"].push_back({ -10, 10 });
	CoatOriginPos["Swing1"]["WhiteTshirt"].push_back({ -11, 9 });
	
	CoatOriginPos["Swing2"]["WhiteTshirt"].push_back({ -10, 10 });
	CoatOriginPos["Swing2"]["WhiteTshirt"].push_back({ -10, 10 });
	CoatOriginPos["Swing2"]["WhiteTshirt"].push_back({ -11, 9 });

	CoatOriginPos["Alert"]["WhiteTshirt"].push_back({ -10, 10 });
	CoatOriginPos["Alert"]["WhiteTshirt"].push_back({ -10, 10 });
	CoatOriginPos["Alert"]["WhiteTshirt"].push_back({ -11, 9 });

	CoatOriginPos["Ladder"]["WhiteTshirt"].push_back({ -10, 10 });
	CoatOriginPos["Ladder"]["WhiteTshirt"].push_back({ -10, 10 });

	CoatOriginPos["Jump"]["WhiteTshirt"].push_back({ -10, 10 });

	//
	CoatToNavelPos["Stand"]["WhiteTshirt"].push_back({ 8, 1 });
	CoatToNavelPos["Stand"]["WhiteTshirt"].push_back({ 6, 2 });
	CoatToNavelPos["Stand"]["WhiteTshirt"].push_back({ 5, 1 });
	CoatToNavelPos["Stand"]["WhiteTshirt"].push_back({ 6, 2 });

	CoatToNavelPos["Walk"]["WhiteTshirt"].push_back({ 6, 3 });
	CoatToNavelPos["Walk"]["WhiteTshirt"].push_back({ 6, 3 });
	CoatToNavelPos["Walk"]["WhiteTshirt"].push_back({ 6, 3 });
	CoatToNavelPos["Walk"]["WhiteTshirt"].push_back({ 6, 4 });

	CoatToNavelPos["Swing0"]["WhiteTshirt"].push_back({ 5, 2 });
	CoatToNavelPos["Swing0"]["WhiteTshirt"].push_back({ 7, 1 });
	CoatToNavelPos["Swing0"]["WhiteTshirt"].push_back({ 6, 1 });

	CoatToNavelPos["Swing1"]["WhiteTshirt"].push_back({ 5, 1 });
	CoatToNavelPos["Swing1"]["WhiteTshirt"].push_back({ 4, 3 });
	CoatToNavelPos["Swing1"]["WhiteTshirt"].push_back({ 4, 3 });

	CoatToNavelPos["Swing2"]["WhiteTshirt"].push_back({ 0, 1 });
	CoatToNavelPos["Swing2"]["WhiteTshirt"].push_back({ 6, 3 });
	CoatToNavelPos["Swing2"]["WhiteTshirt"].push_back({ 9, 2 });

	CoatToNavelPos["Alert"]["WhiteTshirt"].push_back({ 3, 1 });
	CoatToNavelPos["Alert"]["WhiteTshirt"].push_back({ 3, 1 });
	CoatToNavelPos["Alert"]["WhiteTshirt"].push_back({ 5, 2 });

	CoatToNavelPos["Ladder"]["WhiteTshirt"].push_back({ 0, -1 });
	CoatToNavelPos["Ladder"]["WhiteTshirt"].push_back({ 2, -1 });

	CoatToNavelPos["Jump"]["WhiteTshirt"].push_back({ 4, 2 });

	CoatArmOriginPos["Stand"]["WhiteTshirt"].push_back({ -3, 4 });
	CoatArmOriginPos["Stand"]["WhiteTshirt"].push_back({ -3, 4 });
	CoatArmOriginPos["Stand"]["WhiteTshirt"].push_back({ -4, 4 });
	CoatArmOriginPos["Stand"]["WhiteTshirt"].push_back({ -3, 4 });

	CoatArmOriginPos["Walk"]["WhiteTshirt"].push_back({ -4, 3 });
	CoatArmOriginPos["Walk"]["WhiteTshirt"].push_back({ -3, 5 });
	CoatArmOriginPos["Walk"]["WhiteTshirt"].push_back({ -4, 3 });
	CoatArmOriginPos["Walk"]["WhiteTshirt"].push_back({ -4, 2 });

	CoatArmOriginPos["Swing0"]["WhiteTshirt"].push_back({ -3, 5 });
	CoatArmOriginPos["Swing0"]["WhiteTshirt"].push_back({ -3, 5 });
	CoatArmOriginPos["Swing0"]["WhiteTshirt"].push_back({ -3, 5 });
	
	CoatArmOriginPos["Swing1"]["WhiteTshirt"].push_back({ -4, 4 });
	CoatArmOriginPos["Swing1"]["WhiteTshirt"].push_back({ -3, 5 });
	CoatArmOriginPos["Swing1"]["WhiteTshirt"].push_back({ -3, 5 });
	
	CoatArmOriginPos["Swing2"]["WhiteTshirt"].push_back({ -4, 4 });
	CoatArmOriginPos["Swing2"]["WhiteTshirt"].push_back({ -3, 5 });
	CoatArmOriginPos["Swing2"]["WhiteTshirt"].push_back({ -3, 5 });

	CoatArmOriginPos["Alert"]["WhiteTshirt"].push_back({ -4, 4 });
	CoatArmOriginPos["Alert"]["WhiteTshirt"].push_back({ -3, 5 });
	CoatArmOriginPos["Alert"]["WhiteTshirt"].push_back({ -3, 5 });

	CoatArmOriginPos["Jump"]["WhiteTshirt"].push_back({ -4, 4 });

	CoatArmToNavelPos["Stand"]["WhiteTshirt"].push_back({ 12, 4 });
	CoatArmToNavelPos["Stand"]["WhiteTshirt"].push_back({ 11, 5 });
	CoatArmToNavelPos["Stand"]["WhiteTshirt"].push_back({ 11, 4 });
	CoatArmToNavelPos["Stand"]["WhiteTshirt"].push_back({ 11, 5 });

	CoatArmToNavelPos["Walk"]["WhiteTshirt"].push_back({ 10, 7 });
	CoatArmToNavelPos["Walk"]["WhiteTshirt"].push_back({ 9, 3 });
	CoatArmToNavelPos["Walk"]["WhiteTshirt"].push_back({ 10, 7 });
	CoatArmToNavelPos["Walk"]["WhiteTshirt"].push_back({ 10, 9 });

	CoatArmToNavelPos["Swing0"]["WhiteTshirt"].push_back({ -5, 4 });
	CoatArmToNavelPos["Swing0"]["WhiteTshirt"].push_back({ -1, 6 });
	CoatArmToNavelPos["Swing0"]["WhiteTshirt"].push_back({ 5, 8 });
	
	CoatArmToNavelPos["Swing1"]["WhiteTshirt"].push_back({ -2, 6 });
	CoatArmToNavelPos["Swing1"]["WhiteTshirt"].push_back({ -6, 5 });
	CoatArmToNavelPos["Swing1"]["WhiteTshirt"].push_back({ 7, 6 });
	
	CoatArmToNavelPos["Swing2"]["WhiteTshirt"].push_back({ 7, 6 });
	CoatArmToNavelPos["Swing2"]["WhiteTshirt"].push_back({ -4, 6 });
	CoatArmToNavelPos["Swing2"]["WhiteTshirt"].push_back({ -1, 4 });

	CoatArmToNavelPos["Alert"]["WhiteTshirt"].push_back({ 9, 5 });
	CoatArmToNavelPos["Alert"]["WhiteTshirt"].push_back({ 8, 4 });
	CoatArmToNavelPos["Alert"]["WhiteTshirt"].push_back({ 8, 4 });

	CoatArmToNavelPos["Jump"]["WhiteTshirt"].push_back({ 13, 5 });

}

void Player::SetPantsTexturePosVector()
{
	PantsOriginPos["Stand"]["BluePants"].push_back({ -9, 6 });
	PantsOriginPos["Stand"]["BluePants"].push_back({ -9, 6 });
	PantsOriginPos["Stand"]["BluePants"].push_back({ -9, 6 });
	PantsOriginPos["Stand"]["BluePants"].push_back({ -9, 6 });

	PantsOriginPos["Walk"]["BluePants"].push_back({ -9, 7 });
	PantsOriginPos["Walk"]["BluePants"].push_back({ -9, 6 });
	PantsOriginPos["Walk"]["BluePants"].push_back({ -9, 7 });
	PantsOriginPos["Walk"]["BluePants"].push_back({ -9, 6 });

	PantsOriginPos["Swing0"]["BluePants"].push_back({ -9, 6 });
	PantsOriginPos["Swing0"]["BluePants"].push_back({ -10, 6 });
	PantsOriginPos["Swing0"]["BluePants"].push_back({ -9, 6 });

	PantsOriginPos["Swing1"]["BluePants"].push_back({ -10, 5 });
	PantsOriginPos["Swing1"]["BluePants"].push_back({ -10, 6 });
	PantsOriginPos["Swing1"]["BluePants"].push_back({ -9, 6 });
	
	PantsOriginPos["Swing2"]["BluePants"].push_back({ -10, 5 });
	PantsOriginPos["Swing2"]["BluePants"].push_back({ -10, 6 });
	PantsOriginPos["Swing2"]["BluePants"].push_back({ -9, 6 });

	PantsOriginPos["Alert"]["BluePants"].push_back({ -10, 5 });
	PantsOriginPos["Alert"]["BluePants"].push_back({ -10, 6 });
	PantsOriginPos["Alert"]["BluePants"].push_back({ -9, 6 });

	PantsOriginPos["Ladder"]["BluePants"].push_back({ -10, 5 });
	PantsOriginPos["Ladder"]["BluePants"].push_back({ -10, 5 });

	PantsOriginPos["Jump"]["BluePants"].push_back({ -10, 5 });

	//X만 반전
	PantsToNavelPos["Stand"]["BluePants"].push_back({ 5, -6 });
	PantsToNavelPos["Stand"]["BluePants"].push_back({ 4, -5 });
	PantsToNavelPos["Stand"]["BluePants"].push_back({ 3, -6 });
	PantsToNavelPos["Stand"]["BluePants"].push_back({ 4, -5 });

	PantsToNavelPos["Walk"]["BluePants"].push_back({ 5, -7 });
	PantsToNavelPos["Walk"]["BluePants"].push_back({ 3, -7 });
	PantsToNavelPos["Walk"]["BluePants"].push_back({ 5, -7 });
	PantsToNavelPos["Walk"]["BluePants"].push_back({ 5, -5 });

	PantsToNavelPos["Swing0"]["BluePants"].push_back({ 2, -3 });
	PantsToNavelPos["Swing0"]["BluePants"].push_back({ 8, -3 });
	PantsToNavelPos["Swing0"]["BluePants"].push_back({ 2, -3 });

	PantsToNavelPos["Swing1"]["BluePants"].push_back({ 4, -4 });
	PantsToNavelPos["Swing1"]["BluePants"].push_back({ 2, -3 });
	PantsToNavelPos["Swing1"]["BluePants"].push_back({ 2, -3 });

	PantsToNavelPos["Swing2"]["BluePants"].push_back({ 3, -4 });
	PantsToNavelPos["Swing2"]["BluePants"].push_back({ 8, -2 });
	PantsToNavelPos["Swing2"]["BluePants"].push_back({ 6, -3 });

	PantsToNavelPos["Alert"]["BluePants"].push_back({ 0, -6 });
	PantsToNavelPos["Alert"]["BluePants"].push_back({ -1, -7 });
	PantsToNavelPos["Alert"]["BluePants"].push_back({ -1, -7 });

	PantsToNavelPos["Ladder"]["BluePants"].push_back({ 2, -6 });
	PantsToNavelPos["Ladder"]["BluePants"].push_back({ 2, -6 });

	PantsToNavelPos["Jump"]["BluePants"].push_back({ 2, -5 });

}

void Player::SetWeaponTexturePosVector()
{
	WeaponOriginPos["Stand"]["BasicSword"].push_back({ -25, 7 });
	WeaponOriginPos["Stand"]["BasicSword"].push_back({ -25, 7 });
	WeaponOriginPos["Stand"]["BasicSword"].push_back({ -25, 7 });
	WeaponOriginPos["Stand"]["BasicSword"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["BasicSword"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["BasicSword"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["BasicSword"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["BasicSword"].push_back({ -25, 7 });
	WeaponOriginPos["Swing0"]["BasicSword"].push_back({ -11, 5 });
	WeaponOriginPos["Swing0"]["BasicSword"].push_back({ -11, 5 });
	WeaponOriginPos["Swing0"]["BasicSword"].push_back({ -11, 5 });
	WeaponOriginPos["Swing1"]["BasicSword"].push_back({ -12, 5 });
	WeaponOriginPos["Swing1"]["BasicSword"].push_back({ -12, 5 });
	WeaponOriginPos["Swing1"]["BasicSword"].push_back({ -12, 5 });
	WeaponOriginPos["Swing2"]["BasicSword"].push_back({ -12, 5 });
	WeaponOriginPos["Swing2"]["BasicSword"].push_back({ -12, 5 });
	WeaponOriginPos["Swing2"]["BasicSword"].push_back({ -12, 5 });
	WeaponOriginPos["Jump"]["BasicSword"].push_back({ -13, 5 });

	WeaponOriginPos["Stand"]["Ganier"].push_back({ -25, 7 });
	WeaponOriginPos["Stand"]["Ganier"].push_back({ -25, 7 });
	WeaponOriginPos["Stand"]["Ganier"].push_back({ -25, 7 });
	WeaponOriginPos["Stand"]["Ganier"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["Ganier"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["Ganier"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["Ganier"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["Ganier"].push_back({ -25, 7 });
	WeaponOriginPos["Swing0"]["Ganier"].push_back({ 10, 5 }); //사라짐
	WeaponOriginPos["Swing0"]["Ganier"].push_back({ -11, 5 });
	WeaponOriginPos["Swing0"]["Ganier"].push_back({ -11, 5 });
	WeaponOriginPos["Swing1"]["Ganier"].push_back({ -12, 5 });
	WeaponOriginPos["Swing1"]["Ganier"].push_back({ -12, 5 });
	WeaponOriginPos["Swing1"]["Ganier"].push_back({ -12, 5 });
	WeaponOriginPos["Swing2"]["Ganier"].push_back({ -12, 5 });
	WeaponOriginPos["Swing2"]["Ganier"].push_back({ -12, 5 });
	WeaponOriginPos["Swing2"]["Ganier"].push_back({ -12, 5 });//사라짐
	WeaponOriginPos["Alert"]["Ganier"].push_back({ -23, 10 });
	WeaponOriginPos["Alert"]["Ganier"].push_back({ -23, 10 });
	WeaponOriginPos["Alert"]["Ganier"].push_back({ -23, 10 });
	WeaponOriginPos["Jump"]["Ganier"].push_back({ -13, 5 });


	WeaponOriginPos["Stand"]["Club"].push_back({ -25, 7 });
	WeaponOriginPos["Stand"]["Club"].push_back({ -25, 7 });
	WeaponOriginPos["Stand"]["Club"].push_back({ -25, 7 });
	WeaponOriginPos["Stand"]["Club"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["Club"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["Club"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["Club"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["Club"].push_back({ -25, 7 });

	//X만 반전
	WeaponToHandPos["Stand"]["BasicSword"].push_back({ -6, -5 });
	WeaponToHandPos["Stand"]["BasicSword"].push_back({ -6, -5 });
	WeaponToHandPos["Stand"]["BasicSword"].push_back({ -6, -5 });
	WeaponToHandPos["Stand"]["BasicSword"].push_back({ -6, -5 });
	WeaponToHandPos["Walk"]["BasicSword"].push_back({ -8, -2 });
	WeaponToHandPos["Walk"]["BasicSword"].push_back({ -6, 6 });
	WeaponToHandPos["Walk"]["BasicSword"].push_back({ -8, -2 });
	WeaponToHandPos["Walk"]["BasicSword"].push_back({ -8, -1 });

	WeaponToHandPos["Stand"]["Ganier"].push_back({ 20, -2 });
	WeaponToHandPos["Stand"]["Ganier"].push_back({ 20, -2 });
	WeaponToHandPos["Stand"]["Ganier"].push_back({ 20, -2 });
	WeaponToHandPos["Stand"]["Ganier"].push_back({ 20, -2 });
	WeaponToHandPos["Walk"]["Ganier"].push_back({ 20, -2 });
	WeaponToHandPos["Walk"]["Ganier"].push_back({ 20, 0 });
	WeaponToHandPos["Walk"]["Ganier"].push_back({ 20, -2 });
	WeaponToHandPos["Walk"]["Ganier"].push_back({ 20, -1 });
	WeaponToHandPos["Alert"]["Ganier"].push_back({ 16, -4 });
	WeaponToHandPos["Alert"]["Ganier"].push_back({ 17, -5 });
	WeaponToHandPos["Alert"]["Ganier"].push_back({ 16, -6 });

	WeaponToHandPos["Stand"]["Club"].push_back({ -5, -4 });
	WeaponToHandPos["Stand"]["Club"].push_back({ -5, -4 });
	WeaponToHandPos["Stand"]["Club"].push_back({ -5, -4 });
	WeaponToHandPos["Stand"]["Club"].push_back({ -5, -4 });
	WeaponToHandPos["Walk"]["Club"].push_back({ -7, -1 });
	WeaponToHandPos["Walk"]["Club"].push_back({ -7,  6 });
	WeaponToHandPos["Walk"]["Club"].push_back({ -7, -1 });
	WeaponToHandPos["Walk"]["Club"].push_back({ -7, -2 });

	//
	WeaponToNavelPos["Swing0"]["BasicSword"].push_back({ 4, -1 });
	WeaponToNavelPos["Swing0"]["BasicSword"].push_back({ -4, -2 });
	WeaponToNavelPos["Swing0"]["BasicSword"].push_back({ 23, 41 });
	WeaponToNavelPos["Swing1"]["BasicSword"].push_back({ -11, 34 });
	WeaponToNavelPos["Swing1"]["BasicSword"].push_back({ -14, 35 });
	WeaponToNavelPos["Swing1"]["BasicSword"].push_back({ 26, 1 });
	WeaponToNavelPos["Swing2"]["BasicSword"].push_back({ 26, 33 });
	WeaponToNavelPos["Swing2"]["BasicSword"].push_back({ -39, 2 });
	WeaponToNavelPos["Swing2"]["BasicSword"].push_back({ 5, 1 });

	WeaponToNavelPos["Swing0"]["Ganier"].push_back({ -1, -1 });
	WeaponToNavelPos["Swing0"]["Ganier"].push_back({ -1, -1 });
	WeaponToNavelPos["Swing0"]["Ganier"].push_back({ 23, 20 });
	WeaponToNavelPos["Swing1"]["Ganier"].push_back({ -10, 14 });
	WeaponToNavelPos["Swing1"]["Ganier"].push_back({ -13, 10 });
	WeaponToNavelPos["Swing1"]["Ganier"].push_back({ 24, -1 });
	WeaponToNavelPos["Swing2"]["Ganier"].push_back({ 26, 12 });
	WeaponToNavelPos["Swing2"]["Ganier"].push_back({ -14, 3 });
	WeaponToNavelPos["Swing2"]["Ganier"].push_back({ -14, 3 });

	WeaponToNavelPos["Jump"]["BasicSword"].push_back({ 11, 27 });
	WeaponToNavelPos["Jump"]["Ganier"].push_back({ 12, 9 });

}


void Player::SetHairAndFaceTexturePosVector()
{
	HairOriginPos["Toven"]["Front"] = float4{ -24, 15 };
	HairOriginPos["Toven"]["Back"] = float4{ -17, 16 };
	//x,y 둘다반전
	HairToBrowPos["Toven"]["Front"] = float4{ 9, -1 };
	//x만 반전
	HairToBrowPos["Toven"]["Back"] = float4{ 3, -3 };

	//Face

	FaceOriginPos["Face1"]["Default"] = float4{ -13, 8 };
	//x,y 둘다반전
	FaceToBrowPos["Face1"]["Default"] = float4{ 1, -12 };
}

void Player::TextureUpdate()
{
	std::string BodyTexture = SkinType + "Body" + MoveType + std::to_string(AniIndex) + ".png";
	Body->SetScaleToTexture(BodyTexture);

	if (MoveType == "Ladder" || MoveType == "Rope")
	{
		Arm->Off();
		Face->Off();
		CoatArm->Off();
		Weapon->Off();
	}
	else
	{
		Arm->On();
		Face->On();
		CoatArm->On();
		Weapon->On();

		if (MoveType == "Swing2" && AniIndex == 2)
		{
			Weapon->Off();
		}

		if (MoveType == "Swing0" && AniIndex == 0)
		{
			Weapon->Off();
		}

		std::string ArmTexture = SkinType + "Arm" + MoveType + std::to_string(AniIndex) + ".png";
		Arm->SetScaleToTexture(ArmTexture);

		std::string FaceTexture = FaceName + Expression + ".png";
		Face->SetScaleToTexture(FaceTexture);

		std::string CoatArmTexture = CoatName + "Arm" + MoveType + std::to_string(AniIndex) + ".png";
		CoatArm->SetScaleToTexture(CoatArmTexture);

		std::string WeaponTexture = WeaponName + MoveType + std::to_string(AniIndex) + ".png";
		Weapon->SetScaleToTexture(WeaponTexture);
	}

	std::string HeadTexture = SkinType + "Head" + FrontBackDir + ".png";
	Head->SetScaleToTexture(HeadTexture);

	std::string HairTexture = HairName + FrontBackDir + HairStatus + ".png";
	Hair->SetScaleToTexture(HairTexture);

	std::string CoatTexture = CoatName + MoveType + std::to_string(AniIndex) + ".png";
	Coat->SetScaleToTexture(CoatTexture);

	std::string PantsTexture = PantsName + MoveType + std::to_string(AniIndex) + ".png";
	Pants->SetScaleToTexture(PantsTexture);

	if (isHit == true || isKnockBack == true)
	{
		HitTimeCount += TimeCount;

		if (HitTimeCount >= 0.15f)
		{
			HitTimeCount = 0.0f;

			if (Arm->ColorOptionValue.MulColor.x < 1.0f)
			{
				SetMulColorAllTexture(1.0f);
			}
			else
			{
				SetMulColorAllTexture(0.4f);
			}
		}
	}
}


void Player::TextureAnimationUpdate()
{
	if (MoveType == "Jump")
	{
		AniIndex = 0;
		return;
	}

	//MoveType에 따라 애니메이션 조절
	if (isSwing == true)
	{
		float Speed = PlayerValue::Value.AttackSpeed;
		AnimationCount += TimeCount * Speed;
	}
	else if (isRopeOrLadder == true)
	{
		//사다리는 이동중에만 애니메이션이 바뀜
		if (GameEngineInput::IsPress("Upkey") == true || GameEngineInput::IsPress("Downkey") == true)
		{
			AnimationCount += TimeCount;
		}
	}
	else
	{
		AnimationCount += TimeCount;
	}

	//애니메이션 조절
	if (AnimationCount >= AniFrameList[MoveType][AniIndex])
	{
		if(isAvenger == false)
		{
			AniIndex++;
		}

		//공격이 끝나면 자동으로 Stand로 변경
		if (isSwing == true && AniIndex == 3)
		{
			isSwing = false;
			MoveType = "Stand";
			AniIndex = 0;
			AnimationCount = 0.0f;

			if (Weapon->IsUpdate() == false)
			{
				Weapon->On();
			}

			return;
		}

		//인덱스 처음으로
		if (AniIndex >= AniFrameList[MoveType].size())
		{
			AniIndex = 0;
		}

		//카운트 초기화
		AnimationCount = 0.0f;

		//무기관련 애니메이션 조건식
		if (MoveType == "Swing2" && AniIndex == 2)
		{
			Weapon->Off();
		}

		if (MoveType == "Swing0" && AniIndex == 0)
		{
			Weapon->Off();
		}
		else if (MoveType == "Swing0" && AniIndex != 0)
		{
			Weapon->On();
		}
	}
}

void Player::TexturePosUpdate()
{
	float4 BodyScale = Body->GetTransform()->GetLocalScale();
	Body->GetTransform()->SetLocalPosition({ BodyScale.hx(), -BodyScale.hy()});
	//Origin
	Body->GetTransform()->AddLocalPosition(BodyOriginPos[MoveType][AniIndex]);

	float4 HeadScale = Head->GetTransform()->GetLocalScale();
	Head->GetTransform()->SetLocalPosition({ HeadScale.hx(), -HeadScale.hy(), 0 });
	Head->GetTransform()->AddLocalPosition(BodyNeckPos[MoveType][AniIndex] + HeadToNeckPos[FrontBackDir] + HeadOriginPos[FrontBackDir]);

	float4 HeadPos = Head->GetTransform()->GetLocalPosition();
	float4 BrowPos = HeadPos + HeadBrowPos[FrontBackDir];

	float4 HairScale = Hair->GetTransform()->GetLocalScale();
	Hair->GetTransform()->SetLocalPosition({ HairScale.hx(), -HairScale.hy(), 0 });
	Hair->GetTransform()->AddLocalPosition(BrowPos + HairToBrowPos[HairName][FrontBackDir] + HairOriginPos[HairName][FrontBackDir]);

	float4 CoatScale = Coat->GetTransform()->GetLocalScale();
	Coat->GetTransform()->SetLocalPosition({ CoatScale.hx(), -CoatScale.hy(), 0 });
	Coat->GetTransform()->AddLocalPosition(BodyNavelPos[MoveType][AniIndex] + CoatToNavelPos[MoveType][CoatName][AniIndex] + CoatOriginPos[MoveType][CoatName][AniIndex]);

	float4 PantsScale = Pants->GetTransform()->GetLocalScale();
	Pants->GetTransform()->SetLocalPosition({ PantsScale.hx(), -PantsScale.hy(), 0 });
	Pants->GetTransform()->AddLocalPosition(BodyNavelPos[MoveType][AniIndex] + PantsToNavelPos[MoveType][PantsName][AniIndex] + PantsOriginPos[MoveType][PantsName][AniIndex]);
	
	if (MoveType != "Ladder" && MoveType != "Rope")
	{
		float4 ArmScale = Arm->GetTransform()->GetLocalScale();
		Arm->GetTransform()->SetLocalPosition({ ArmScale.hx(), -ArmScale.hy(), 0 });
		Arm->GetTransform()->AddLocalPosition(BodyNavelPos[MoveType][AniIndex] + ArmToNavelPos[MoveType][AniIndex] + ArmOriginPos[MoveType][AniIndex]);
		float4 FaceScale = Face->GetTransform()->GetLocalScale();
		Face->GetTransform()->SetLocalPosition({ FaceScale.hx(), -FaceScale.hy(), 0 });
		Face->GetTransform()->AddLocalPosition(BrowPos + FaceToBrowPos[FaceName][Expression] + FaceOriginPos[FaceName][Expression]);
		float4 CoatArmScale = CoatArm->GetTransform()->GetLocalScale();
		CoatArm->GetTransform()->SetLocalPosition({ CoatArmScale.hx(), -CoatArmScale.hy(), 0 });
		CoatArm->GetTransform()->AddLocalPosition(BodyNavelPos[MoveType][AniIndex] + CoatArmToNavelPos[MoveType][CoatName][AniIndex] + CoatArmOriginPos[MoveType][CoatName][AniIndex]);
	}


	if (MoveType == "Jump" || MoveType == "Swing0" || MoveType == "Swing1" || MoveType == "Swing2")
	{		
		float4 WeaponScale = Weapon->GetTransform()->GetLocalScale();
		Weapon->GetTransform()->SetLocalPosition({ WeaponScale.hx(), -WeaponScale.hy(), 0 });
		Weapon->GetTransform()->AddLocalPosition(BodyNavelPos[MoveType][AniIndex] + WeaponToNavelPos[MoveType][WeaponName][AniIndex] + WeaponOriginPos[MoveType][WeaponName][AniIndex]);
	}
	else if (MoveType == "Rope" || MoveType == "Ladder")
	{
		//아무것도 안함
	}
	else
	{
		float4 HandPos = ArmHandPos[MoveType][AniIndex] + Arm->GetTransform()->GetLocalPosition();
		float4 WeaponScale = Weapon->GetTransform()->GetLocalScale();
		Weapon->GetTransform()->SetLocalPosition({ WeaponScale.hx(), -WeaponScale.hy(), 0 });
		Weapon->GetTransform()->AddLocalPosition(HandPos + WeaponToHandPos[MoveType][WeaponName][AniIndex] + WeaponOriginPos[MoveType][WeaponName][AniIndex]);
	}
}

void Player::SetMulColorAllTexture(float _MulColor)
{
	Body->ColorOptionValue.MulColor = { _MulColor, _MulColor, _MulColor, 1 };
	Arm->ColorOptionValue.MulColor = { _MulColor, _MulColor, _MulColor, 1 };
	Face->ColorOptionValue.MulColor = { _MulColor, _MulColor, _MulColor, 1 };
	CoatArm->ColorOptionValue.MulColor = { _MulColor, _MulColor, _MulColor, 1 };
	Pants->ColorOptionValue.MulColor = { _MulColor, _MulColor, _MulColor, 1 };
	Weapon->ColorOptionValue.MulColor = { _MulColor, _MulColor, _MulColor, 1 };
	Head->ColorOptionValue.MulColor = { _MulColor, _MulColor, _MulColor, 1 };
	Hair->ColorOptionValue.MulColor = { _MulColor, _MulColor, _MulColor, 1 };
	Coat->ColorOptionValue.MulColor = { _MulColor, _MulColor, _MulColor, 1 };
}