#pragma once
#include "BasicFunction.h"
#include "BuffList.h"
#include <GameEngineCore/GameEngineTexture.h>

class GameEngineSpriteRenderer;
class Player : public BasicFunction
{
	friend BuffList;
	friend class SkillActor;
	friend class SkillList;
public:

	void Hit();

	static std::shared_ptr<Player> GetCurPlayer()
	{
		return CurPlayer;
	}

	void SetisHit(bool _isHit)
	{
		isHit = _isHit;
	}

	void SetColMap(const std::string_view& _MapName)
	{		
		ColMap = GameEngineTexture::Find(_MapName);
	}

	const std::string_view GetMoveType() const
	{
		return MoveType;
	}

	const int GetAniIndex() const
	{
		return AniIndex;
	}

	void SetMoveType(const std::string_view& _MoveType);

	void SetMovable(bool _Bool)
	{
		isMovable = _Bool;
	}

	const std::string_view GetLeftRightDir() const
	{
		return LeftRightDir;
	}

	const float4 GetWeaponPos() const
	{
		return Weapon->GetTransform()->GetWorldPosition();
	}

	const bool isBuffOn(const std::string_view& _BuffName)
	{
		return MyBuffList->IsBuffOn(_BuffName);
	}

	void SetCurPlayer(std::shared_ptr<Player> _Player)
	{
		CurPlayer = _Player;
	}
	
	void SetDelSkill(std::function<void(std::shared_ptr<Player>)> _Skill)
	{
		DelSkill = _Skill;
	}

	void SetInsSkill(std::function<void(std::shared_ptr<Player>)> _Skill)
	{
		InsertSkill = _Skill;
	}

	void SetPgDnSkill(std::function<void(std::shared_ptr<Player>)> _Skill)
	{
		PageDownSkill = _Skill;
	}

	void SetPgUpSkill(std::function<void(std::shared_ptr<Player>)> _Skill)
	{
		PageUpSkill = _Skill;
	}

	void SetShiftSkill(std::function<void(std::shared_ptr<Player>)> _Skill)
	{
		ShiftSkill = _Skill;
	}

	void SetHomeSkill(std::function<void(std::shared_ptr<Player>)> _Skill)
	{
		HomeSkill = _Skill;
	}

	void SetEndSkill(std::function<void(std::shared_ptr<Player>)> _Skill)
	{
		EndSkill = _Skill;
	}

	void SetCtrlSkill(std::function<void(std::shared_ptr<Player>)> _Skill)
	{
		CtrlSkill = _Skill;
	}

	void SetMulColorAllTexture(float _MulColor);


	void SetLeft();
	void SetRight();

	Player();
	~Player();

	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	
	static std::shared_ptr<Player> CurPlayer;
	std::shared_ptr<GameEngineTexture> ColMap;
	std::shared_ptr<class GameEngineCollision> BodyCollision;
	std::shared_ptr<class GameEngineCollision> PointCollision;

	void CameraUpdate(float _DeltaTime);

	float4 LerpStart = { 0,0 };
	float4 LerpEnd = { 0,0 };
	float LerpRatio = 0.0f;

	float4 PlayerPos = {0,0};

	void GetItem();

	//키 관련
	int GetStateByKeyInput() const;
	void CreateAllKey();

	//움직임관련

	void GravityUpdate(float _DeltaTime);
	void ActingUpdate(float _DeltaTime);

	bool isSameColor();

	void Idle();
	void Move(float _DeltaTime);
	void Swing();
	void Jump(float _DeltaTime);
	void JumpUpdate(float _DeltaTime);
	void RopeAndLadder(float _DeltaTime);
	void RopeAndLadderUp(float _DeltaTime);
	void RopeAndLadderDown(float _DeltaTime);

	bool isRopeOrLadder = false;
	bool isGround = false;
	bool isKeyJump = false;
	bool isSwing = false;

	bool isMovable = true;
	bool isHit = false;
	float HitTimeCount = 0.0f;

	bool isJumpUp = false;

	float Gravity = 200.0f;
	float GravityAccel = 1000.0f;

	float JumpPower = 585.0f;
	float JumpXMove = 0.0f;

	float BasicMoveSpeed = 100.0f;
	float MoveSpeed = 100.0f;

	//스킬관련

		//Active
	void LuckySeven();
	void Haste();
	void Avenger();
	void JavelinBooster();
	void ShadowPartner();
	void FlashJump();

		//Passive
	void KeenEyes();

	bool isFlashJump = false;
	bool isAvenger = false;
	bool isOnShadow = false;
	float Range = 300.0f;

