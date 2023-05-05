#include "PrecompileHeader.h"
#include "Player.h"
#include "PlayerValue.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
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

	AniFrameList["Jump"].push_back(0.0f);

	//Origin은 X반전 Y그대로

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
	BodyNeckPos["Jump"].push_back({ -4, 30 });

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

	ArmHandPos["Jump"].push_back({ -3, 3 });

	//Coat

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

	CoatOriginPos["Jump"]["WhiteTshirt"].push_back({ -10, 10 });

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

	CoatToNavelPos["Jump"]["WhiteTshirt"].push_back({ 4, 2 });

	CoatArmOriginPos["Stand"]["WhiteTshirt"].push_back({ -3, 4 });
	CoatArmOriginPos["Stand"]["WhiteTshirt"].push_back({ -3, 4 });
	CoatArmOriginPos["Stand"]["WhiteTshirt"].push_back({ -4, 4 });
	CoatArmOriginPos["Stand"]["WhiteTshirt"].push_back({ -3, 4 });

	CoatArmOriginPos["Walk"]["WhiteTshirt"].push_back({ -4, 3 });
	CoatArmOriginPos["Walk"]["WhiteTshirt"].push_back({ -3, 5 });
	CoatArmOriginPos["Walk"]["WhiteTshirt"].push_back({ -4, 3 });
	CoatArmOriginPos["Walk"]["WhiteTshirt"].push_back({ -4, 2 });

	CoatArmOriginPos["Jump"]["WhiteTshirt"].push_back({ -4, 4 });

	CoatArmToNavelPos["Stand"]["WhiteTshirt"].push_back({ 12, 4 });
	CoatArmToNavelPos["Stand"]["WhiteTshirt"].push_back({ 11, 5 });
	CoatArmToNavelPos["Stand"]["WhiteTshirt"].push_back({ 11, 4 });
	CoatArmToNavelPos["Stand"]["WhiteTshirt"].push_back({ 11, 5 });

	CoatArmToNavelPos["Walk"]["WhiteTshirt"].push_back({ 10, 7 });
	CoatArmToNavelPos["Walk"]["WhiteTshirt"].push_back({ 9, 3 });
	CoatArmToNavelPos["Walk"]["WhiteTshirt"].push_back({ 10, 7 });
	CoatArmToNavelPos["Walk"]["WhiteTshirt"].push_back({ 10, 9 });

	CoatArmToNavelPos["Jump"]["WhiteTshirt"].push_back({ 13, 5 });

	//Pants

	PantsOriginPos["Stand"]["BluePants"].push_back({ -9, 6 });
	PantsOriginPos["Stand"]["BluePants"].push_back({ -9, 6 });
	PantsOriginPos["Stand"]["BluePants"].push_back({ -9, 6 });
	PantsOriginPos["Stand"]["BluePants"].push_back({ -9, 6 });

	PantsOriginPos["Walk"]["BluePants"].push_back({ -9, 7 });
	PantsOriginPos["Walk"]["BluePants"].push_back({ -9, 6 });
	PantsOriginPos["Walk"]["BluePants"].push_back({ -9, 7 });
	PantsOriginPos["Walk"]["BluePants"].push_back({ -9, 6 });

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

	PantsToNavelPos["Jump"]["BluePants"].push_back({ 2, -5 });

	//Weapon

	WeaponOriginPos["Stand"]["BasicSword"].push_back({ -25, 7 });
	WeaponOriginPos["Stand"]["BasicSword"].push_back({ -25, 7 });
	WeaponOriginPos["Stand"]["BasicSword"].push_back({ -25, 7 });
	WeaponOriginPos["Stand"]["BasicSword"].push_back({ -25, 7 });

	WeaponOriginPos["Walk"]["BasicSword"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["BasicSword"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["BasicSword"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["BasicSword"].push_back({ -25, 7 });

	WeaponOriginPos["Jump"]["BasicSword"].push_back({ -13, 5 });

	WeaponOriginPos["Stand"]["Ganier"].push_back({ -25, 7 });
	WeaponOriginPos["Stand"]["Ganier"].push_back({ -25, 7 });
	WeaponOriginPos["Stand"]["Ganier"].push_back({ -25, 7 });
	WeaponOriginPos["Stand"]["Ganier"].push_back({ -25, 7 });

	WeaponOriginPos["Walk"]["Ganier"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["Ganier"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["Ganier"].push_back({ -25, 7 });
	WeaponOriginPos["Walk"]["Ganier"].push_back({ -25, 7 });

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

	WeaponToHandPos["Stand"]["Club"].push_back({ -5, -4 });
	WeaponToHandPos["Stand"]["Club"].push_back({ -5, -4 });
	WeaponToHandPos["Stand"]["Club"].push_back({ -5, -4 });
	WeaponToHandPos["Stand"]["Club"].push_back({ -5, -4 });

	WeaponToHandPos["Walk"]["Club"].push_back({ -7, -1 });
	WeaponToHandPos["Walk"]["Club"].push_back({ -7,  6 });
	WeaponToHandPos["Walk"]["Club"].push_back({ -7, -1 });
	WeaponToHandPos["Walk"]["Club"].push_back({ -7, -2 });

	//
	WeaponToNavelPos["Jump"]["BasicSword"].push_back({ 11, 27 });
	//Head

	HeadOriginPos["Front"] = float4{ -19, 17 };

	HeadToNeckPos["Front"] = float4{ 0, 15 };
	//x,y 둘다반전
	HeadBrowPos["Front"] = float4{ -4, 5 };

	//Hair

	HairOriginPos["Toven"]["Front"] = float4{ -24, 15 };
	//x,y 둘다반전
	HairToBrowPos["Toven"]["Front"] = float4{ 9, -1 };

	//Face

	FaceOriginPos["Face1"]["Default"] = float4{ -13, 8 };
	//x,y 둘다반전
	FaceToBrowPos["Face1"]["Default"] = float4{ 1, -12 };
}