	std::shared_ptr<BuffList> MyBuffList;

	std::function<void(Player&)> QSkill = nullptr;
	std::function<void(Player&)> WSkill = nullptr;
	std::function<void(Player&)> ESkill = nullptr;

	std::shared_ptr<class GameEngineCollision> RangeCheck = nullptr;

	std::function<void(std::shared_ptr<Player>)> DelSkill = nullptr;
	std::function<void(std::shared_ptr<Player>)> InsertSkill = nullptr;
	std::function<void(std::shared_ptr<Player>)> PageDownSkill = nullptr;
	std::function<void(std::shared_ptr<Player>)> PageUpSkill = nullptr;
	std::function<void(std::shared_ptr<Player>)> ShiftSkill = nullptr;
	std::function<void(std::shared_ptr<Player>)> HomeSkill = nullptr;
	std::function<void(std::shared_ptr<Player>)> EndSkill = nullptr;
	std::function<void(std::shared_ptr<Player>)> CtrlSkill = nullptr;


	//텍스쳐 관련 
	void SetAllTexturePosVector();
	void SetBodyTexturePosVector();
	void SetCoatTexturePosVector();
	void SetPantsTexturePosVector();
	void SetWeaponTexturePosVector();
	void SetHairAndFaceTexturePosVector();
	void TextureUpdate();
	void TextureAnimationUpdate();
	void TexturePosUpdate();

	int WeaponType = 0;

	float AnimationCount = 0.0f;
	int AniIndex = 0;

	float4 PrevPos = { 0, 0 };

	std::string MoveType = "";

	std::string LeftRightDir = ""; //좌우 방향
	std::string FrontBackDir = "Front"; //앞뒤 방향 ( ex 사다리를 탔을 땐 뒤 )

	std::string HairName = "Toven";
	std::string HairStatus = "Hair"; //모자를 썼는지 안썼는지

	std::string FaceName = "Face1";
	std::string Expression = "Default";

	std::string SkinType = "Basic";

	std::string CoatName = "";
	std::string PantsName = "";

	std::string WeaponName = "";

	std::map <std::string, std::vector<float>> AniFrameList;

	std::map<std::string, std::vector<float4>> BodyOriginPos;
	std::map<std::string, std::vector<float4>> BodyNavelPos;
	std::map<std::string, std::vector<float4>> BodyNeckPos;
	std::map<std::string, std::vector<float4>> BodyHandPos;
	std::map<std::string, std::vector<float4>> ArmOriginPos;
	std::map<std::string, std::vector<float4>> ArmToNavelPos;
	std::map<std::string, std::vector<float4>> ArmHandPos;

	std::map<std::string, float4> HeadOriginPos;
	std::map<std::string, float4> HeadToNeckPos;
	std::map<std::string, float4> HeadBrowPos;

	std::map<std::string, std::map<std::string, float4>> HairOriginPos;
	std::map<std::string, std::map<std::string, float4>> HairToBrowPos;

	std::map<std::string, std::map<std::string, float4>> FaceOriginPos;
	std::map<std::string, std::map<std::string, float4>> FaceToBrowPos;

	std::map<std::string, std::map<std::string, std::vector<float4>>> CoatOriginPos;
	std::map<std::string, std::map<std::string, std::vector<float4>>> CoatToNavelPos;

	std::map<std::string, std::map<std::string, std::vector<float4>>> CoatArmOriginPos;
	std::map<std::string, std::map<std::string, std::vector<float4>>> CoatArmToNavelPos;

	std::map<std::string, std::map<std::string, std::vector<float4>>> PantsOriginPos;
	std::map<std::string, std::map<std::string, std::vector<float4>>> PantsToNavelPos;

	std::map<std::string, std::map<std::string, std::vector<float4>>> WeaponOriginPos;
	std::map<std::string, std::map<std::string, std::vector<float4>>> WeaponToHandPos;
	std::map<std::string, std::map<std::string, std::vector<float4>>> WeaponToNavelPos;

	std::shared_ptr<GameEngineSpriteRenderer> Body;
	std::shared_ptr<GameEngineSpriteRenderer> Arm;
	std::shared_ptr<GameEngineSpriteRenderer> Head;
	std::shared_ptr<GameEngineSpriteRenderer> Coat;
	std::shared_ptr<GameEngineSpriteRenderer> CoatArm;
	std::shared_ptr<GameEngineSpriteRenderer> Pants;
	std::shared_ptr<GameEngineSpriteRenderer> Weapon;
	std::shared_ptr<GameEngineSpriteRenderer> Hair;
	std::shared_ptr<GameEngineSpriteRenderer> Face;

};

